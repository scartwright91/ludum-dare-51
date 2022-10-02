#include "Player.h"

Player::Player(float x, float y, unsigned int textureID)
{
	sprite.setPosition(glm::vec2(x, y));
	sprite.size = glm::vec2(64.f, 64.f);
	sprite.color = glm::vec3(0.1f, 0.7f, 0.3f);
	sprite.setRenderLayer(s2d::SPRITE_LAYER);
	sprite.setTexture(textureID);
}

Player::~Player()
{

}

void Player::update(
	float dt,
	graphics::Window* window,
	std::vector<s2d::Object*> collideableEntities,
	std::vector<s2d::Object*> beerEntities,
	std::vector<s2d::Object*> wineEntities,
	std::vector<s2d::Object*> liquorEntities,
	std::vector<s2d::Object*> champagneEntities
	)
{
	// movement based on keyboard inputs
	glm::vec2 movementBeforeCollisions = calculateMovement(window, dt);
	// calculate collision logic
	glm::vec2 movementAfterCollisions = calculateCollision(movementBeforeCollisions, collideableEntities);
	// move player sprite
	sprite.move(movementAfterCollisions.x, movementAfterCollisions.y);

	double now = glfwGetTime();
	// beer detection
	for (s2d::Object* o : beerEntities)
	{
		// check distance from player to bar
		glm::vec2 pos = o->getPosition();
		glm::vec2 playerPos = sprite.getPosition();
		double distance = sqrt(pow(pos.x - playerPos.x, 2) + pow(pos.y - playerPos.y, 2));
		if (distance <= 100.f)
		{
			// can pick up a beer
			if (window->isKeyPressed(GLFW_KEY_SPACE) && (now - pickupCooldown > 1.f))
			{
				pickupDrink("beer");
				pickupCooldown = now;
			}
		}
	}
	// wine detection
	for (s2d::Object* o : wineEntities)
	{
		// check distance from player to bar
		glm::vec2 pos = o->getPosition();
		glm::vec2 playerPos = sprite.getPosition();
		double distance = sqrt(pow(pos.x - playerPos.x, 2) + pow(pos.y - playerPos.y, 2));
		if (distance <= 100.f)
		{
			// can pick up a beer
			if (window->isKeyPressed(GLFW_KEY_SPACE) && (now - pickupCooldown > .5f))
			{
				pickupDrink("wine");
				pickupCooldown = now;
			}
		}
	}
	// liquor detection
	for (s2d::Object* o : liquorEntities)
	{
		// check distance from player to bar
		glm::vec2 pos = o->getPosition();
		glm::vec2 playerPos = sprite.getPosition();
		double distance = sqrt(pow(pos.x - playerPos.x, 2) + pow(pos.y - playerPos.y, 2));
		if (distance <= 100.f)
		{
			// can pick up a beer
			if (window->isKeyPressed(GLFW_KEY_SPACE) && (now - pickupCooldown > .5f))
			{
				pickupDrink("liquor");
				pickupCooldown = now;
			}
		}
	}
	// champagne detection
	for (s2d::Object* o : champagneEntities)
	{
		// check distance from player to bar
		glm::vec2 pos = o->getPosition();
		glm::vec2 playerPos = sprite.getPosition();
		double distance = sqrt(pow(pos.x - playerPos.x, 2) + pow(pos.y - playerPos.y, 2));
		if (distance <= 100.f)
		{
			// can pick up a beer
			if (window->isKeyPressed(GLFW_KEY_SPACE) && (now - pickupCooldown > .5f))
			{
				pickupDrink("champagne");
				pickupCooldown = now;
			}
		}
	}
}

void Player::pickupDrink(std::string drink)
{
	inventory[drink] += 1;
}

void::Player::clearPlayerInventory()
{
	inventory["beer"] = 0;
	inventory["wine"] = 0;
	inventory["liquor"] = 0;
	inventory["champagne"] = 0;
}

void Player::getPlayerInventory(s2d::Object* obj)
{
	obj->clear();
	float yOffset = 0.f;
	std::map<std::string, unsigned int>::iterator it;
	for (it = inventory.begin(); it != inventory.end(); it++)
	{
		s2d::Text* t = new s2d::Text();
		t->setPosition(glm::vec2(0, yOffset));
		t->text = it->first + ": " + std::to_string(it->second);
		t->color = glm::vec3(1.f);
		t->textScale = glm::vec2(.5f);
		obj->addChild(t);
		yOffset -= 20.f;
	}
}

glm::vec2 Player::calculateMovement(graphics::Window* window, float dt)
{
	float dx = 0.0f;
	float dy = 0.0f;

	if (window->isKeyPressed(GLFW_KEY_W) || window->isKeyPressed(GLFW_KEY_UP))
	{
		dy = speed * dt;
	}
	if (window->isKeyPressed(GLFW_KEY_S) || window->isKeyPressed(GLFW_KEY_DOWN))
	{
		dy = -speed * dt;
	}
	if (window->isKeyPressed(GLFW_KEY_D) || window->isKeyPressed(GLFW_KEY_RIGHT))
	{
		dx = speed * dt;
	}
	if (window->isKeyPressed(GLFW_KEY_A) || window->isKeyPressed(GLFW_KEY_LEFT))
	{
		dx = -speed * dt;
	}
	// TODO - change to speed * cos(theta); speed * sin(theta)
	return glm::vec2(dx, dy);

}

glm::vec2 Player::calculateCollision(glm::vec2 movement, std::vector<s2d::Object*> collideableEntities)
{
	for (s2d::Object* e : collideableEntities)
	{
		// x-axis collisions
		bool xCollision = sprite.getShiftedBoundingBox(movement.x, 0.0f).intersectsBounds(e->getBoundingBox());
		if (xCollision)
		{
			float dx = 0;
			while (abs(dx) < abs(movement.x))
			{
				bool xCollision = sprite.getShiftedBoundingBox(dx, 0.0f).intersectsBounds(e->getBoundingBox());
				if (xCollision)
				{
					//std::cout << "dx: " << dx << std::endl;
					if (movement.x > 0)
						movement.x = dx - 0.1f;
					if (movement.x < 0)
						movement.x = dx + 0.1f;
					break;
				}
				if (movement.x > 0)
				{
					dx += 0.1f;
				}
				else
				{
					dx -= 0.1f;
				}
			}
		}

		bool yCollision = sprite.getShiftedBoundingBox(0.0f, movement.y).intersectsBounds(e->getBoundingBox());
		if (yCollision)
		{
			float dy = 0;
			while (abs(dy) < abs(movement.y))
			{
				bool yCollision = sprite.getShiftedBoundingBox(0.0f, dy).intersectsBounds(e->getBoundingBox());
				if (yCollision)
				{
					if (movement.y > 0)
						movement.y = dy - 0.1f;
					if (movement.y < 0)
						movement.y = dy + 0.1f;
					break;
				}
				if (movement.y > 0)
				{
					dy += 0.1f;
				}
				else
				{
					dy -= 0.1f;
				}
			}
		}
	}
	return movement;
}
