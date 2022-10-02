#pragma once

#include <iostream>
#include <GLEW/glew.h>
#include <irrklang/irrKlang.h>
#include <vector>
#include <string>

// engine scripts
#include "../src/graphics/Window.h"
#include "../src/graphics/UI.h"
#include "../src/Clock.h"
#include "../src/s2d/Settings.h"
#include "../src/s2d/Scene.h"
#include "../src/s2d/Particles.h"
#include "../src/s2d/Text.h"
#include "../ResourceManager.h"

// game 
#include "Player.h"
#include "LevelParser.h"
#include "OrderManager.h"
#include "Order.h"
#include "Crowd.h"


class Game
{

public:

	bool running = true;
	bool won = false;

	Game(graphics::Window* window, ResourceManager* resourceManager);
	~Game();

	Clock clock;

private:
	graphics::Window* window = nullptr;
	ResourceManager* resourceManager = nullptr;
	irrklang::ISoundEngine* soundEngine = irrklang::createIrrKlangDevice();
	std::random_device dev;
	s2d::Scene* scene;

	// hud stuff
	s2d::Text* fps;
	s2d::Text* orderTimer;
	s2d::Object* inventory;
	s2d::Text* closingTime;
	float secondsRemaining;
	s2d::Text* customerFrustrationHUD;
	float customerFrustration = 0.0f;

	LevelParser levelParser;
	Player player;
	s2d::ParticleGenerator* pg;

	std::map<unsigned int, s2d::Object*> barMap = {};
	std::vector<s2d::Object*> collideableEntities = {};
	std::vector<glm::vec2> crowdGrid = {};
	std::vector<s2d::Object*> beerEntities = {};
	std::vector<s2d::Object*> wineEntities = {};
	std::vector<s2d::Object*> liquorEntities = {};
	std::vector<s2d::Object*> champagneEntities = {};

	// orders
	OrderManager* orderManager = nullptr;

	// level generation
	unsigned int level = 0;
	float levelDuration = 60.f;
	void createLevel();

	// crowd
	Crowd* crowd = nullptr;

public:

	void run(Clock* clock);
	void events();
	void update(float dt);
	void render();

};

