#pragma once

#include "FruitConfigEntry.h"
#include <glm/glm.hpp>

class FruitObject
{
public:
	FruitObject(PFruitConfigEntry pFruitConfig);
	FruitObject(PFruitConfigEntry pFruitConfig, float xPos, float yPos);
	FruitObject(PFruitConfigEntry pFruitConfig, glm::vec2 pos);

	int getLevel();
	float getRadius();
	float getMass();
	float getElasticCoefficient();

	bool isDummy;
	glm::vec2 position;
	glm::vec2 velocity;
	glm::vec2 acceleration;
	float rotation;
	float angularVelocity;
	float radiusScale;
	float gameoverTimer;
private:
	PFruitConfigEntry fruitConfig;
};

