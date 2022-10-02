#pragma once

#include <vector>
#include <algorithm>

#include "../ResourceManager.h"
#include "Camera.h"
#include "Object.h"
#include "Particles.h"
#include "Text.h"

#include "rendering/SpriteRenderer.h"
#include "rendering/ParticleRenderer.h"
#include "rendering/TextRenderer.h"

#include "../graphics/Window.h"

namespace s2d
{

	class Scene
	{

	public:
		Scene(graphics::Window* window, ResourceManager* resourceManager);
		~Scene();

		graphics::Window* window;
		s2d::Camera* camera;

		int windowWidth;
		int windowHeight;

		void addChild(s2d::Object* object);
		void removeChild(s2d::Object* object);

		void update();
		void render();
		void clear();

	private:

		ResourceManager* resourceManager;
		s2d::SpriteRenderer* spriteRenderer;
		s2d::ParticleRenderer* particleRenderer;
		s2d::TextRenderer* textRenderer;

		s2d::Object* root; // root node for all children
		std::vector<s2d::Object*> linkedChildren = {}; // flattened version of children

		std::vector<s2d::Object*> preorderTraversal();
		void scaleScene(glm::vec2 s);
		void init();

	};
}

