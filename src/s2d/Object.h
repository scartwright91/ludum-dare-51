#pragma once

#include <iostream>
#include "GLEW/glew.h"
#include <vector>
#include <stack>
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "col/BoundingBox.h"
#include "rendering/RenderTypes.h"
#include "Settings.h"


namespace s2d
{

	class Object
	{
	public:

		// vertex
		glm::vec2 size = glm::vec2(0.0f);
		glm::vec3 modelScale = glm::vec3(1.0f);
		float rotation = 0.0f;

		// fragment
		glm::vec3 color = glm::vec3(0.0f);
		float alpha = 1.0f;
		unsigned int texture = 0;
		bool useTexture = false;
		float numberOfRows = 1.f;
		float numberOfCols = 1.f;
		glm::vec2 textureOffset = glm::vec2(0.0f);

		// children
		Object* parent = nullptr;
		std::vector <Object*> children = {};
		unsigned int nChildren = 0;

		// rendering
		RenderTypes renderType;
		unsigned int renderLayer = 0;
		float depth = 1.0f;

		Object() : renderType(SPRITE)
		{

		}

		Object(float x, float y) : renderType(SPRITE)
		{
			move(x, y);
		}

		~Object()
		{

		}

		void addChild(Object* o)
		{
			children.push_back(o);
			o->addParent(this);
			nChildren++;
		}

		void addParent(Object* o)
		{
			this->parent = o;
			syncParentPosition();
		}

		void removeChild(Object* o)
		{
			o->removeParent();
			children.erase(std::remove(children.begin(), children.end(), o), children.end());
			nChildren--;
		}

		void removeParent()
		{
			this->parent = nullptr;
		}

		void clear()
		{
			children.clear();
			/*
			for (unsigned int i = 0; i < children.size(); i++)
			{
				Object* obj = children[i];
				delete obj;
			}
			children.resize(0);
			*/
		}

		glm::mat4 calculateModelMatrix(glm::vec2 offset)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(getScaledPosition(), 0.0f));
			model = glm::translate(model, glm::vec3(-offset, 0.0f));
			model = glm::scale(model, glm::vec3(getScaledSize(), 1.0f));
			return model;
		}

		void move(float dx, float dy)
		{
			position += glm::vec2(dx, dy);
			for (Object* child : children)
			{
				child->move(dx, dy);
			}
		}

		void scale(glm::vec2 s)
		{
			modelScale = glm::vec3(s, 1.0f);
		}

		void rotate(float v)
		{
			rotation += v;
		}

		glm::vec2 getScaledSize()
		{
			glm::vec2 scaledSize = glm::vec2(size.x * modelScale.x, size.y * modelScale.y);
			return scaledSize;
		}

		glm::vec2 getScaledPosition()
		{
			glm::vec2 scaledPosition = glm::vec2(position.x * modelScale.x, position.y * modelScale.y);
			return scaledPosition;
		}

		glm::vec2 getPosition()
		{
			return position;
		}

		void setPosition(glm::vec2 pos)
		{
			glm::vec2 deltaPosition = pos - position;
			move(deltaPosition.x, deltaPosition.y);
		}

		void setTexture(unsigned int textureID)
		{
			this->texture = textureID;
			useTexture = true;
		}

		void setTileMapTexture(
			unsigned int textureID,
			float width,
			float height,
			unsigned int gridSize,
			unsigned int x,
			unsigned int y
		)
		{
			this->texture = textureID;
			useTexture = true;
			numberOfRows = (float)width / gridSize;
			numberOfCols = (float)height / gridSize;
			textureOffset = glm::vec2(x / width, y / height);
		}

		void setRenderLayer(RenderLayer layer)
		{
			renderLayer = (unsigned int) layer;
			if (layer == SKY_LAYER)
			{
				depth = SKY_DEPTH;
			}
			else if (layer == FAR_BACKGROUND_LAYER)
			{
				depth = FAR_BACKGROUND_DEPTH;
			}
			else if (layer == NEAR_BACKGROUND_LAYER)
			{
				depth = NEAR_BACKGROUND_DEPTH;
			}
			else if (layer == SPRITE_BACKGROUND_LAYER)
			{
				depth = NEAR_BACKGROUND_DEPTH;
			}
			else if (layer == SPRITE_LAYER)
			{
				depth = SPRITE_DEPTH;
			}
			else if (layer == FOREGROUND_LAYER)
			{
				depth = FOREGROUND_DEPTH;
			}
			else if (layer == HUD_LAYER)
			{
				depth = HUD_DEPTH;
			}
		}

		glm::vec2 getAbsolutePosition()
		{
			bool parentExists = true;
			Object* currentParent = parent;
			glm::vec2 absPosition = position;
			while (parentExists)
			{
				if (currentParent == NULL)
					parentExists = false;
				else
				{
					absPosition += currentParent->position;
					currentParent = currentParent->parent;
				}
			}
			return absPosition;
		}

		s2d::col::BoundingBox getBoundingBox()
		{
			return s2d::col::BoundingBox(position.x, position.y, size.x, size.y);
		}

		s2d::col::BoundingBox getShiftedBoundingBox(float dx, float dy)
		{
			return s2d::col::BoundingBox(position.x + dx, position.y + dy, size.x, size.y);
		}

	private:

		glm::vec2 position = glm::vec2(0.0f); // private to force using setPosition method

		void syncParentPosition()
		{
			position += parent->position;
		}

	};
}
