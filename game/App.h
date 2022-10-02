#pragma once

#include <GLEW/glew.h>
#include <iostream>
#include <vector>
#include <string>

#include "../src/graphics/Window.h"
#include "../src/Clock.h"
#include "../src/s2d/Settings.h"
#include "../src/s2d/Scene.h"

#include "Game.h"
#include "Menu.h"


class App
{

public:

	graphics::Window window;
	ResourceManager resourceManager;

	Game* game = nullptr;
	Menu* startMenu = nullptr;
	Menu* wonMenu = nullptr;
	Menu* lostMenu = nullptr;
	Clock clock;

	App() : window("game", false)
	{
		init();
		loadResources();
		game = new Game(&window, &resourceManager);
		startMenu = new Menu(&window, &resourceManager, "start");
		wonMenu = new Menu(&window, &resourceManager, "won");
		lostMenu = new Menu(&window, &resourceManager, "lost");
	}
	~App()
	{
		delete game;
		delete startMenu;
		delete wonMenu;
		delete lostMenu;
	}

	void run()
	{
		while (!window.closed())
		{
			// update clock and window
			clock.tick(60);
			window.update();
			// run game or menu
			if (startMenu->running)
			{
				startMenu->run();
			}
			else if (game->running)
			{
				game->run(&clock);
			}
			else if (game->won)
			{
				wonMenu->run();
			}
			else
			{
				lostMenu->run();
			}
		}
	}

	void init() const
	{
		glewInit();
		glEnable(GL_BLEND);
		glEnable(GL_TEXTURE_2D);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void loadResources()
	{
		// shaders
		resourceManager.loadShader("res/shaders/sprite.vert", "res/shaders/sprite.frag", "sprite");
		resourceManager.loadShader("res/shaders/particle.vert", "res/shaders/particle.frag", "particle");
		resourceManager.loadShader("res/shaders/text.vert", "res/shaders/text.frag", "text");
		// textures
		resourceManager.loadTexture("res/textures/menu_lose.png", "menu_lose");

		resourceManager.loadTexture("res/textures/sprites/player.png", "player");
		resourceManager.loadTexture("res/textures/sprites/customer1.png", "customer1");
		resourceManager.loadTexture("res/textures/sprites/customer2.png", "customer2");
		resourceManager.loadTexture("res/textures/sprites/customer3.png", "customer3");
		resourceManager.loadTexture("res/textures/sprites/customer4.png", "customer4");
		resourceManager.loadTexture("res/tileset.png", "tileset");
	}

};