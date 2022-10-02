#pragma once

#include <vector>
#include <random>

#include "../src/ResourceManager.h"
#include "../src/s2d/Scene.h"

#include "Customer.h"

class Crowd
{

public:

	// generate 50 crowd members
	// jitter movement, speech bubbles, react to frustration levels

	std::vector<glm::vec2> grid = {};
	s2d::Scene* scene = nullptr;
	std::vector<Customer*> customers = {};

	Crowd(s2d::Scene* scene, ResourceManager* resourceManager, std::vector<glm::vec2> grid, unsigned int amount)
	{
		this->scene = scene;
		this->grid = grid;
		createCrowd(resourceManager, amount);
	}
	~Crowd()
	{

	}

	void update(float customerFrustration)
	{
		for (Customer* c : customers)
		{
			c->update();
		}
	}

	void createCrowd(ResourceManager* resourceManager, unsigned int amount)
	{
		for (unsigned int i = 0; i < amount; i++)
		{
			glm::vec2 randomPos = selectCrowdPosition();
			Customer* c = new Customer(resourceManager, randomPos);
			scene->addChild(c->sprite);
			customers.push_back(c);
		}
	}

	glm::vec2 selectCrowdPosition() {
		int random = rand() % grid.size();
		return grid[random];
	}

};
