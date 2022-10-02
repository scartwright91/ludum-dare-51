#pragma once

#include <map>
#include <string>
#include <random>

#include "../src/s2d/Object.h"
#include "../src/s2d/Text.h"


class Order
{

public:

	unsigned int barNumber;
	unsigned int level;
	float orderHeight;
	float orderWidth;
	bool orderComplete = false;
	std::map<std::string, unsigned int> order = {};
	s2d::Object* sprite = nullptr;

	Order(float x, float y, unsigned int barNumber, unsigned int level) :
		orderHeight(200.f), orderWidth(150.f)
	{
		this->barNumber = barNumber;
		this->level = level;
		sprite = new s2d::Object(x, y);
		sprite->setRenderLayer(s2d::HUD_LAYER);
		sprite->size = glm::vec2(orderWidth, orderHeight);
		sprite->color = glm::vec3(.5f);
		createOrder();
	}
	~Order()
	{

	}

	bool isOrderComplete()
	{
		std::map<std::string, unsigned int>::iterator it;
		for (it = order.begin(); it != order.end(); it++)
		{
			if (it->second > 0)
				return false;
		}
		return true;
	}

	void addToOrder(std::string drink, unsigned int quantity)
	{
		order[drink] += quantity;
	}

	bool canCompleteOrder(std::map<std::string, unsigned int>* inventory)
	{
		std::map<std::string, unsigned int>::iterator it;
		for (it = inventory->begin(); it != inventory->end(); it++)
		{
			if (order[it->first] > it->second)
				return false;
		}
		return true;
	}

	void completeOrder(std::map<std::string, unsigned int>* inventory)
	{
		// iterate through order
		std::map<std::string, unsigned int>::iterator it;
		for (it = inventory->begin(); it != inventory->end(); it++)
		{
			it->second -= order[it->first];
			order[it->first] = 0;
		}
	}

	void addDrinksToSprite()
	{
		float yOffset = orderHeight - 40.f;

		// add bar number to top of order
		s2d::Text* t = new s2d::Text();
		t->setPosition(glm::vec2(0.f, yOffset));
		t->text = "Bar: " + std::to_string(barNumber);
		t->color = glm::vec3(0.0f);
		sprite->addChild(t);

		yOffset -= 30.f;

		// iterate through order
		std::map<std::string, unsigned int>::iterator it;
		for (it = order.begin(); it != order.end(); it++)
		{
			s2d::Text* t = new s2d::Text();
			t->setPosition(glm::vec2(0.f, yOffset));
			t->text = it->first + " " + std::to_string(it->second);
			t->textScale = glm::vec2(0.5f);
			t->color = glm::vec3(0.0f);
			sprite->addChild(t);
			yOffset -= 20.f;
		}
	}

	void createOrder()
	{
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> dist(0, 4);
		if (level == 0)
		{
			addToOrder("beer", dist(rng));
			addToOrder("wine", dist(rng));
		}
		else if (level == 1)
		{
			addToOrder("beer", dist(rng));
			addToOrder("wine", dist(rng));
			addToOrder("liquor", dist(rng));
		}
		else if (level == 2)
		{
			addToOrder("beer", dist(rng));
			addToOrder("wine", dist(rng));
			addToOrder("liquor", dist(rng));
			addToOrder("champagne", dist(rng));
		}
		addDrinksToSprite();
	}

};
