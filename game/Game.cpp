#include "Game.h"

Game::Game(graphics::Window* window, ResourceManager* resouceManager) : 
    player(64.f, 64, resouceManager->getTexture("player").textureID),
    levelParser("res/levels/test.ldtk", ""),
    secondsRemaining(60.f)
{
    this->window = window;
    this->resourceManager = resouceManager;
   
    // create first level
    createLevel();

}

Game::~Game()
{
    delete fps;
    delete orderTimer;
    delete scene;
    delete pg;
    delete crowd;
}

void Game::run(Clock* clock)
{
    events();
    update(clock->deltaTime);
    render();
}

void Game::events()
{

}

void Game::update(float dt)
{
    // change level logic
    secondsRemaining -= dt;
    if (secondsRemaining <= 0)
    {
        if (level == 2)
        {
            running = false;
            won = true;
            return;
        }
        secondsRemaining = levelDuration;
        level++;
        createLevel();
    }

    // customer frustration logic
    if (orderManager->orders.size() > 1)
        customerFrustration += ((orderManager->orders.size() - 1) * dt);

    if (customerFrustration >= 100.f)
    {
        running = false;
        return;
    }

    // update game logic
    player.update(
        dt,
        window,
        collideableEntities,
        beerEntities,
        wineEntities,
        liquorEntities,
        champagneEntities
    );
    scene->update();
    orderManager->update(dt, &player, barMap);

    // update crowd
    crowd->update(customerFrustration);

    // hud updating
    fps->text = std::to_string((int)floor(1 / dt));
    orderTimer->text = "Next order: " + std::to_string((int)orderManager->orderTimer);
    closingTime->text = "Closing time: " + std::to_string((int)secondsRemaining);
    customerFrustrationHUD->text = "Customer frustration: " + std::to_string((int)customerFrustration);

    // hacky way of updating inventory
    scene->removeChild(inventory);
    player.getPlayerInventory(inventory);
    scene->addChild(inventory);
}

void Game::render()
{
    // clear screen and buffers
    glClearColor(0.f, 0.f, 0.f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // scene render
    scene->render();
}

void Game::createLevel()
{

    // create scene
    scene = new s2d::Scene(this->window, this->resourceManager);
    orderManager = new OrderManager(scene, soundEngine, level);
    player.clearPlayerInventory();

    // create new level
    levelParser.parseLevel(
        resourceManager,
        scene,
        "Level_" + std::to_string(level),
        &player,
        &collideableEntities,
        &barMap,
        &beerEntities,
        &wineEntities,
        &liquorEntities,
        &champagneEntities,
        &crowdGrid
    );

    // create crowd
    crowd = new Crowd(scene, resourceManager, crowdGrid, 100);

    // set camera target
    scene->addChild(&player.sprite);
    scene->camera->setTarget(&player.sprite, false);

    // add fps text
    fps = new s2d::Text();
    fps->setPosition(glm::vec2(0, window->getHeight() - 40));
    fps->color = glm::vec3(1.0f);
    fps->text = "";
    scene->addChild(fps);

    // order timer
    orderTimer = new s2d::Text();
    orderTimer->setPosition(glm::vec2(100, window->getHeight() - 40));
    orderTimer->color = glm::vec3(1.0f);
    orderTimer->text = "";
    orderTimer->textScale = glm::vec2(.5f);
    scene->addChild(orderTimer);

    // inventory text
    inventory = new s2d::Object();
    inventory->setPosition(glm::vec2(250, window->getHeight() - 40));
    inventory->setRenderLayer(s2d::HUD_LAYER);
    scene->addChild(inventory);

    // closing time
    closingTime = new s2d::Text();
    closingTime->setPosition(glm::vec2(400, window->getHeight() - 40));
    closingTime->color = glm::vec3(1.0f);
    closingTime->text = "";
    closingTime->textScale = glm::vec2(.5f);
    scene->addChild(closingTime);

    // customer frustration
    customerFrustrationHUD = new s2d::Text();
    customerFrustrationHUD->setPosition(glm::vec2(700, window->getHeight() - 40));
    customerFrustrationHUD->color = glm::vec3(1.0f, 0.0f, 0.0f);
    customerFrustrationHUD->text = "";
    customerFrustrationHUD->textScale = glm::vec2(.5f);
    scene->addChild(customerFrustrationHUD);

}
