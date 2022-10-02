#pragma once

#include <GLFW/glfw3.h>
#include <vector>

#include "../src/s2d/Scene.h"

#include "Order.h"
#include "Player.h"

class OrderManager
{

public:

	float orderTimer;
	unsigned int level;
	Order* currentOrder = nullptr;
	std::vector<Order*> orders = {};
	irrklang::ISoundEngine* soundEngine;

	OrderManager(s2d::Scene* scene, irrklang::ISoundEngine* soundEngine, unsigned int level) :
		orderTimer(0.f)
	{
		this->scene = scene;
		this->level = level;
		this->soundEngine = soundEngine;
	}
	~OrderManager()
	{

	}

	void update(float dt, Player* player, std::map<unsigned int, s2d::Object*> barMap)
	{
		orderTimer -= dt;
		if (orderTimer <= 0.f)
		{
			// create new order
			Order* order = createOrder(barMap);
			addOrder(order);
			orderTimer = 10.f;
		}
		
		// completing order logic
		if (currentOrder != NULL)
		{
			s2d::Object* bar;
			bar = barMap[currentOrder->barNumber];
			// check distance from player to bar
			glm::vec2 barPos = bar->getPosition();
			glm::vec2 playerPos = player->sprite.getPosition();
			float distance = (float) sqrt(pow(barPos.x - playerPos.x, 2) + pow(barPos.y - playerPos.y, 2));
			if (distance < 100.f)
			{
				bar->children[0]->color = glm::vec3(1.0f, 0.0f, 0.0f);
				if (scene->window->isKeyPressed(GLFW_KEY_SPACE))
				{
					if (currentOrder->canCompleteOrder(&player->inventory))
					{
						currentOrder->completeOrder(&player->inventory);
						//soundEngine->play2D("res/audio/drink_delivered.mp3");
					}
				}
			}
			else
			{
				bar->children[0]->color = glm::vec3(0.0f);
			}

			// check if order is complete
			if (currentOrder->isOrderComplete())
			{
				// reset bar color and remove order sprite
				bar->children[0]->color = glm::vec3(0.0f);
				scene->removeChild(currentOrder->sprite);
				// remove order from list and re-point current order
				orders.erase(orders.begin());
				if (orders.size() > 0)
				{
					currentOrder = orders[0];
					currentOrder->sprite->color = glm::vec3(0.9f);
				}
				else
					currentOrder = nullptr;
			}
		}

	}

	void addOrder(Order* order)
	{
		orders.push_back(order);
		if (currentOrder == NULL)
		{
			currentOrder = order;
			currentOrder->sprite->color = glm::vec3(0.9f);
		}
	}

	Order* createOrder(std::map<unsigned int, s2d::Object*> barMap)
	{
		std::mt19937 rng(dev());
		std::uniform_int_distribution<int> randomWidth(0, scene->windowWidth - 200);
		std::uniform_int_distribution<int> randomHeight(200, scene->windowHeight - 300);
		std::uniform_int_distribution<std::mt19937::result_type> dist(1, (int) barMap.size());

		float x = (float)randomWidth(rng);
		float y = (float)randomHeight(rng);

		bool searchingForBar = true;
		unsigned int barID;
		while (searchingForBar)
		{
			barID = dist(rng);
			for (std::map<unsigned int, s2d::Object*>::iterator it = barMap.begin(); it != barMap.end(); ++it) {
				if (barID != it->first)
					searchingForBar = false;
			}
		}

		Order* order = new Order(x, y, barID, level);
		scene->addChild(order->sprite);
		return order;
	}

private:
	s2d::Scene* scene = nullptr;
	std::random_device dev;

};
