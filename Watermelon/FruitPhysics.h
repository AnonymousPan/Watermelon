#pragma once

#include <glm/glm.hpp>

#include "WatermelonGame.h"
#include "FruitObject.h"

class WatermelonGame;

void tickFruits(WatermelonGame* game, float dt);

namespace FruitPhysics
{
	glm::vec2 calcTotalForce(WatermelonGame* game, FruitObject* fruit);
	glm::vec2 calcForce_Gravity(WatermelonGame* game, FruitObject* fruit);
	glm::vec2 calcForce_ElasticFromBorder(WatermelonGame* game, FruitObject* fruit);
	glm::vec2 calcForce_ElasticFromFruit(WatermelonGame* game, FruitObject* fruit);
	glm::vec2 calcForce_FrictionFromBorder(WatermelonGame* game, FruitObject* fruit);
	glm::vec2 calcForce_FrictionFromFruit(WatermelonGame* game, FruitObject* fruit);
	void checkFruitMerge(WatermelonGame* game);
	FruitObject* mergeFruit(WatermelonGame* game, FruitObject* fruitA, FruitObject* fruitB);
	bool tickFruitGameoverTimer(WatermelonGame* game, float dt, bool* showDeadline);
}