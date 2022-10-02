#pragma once

#include <GLEW/glew.h>
#include <map>
#include <string>

#include "../src/graphics/Window.h"
#include "../src/s2d/Object.h"
#include "../src/s2d/Text.h"
#include "../src/s2d/Settings.h"

class Player
{

public:

	s2d::Object sprite;
	std::map<std::string, unsigned int> inventory = {
		{"beer", 0},
		{"wine", 0},
		{"liquor", 0},
		{"champagne", 0}
	};

	Player(float x, float y, unsigned int textureID);
	~Player();

	void update(
		float dt,
		graphics::Window* window,
		std::vector<s2d::Object*> collideableEntities,
		std::vector<s2d::Object*> beerEntities,
		std::vector<s2d::Object*> wineEntities,
		std::vector<s2d::Object*> liquorEntities,
		std::vector<s2d::Object*> champagneEntities
	);

	void clearPlayerInventory();
	void getPlayerInventory(s2d::Object* obj);

private:

	float speed = 400.0f;
	float weight = 1.0f;
	double pickupCooldown = glfwGetTime();

	glm::vec2 calculateMovement(graphics::Window* window, float dt);
	glm::vec2 calculateCollision(glm::vec2 movement, std::vector<s2d::Object*> collideableEntities);

	void pickupDrink(std::string drink);

};

