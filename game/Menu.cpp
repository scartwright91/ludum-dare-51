#include "Menu.h"


Menu::Menu(graphics::Window* window, ResourceManager* resourceManager, std::string menu)
{
	running = true;
	this->window = window;
	this->resourceManager = resourceManager;
	this->menu = menu;
	this->scene = new s2d::Scene(this->window, this->resourceManager);

	s2d::Text* menuText;
	if (menu == "start")
	{

		s2d::Text* gameText = new s2d::Text();
		gameText->text = "Two beers and a glass of wine";
		gameText->setPosition(glm::vec2(0, window->getHeight() - 100));
		gameText->color = glm::vec3(1.0f);
		gameText->textScale = glm::vec2(1.5f);

		s2d::Text* rulesText = new s2d::Text();
		rulesText->text = "Rules";
		rulesText->setPosition(glm::vec2(0, window->getHeight() - 300));
		rulesText->color = glm::vec3(1.0f);
		rulesText->textScale = glm::vec2(1.f);

		s2d::Text* movementText = new s2d::Text();
		movementText->text = "WASD or arrow keys to move";
		movementText->setPosition(glm::vec2(0, window->getHeight() - 350));
		movementText->color = glm::vec3(1.0f);
		movementText->textScale = glm::vec2(.5f);

		s2d::Text* spaceText = new s2d::Text();
		spaceText->text = "Press SPACE next to drinks to pick them up. Press SPACE next to bar to deliver drinks";
		spaceText->setPosition(glm::vec2(0, window->getHeight() - 400));
		spaceText->color = glm::vec3(1.0f);
		spaceText->textScale = glm::vec2(.5f);

		s2d::Text* failText = new s2d::Text();
		failText->text = "Survive until closing time to get to the next level, and don't let customers get too frustrated!";
		failText->setPosition(glm::vec2(0, window->getHeight() - 450));
		failText->color = glm::vec3(1.0f);
		failText->textScale = glm::vec2(.5f);

		s2d::Text* enterText = new s2d::Text();
		enterText->text = "Press ENTER to start serving drinks";
		enterText->setPosition(glm::vec2(0, window->getHeight() - 600));
		enterText->color = glm::vec3(0.0f, 1.0f, 0.0f);
		enterText->textScale = glm::vec2(1.f);

		scene->addChild(gameText);
		scene->addChild(rulesText);
		scene->addChild(movementText);
		scene->addChild(spaceText);
		scene->addChild(failText);
		scene->addChild(enterText);
	}
	else if (menu == "won")
	{
		menuText = new s2d::Text();
		menuText->text = "Congratulations!";
		menuText->setPosition(glm::vec2(0, window->getHeight() / 2));
		menuText->color = glm::vec3(1.0f);
		menuText->size = glm::vec2(2.0f);
	}
	else
	{
		s2d::Object* face = new s2d::Object();
		face->setPosition(glm::vec2(0.0f));
		face->size = glm::vec2(600, 400);
		face->setTexture(resourceManager->getTexture("menu_lose").textureID);
		face->setRenderLayer(s2d::SPRITE_LAYER);

		menuText = new s2d::Text();
		menuText->text = "You're fired";
		menuText->setPosition(glm::vec2(0, window->getHeight() / 2));
		menuText->color = glm::vec3(1.0f);
		menuText->size = glm::vec2(2.0f);

		scene->addChild(face);
		scene->addChild(menuText);
	}

}

Menu::~Menu()
{
	delete scene;
}

void Menu::run()
{
	events();
	update();
	render();
}

void Menu::events()
{
	if (menu == "start")
	{
		if (window->isKeyPressed(GLFW_KEY_ENTER))
			running = false;
	}
}

void Menu::update()
{
	scene->update();
}

void Menu::render()
{
	// clear screen and buffers
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	scene->render();
}
