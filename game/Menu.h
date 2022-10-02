#pragma once

#include <GLEW/glew.h>
#include <irrklang/irrKlang.h>

#include "../src/graphics/Window.h"
#include "../src/ResourceManager.h"
#include "../src/s2d/Scene.h"
#include "../src/s2d/Text.h"

class Menu
{

public:

	graphics::Window* window = nullptr;
	ResourceManager* resourceManager = nullptr;
	std::string menu;

	s2d::Scene* scene;

	Menu(graphics::Window* window, ResourceManager* resourceManager, std::string menu);
	~Menu();

	void run();
	void events();
	void update();
	void render();

	bool running;

};

