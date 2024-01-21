#include "FruitObject.h"

FruitObject::FruitObject(PFruitConfigEntry pFruitConfig)
	: FruitObject(pFruitConfig, glm::vec2())
{
}

FruitObject::FruitObject(PFruitConfigEntry pFruitConfig, float xPos, float yPos)
	: FruitObject(pFruitConfig, glm::vec2(xPos, yPos))
{
}

FruitObject::FruitObject(PFruitConfigEntry pFruitConfig, glm::vec2 pos)
{
	this->isDummy = false;
	this->fruitConfig = pFruitConfig;
	this->position = pos;
	this->velocity = glm::vec2();
	this->acceleration = glm::vec2();
	this->rotation = 0.0f;
	this->angularVelocity = 0.0f;
}

int FruitObject::getLevel()
{
	return this->fruitConfig->level;
}

float FruitObject::getRadius()
{
	return this->fruitConfig->radius;
}

float FruitObject::getMass()
{
	return this->fruitConfig->mass;
}

float FruitObject::getElasticCoefficient()
{
	return this->fruitConfig->elasticCoefficient;
}
