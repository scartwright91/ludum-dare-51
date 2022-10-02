#pragma once

#include "../src/ResourceManager.h"
#include "../src/s2d/Object.h"

class Customer
{

public:

	s2d::Object* sprite = nullptr;
	float min, max;
	float targetPosition;
	float speed;

	Customer(ResourceManager* resourceManager, glm::vec2 pos)
	{
		this->resourceManager = resourceManager;
		this->min = min;
		this->max = max;
		sprite = new s2d::Object();
		sprite->setPosition(pos);
		sprite->setRenderLayer(s2d::SPRITE_LAYER);

		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> dist(0, 3);

		speed = dist(rng) / 3 + 0.33;

		if (dist(rng) == 0)
			sprite->setTexture(resourceManager->getTexture("customer1").textureID);
		else if (dist(rng) == 1)
			sprite->setTexture(resourceManager->getTexture("customer2").textureID);
		else if (dist(rng) == 2)
			sprite->setTexture(resourceManager->getTexture("customer3").textureID);
		else if (dist(rng) == 3)
			sprite->setTexture(resourceManager->getTexture("customer4").textureID);
		else
			sprite->setTexture(resourceManager->getTexture("customer4").textureID);
		sprite->color = glm::vec3(0.0f);
		sprite->size = glm::vec2(64.f, 64.f);

		min = pos.x - 64;
		max = pos.x + 128;
		targetPosition = setTargetPosition();
	}
	~Customer()
	{

	}

	void update()
	{
		float dx = targetPosition - sprite->getPosition().x;
		if (targetPosition > sprite->getPosition().x)
		{
			sprite->move(speed, 0.f);
		}
		else
		{
			sprite->move(-speed, 0.f);
		}

		if (abs(dx) < 10.f)
		{
			targetPosition = setTargetPosition();
		}
		
	}

	float setTargetPosition()
	{
		std::mt19937 rng(dev());
		std::uniform_int_distribution<int> randomPosition((int)min, (int)max);
		return (float)randomPosition(rng);
	}

private:
	ResourceManager* resourceManager = nullptr;
	std::random_device dev;

};
