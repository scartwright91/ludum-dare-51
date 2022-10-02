#pragma once

#include <iostream>
#include <algorithm>
#include <cmath>

#include "../graphics/Window.h"
#include "Object.h"


namespace s2d
{
	class Camera
	{

	public:

		Object* target = nullptr;

		// camera position & screen position
		glm::vec3 cameraPosition = glm::vec3(0.0f);
		glm::vec2 screenPos = glm::vec2(0.0f, 0.0f);

		// zoom variables
		float zoom = 1.0f;

		// transition variables
		bool transitioning = false;
		double distance = 0.0f;

		Camera(graphics::Window* win) :
			window{win}
		{
			setTargetScreenPosition(0.5, 0.5);
		}
		~Camera()
		{

		}

		void setTargetScreenPosition(float x, float y)
		{
			screenPos = glm::vec2(x, y);
		}

		glm::vec2 getTargetScreenPosition(bool pixels)
		{
			if (pixels)
				return glm::vec2(screenPos.x * window->getWidth(), screenPos.y * window->getHeight());
			return screenPos;
		}

		void setTarget(Object* t, bool transition)
		{
			target = t;
			transitioning = transition;
			if (transitioning)
			{
				glm::vec2 pos = target->getScaledPosition();
				distance = sqrt(pow(pos.x - cameraPosition.x, 2) + pow(pos.y - cameraPosition.y, 2));
			}
		}

		glm::mat4 getViewMatrix()
		{
			glm::vec3 pos = glm::vec3(
				cameraPosition.x - (window->getWidth() * screenPos.x),
				cameraPosition.y - (window->getHeight() * screenPos.y),
				0.0f
			);
			glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
			glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
			return glm::lookAt(pos, pos + front, up);
		}

		glm::mat4 getProjectionMatrix()
		{
			float width = window->getWidth() * zoom;
			float height = window->getHeight() * zoom;
			float aspectRatio = (float)width / height;
			float halfHeight =  height / 2;
			float halfWidth = halfHeight * aspectRatio;
			glm::mat4 projection = glm::ortho(0.0f, (float)width, 0.0f, (float)height, -1.0f, 1.0f);
			return projection;
		}

		glm::vec2 getDifferenceFromTarget(glm::vec2 pos)
		{
			if (target == NULL)
				return glm::vec3(0.0f);
			return glm::vec3(target->getScaledPosition() - pos, 0.f);
		}

		void update()
		{

			// zoom in & out functionality
			/*
			if (window->isKeyPressed(GLFW_KEY_DOWN))
			{
				zoom += 0.01f;
				setTargetScreenPosition(0.5f * zoom, 0.5f * zoom);
			}
			if (window->isKeyPressed(GLFW_KEY_UP))
			{
				zoom -= 0.01f;
				setTargetScreenPosition(0.5f * zoom, 0.5f * zoom);
			}
			*/

			// set camera position
			if (transitioning)
			{
				glm::vec2 pos = target->getScaledPosition();
				glm::vec2 transition = calculateTransition();
				float dx = (pos.x - cameraPosition.x);
				float dy = (pos.y - cameraPosition.y);
				cameraPosition.x += transition.x;
				cameraPosition.y += transition.y;
				if ((abs(dx) < 0.01 * distance) && (abs(dy) < 0.01 * distance))
				{
					transitioning = false;
				}
			}
			else if (target != NULL)
			{
				glm::vec2 pos = target->getScaledPosition();
				cameraPosition = glm::vec3(pos, 0.0f);
			}
		}

	private:

		graphics::Window* window;

		glm::vec2 calculateTransition()
		{
			glm::vec2 pos = target->getScaledPosition();
			float theta = atan2(pos.y - cameraPosition.y, pos.x - cameraPosition.x);
			double currentDistance = sqrt(pow(pos.x - cameraPosition.x, 2) + pow(pos.y - cameraPosition.y, 2));
			float transitionDistance = (float) std::max(0.05 * currentDistance, 0.01 * distance);
			return glm::vec2(transitionDistance * cos(theta), transitionDistance * sin(theta));
		}

	};
}
