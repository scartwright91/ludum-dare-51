#include "Scene.h"

namespace s2d
{

	Scene::Scene(graphics::Window* window, ResourceManager* resourceManager)
	{
		this->window = window;
		this->resourceManager = resourceManager;
		init();
	}

	Scene::~Scene()
	{
		delete root;
		delete spriteRenderer;
		delete particleRenderer;
		delete textRenderer;
		delete camera;
	}

	void Scene::addChild(s2d::Object* object)
	{
		root->addChild(object);
		linkedChildren = preorderTraversal();
	}

	void Scene::removeChild(s2d::Object* object)
	{
		root->removeChild(object);
		linkedChildren = preorderTraversal();
	}

	void Scene::update()
	{
		camera->update();
		// screen resizing
		if ((window->getWidth() != windowWidth) || (window->getHeight() != windowHeight))
			scaleScene(window->getScale());
	}

	void Scene::render()
	{
		for (s2d::Object* obj : linkedChildren)
		{
			glm::vec2 offset = glm::vec2(0.0f);  //camera->getDifferenceFromTarget(obj->getScaledPosition())* obj->depth;
			glm::mat4 view = camera->getViewMatrix();
			glm::mat4 projection = camera->getProjectionMatrix();
			if (obj->renderLayer == SKY_LAYER || obj->renderLayer == HUD_LAYER)
				view = glm::mat4(1.0f);

			if (obj->renderType == SPRITE)
			{
				spriteRenderer->render(
					obj->calculateModelMatrix(offset),
					view,
					projection,
					obj->texture,
					obj->useTexture,
					obj->numberOfRows,
					obj->numberOfCols,
					obj->textureOffset,
					obj->color,
					obj->alpha
				);
			}
			else if (obj->renderType == PARTICLE)
			{
				ParticleGenerator* pg = (ParticleGenerator*)obj;
				particleRenderer->render(
					pg->particles,
					pg->calculateModelMatrix(offset),
					view,
					projection,
					pg->color
				);
			}
			else if (obj->renderType == TEXT)
			{
				Text* text = (Text*)obj;
				textRenderer->render(
					text->text,
					text->calculateModelMatrix(offset),
					view,
					projection,
					text->color,
					text->textScale
				);
			}
		}
	}

	void Scene::clear()
	{
		root->clear();
		linkedChildren = preorderTraversal();
		/*
		if (linkedChildren.size() > 1)
		{
			for (unsigned int i = 1; i < linkedChildren.size(); i++)
			{
				Object* obj = linkedChildren[i];
				obj->clear();
				delete obj;
			}
			linkedChildren.resize(1);
		}
		*/
	}

	std::vector<s2d::Object*> Scene::preorderTraversal()
	{
		std::stack<s2d::Object*> stack;
		std::vector<s2d::Object*> preorder;

		stack.push(root);

		while (!stack.empty()) {
			Object* temp = stack.top();
			stack.pop();
			// store the key in preorder vector(visited list)
			preorder.push_back(temp);
			// Push all of the child nodes of temp into
			// the stack from right to left.
			for (Object* child : temp->children)
			{
				stack.push(child);
			}
		}

		// extract sprite layer
		std::vector<s2d::Object*> spriteLayer;
		std::vector<s2d::Object*> entityLayer;
		std::vector<s2d::Object*> hudLayer;
		for (Object* o : preorder)
		{
			if (o->renderLayer == SPRITE_BACKGROUND_LAYER)
			{
				spriteLayer.push_back(o);
			}
			else if (o->renderLayer == SPRITE_LAYER)
			{
				entityLayer.push_back(o);
			}
			else if (o->renderLayer == HUD_LAYER)
			{
				hudLayer.push_back(o);
			}
		}

		// hacky fix
		spriteLayer.insert(spriteLayer.end(), entityLayer.begin(), entityLayer.end());
		spriteLayer.insert(spriteLayer.end(), hudLayer.begin(), hudLayer.end());

		// sort by depth
		/*
		std::sort(preorder.begin(), preorder.end(), [](const Object* lhs, const Object* rhs)
			{
				return lhs->renderLayer < rhs->renderLayer;
			});
		*/

		return spriteLayer;
	}

	void Scene::scaleScene(glm::vec2 s)
	{
		windowWidth = window->getWidth();
		windowHeight = window->getHeight();
		for (s2d::Object* obj : linkedChildren)
			obj->scale(s);
	}

	void Scene::init()
	{
		camera = new s2d::Camera(window);
		root = new s2d::Object();
		spriteRenderer = new s2d::SpriteRenderer(resourceManager->getShader("sprite"));
		particleRenderer = new s2d::ParticleRenderer(resourceManager->getShader("particle"));
		textRenderer = new s2d::TextRenderer("res/fonts/Vollkorn-Regular.ttf", resourceManager->getShader("text"));
	}
}
