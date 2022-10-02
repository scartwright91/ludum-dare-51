#pragma once

#include <string>
#include <vector>

#include "../src/LDtkLoader/Project.h"
#include "../ResourceManager.h"
#include "../src/s2d/Object.h"
#include "../src/s2d/Scene.h"

#include "Player.h"



class LevelParser
{

public:
	LevelParser(std::string path, std::string worldName);
	~LevelParser();

	std::vector<std::string> getLevelNames();
	void parseLevel(
		ResourceManager* resourceManager,
		s2d::Scene* scene,
		std::string level,
		Player* player,
		std::vector<s2d::Object*>* collideableEntities,
		std::map<unsigned int, s2d::Object*>* barMap,
		std::vector<s2d::Object*>* beerEntities,
		std::vector<s2d::Object*>* wineEntities,
		std::vector<s2d::Object*>* liquorEntities,
		std::vector<s2d::Object*>* champagneEntities,
		std::vector<glm::vec2>* crowdGrid
	);

private:

	float TILESIZE = 32.f;
	float SCALE = 2.f;
	unsigned int GRID_X = 20;
	unsigned int GRID_Y = 14;

	std::string worldName;
	ldtk::Project ldtk_project;

};

