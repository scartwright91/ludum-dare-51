#include "LevelParser.h"

LevelParser::LevelParser(std::string path, std::string worldName)
{
	this->worldName = worldName;
	ldtk_project.loadFromFile(path);
}

LevelParser::~LevelParser()
{

}

std::vector<std::string> LevelParser::getLevelNames()
{
    const auto& world = ldtk_project.getWorld(worldName);
    std::vector <std::string> levelNames = {};
    for (const auto& level : world.allLevels())
        levelNames.push_back(level.name);
    return levelNames;
}

void LevelParser::parseLevel(
    ResourceManager* resourceManager,
    s2d::Scene* scene,
    std::string levelName,
    Player* player,
    std::vector<s2d::Object*>* collideableEntities,
    std::map<unsigned int, s2d::Object*>* barMap,
    std::vector<s2d::Object*>* beerEntites,
    std::vector<s2d::Object*>* wineEntities,
    std::vector<s2d::Object*>* liquorEntities,
    std::vector<s2d::Object*>* champagneEntities,
    std::vector<glm::vec2>* crowdGrid
)
{
	// clear scene
    scene->clear();
    collideableEntities->clear();
    barMap->clear();
    crowdGrid->clear();

    // extract world and level
    const auto& world = ldtk_project.getWorld(worldName);
    const auto& level = world.getLevel(levelName);

    // extract grid size
    ldtk::IntPoint s = level.size;
    unsigned int gridX = (int)s.x / TILESIZE + 1;
    unsigned int gridY = (int)s.y / TILESIZE + 1;

    // create entities (including player)
    const auto& entities = level.getLayer("Entities");

    for (const ldtk::Entity& p : level.getLayer("Entities").getEntitiesByName("Player"))
    {
        ldtk::IntPoint playerPosition = p.getGridPosition();
        player->sprite.setPosition(
            glm::vec2(
                playerPosition.x * TILESIZE * SCALE,
                playerPosition.y * TILESIZE * SCALE
            )
        );
    }

    // collideable objects
    const auto& collide_layer = level.getLayer("Collideables");
    // iterate on the tiles of the layer
    unsigned int barNumber = 1;
    for (unsigned int x = 0; x < gridX; x++)
    {
        for (unsigned int y = 0; y < gridY; y++)
        {
            ldtk::IntGridValue gridValue = collide_layer.getIntGridVal(x, y);
            if (gridValue.value != -1)
            {
                s2d::Object* ent = new s2d::Object();
                ent->setPosition(glm::vec2(x * TILESIZE * SCALE, y * TILESIZE * SCALE));
                ent->size = glm::vec2(TILESIZE * SCALE, TILESIZE * SCALE);
                ent->alpha = 0.f;
                /*
                ent->setRenderLayer(s2d::SPRITE_LAYER);
                ent->color = glm::vec3(
                    (float)gridValue.color.r / 255,
                    (float)gridValue.color.g / 255,
                    (float)gridValue.color.b / 255
                );
                */
                if (gridValue.name == "Bar")
                {
                    // add text to bar to indicate order
                    s2d::Text* t = new s2d::Text();
                    t->setPosition(glm::vec2(0.f, 20.f));
                    t->text = std::to_string(barNumber);
                    t->textScale = glm::vec2(.5f);
                    t->setRenderLayer(s2d::SPRITE_LAYER);
                    ent->addChild(t);

                    // add bar
                    (*barMap)[barNumber] = ent;
                    barNumber++;

                }
                else if (gridValue.name == "Beer")
                {
                    beerEntites->push_back(ent);
                }
                else if (gridValue.name == "Wine")
                {
                    wineEntities->push_back(ent);
                }
                else if (gridValue.name == "Liquor")
                {
                    liquorEntities->push_back(ent);
                }
                else if (gridValue.name == "Champagne")
                {
                    champagneEntities->push_back(ent);
                }

                // add to scene and collideable entities
                scene->addChild(ent);
                collideableEntities->push_back(ent);
            }
        }
    }

    const auto& crowd_layer = level.getLayer("Crowd");

    for (unsigned int x = 0; x < gridX; x++)
    {
        for (unsigned int y = 0; y < gridY; y++)
        {
            ldtk::IntGridValue gridValue = crowd_layer.getIntGridVal(x, y);
            if (gridValue.value != -1)
            {
                glm::vec2 pos = glm::vec2(x * TILESIZE * SCALE, y * TILESIZE * SCALE);
                crowdGrid->push_back(pos);
            }
        }
    }

    // painting tiles
    const auto& tiles_layer = level.getLayer("Tiles");
    for (const auto& tile : tiles_layer.allTiles())
    {
        // extracting tile position
        ldtk::IntPoint gridPos = tile.getGridPosition();

        // extracting tilemap position
        ldtk::IntRect r = tile.getTextureRect();

        // create scene object
        s2d::Object* o = new s2d::Object();
        o->setPosition(glm::vec2(gridPos.x * TILESIZE * SCALE, gridPos.y * TILESIZE * SCALE));
        o->size = glm::vec2(TILESIZE * SCALE, TILESIZE * SCALE);
        o->setRenderLayer(s2d::SPRITE_BACKGROUND_LAYER);
        o->setTileMapTexture(
            resourceManager->getTexture("tileset").textureID,
            resourceManager->getTexture("tileset").width,
            resourceManager->getTexture("tileset").height,
            TILESIZE,
            r.x,
            r.y
        );
        scene->addChild(o);
    }

}
