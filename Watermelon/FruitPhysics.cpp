#include "FruitPhysics.h"

void tickFruits(WatermelonGame* game, float dt)
{
	for (FruitObject* fruit : game->fruitObjects)
	{
		if (!fruit->isDummy)
		{
			// Update acceleration by total force
			glm::vec2 totalForce = FruitPhysics::calcTotalForce(game, fruit);
			// a = F / m
			fruit->acceleration = totalForce / fruit->getMass();
		}
	}

	for (FruitObject* fruit : game->fruitObjects)
	{
		// Update velocity by acceleration
		fruit->velocity += fruit->acceleration * dt;

		// Test: velociy limit
		if (glm::length(fruit->velocity) > GameConfig::VelocityMax)
		{
			glm::vec2 v = glm::normalize(fruit->velocity);
			fruit->velocity = v * GameConfig::VelocityMax;
		}

		// Update position by velocity
		fruit->position += fruit->velocity * dt;

		// Test: acceleration limit
		if (glm::length(fruit->acceleration) > GameConfig::AccelerationMax)
		{
			glm::vec2 a = glm::normalize(fruit->acceleration);
			fruit->acceleration = a * GameConfig::AccelerationMax;
		}

		// Update fruit radius scale
		if (fruit->radiusScale < 1.0f)
		{
			fruit->radiusScale += GameConfig::RadiusScaleDelta * dt;
			if (fruit->radiusScale > 1.0f)
			{
				fruit->radiusScale = 1.0f;
			}
		}
	}
	/*
	// Update acceleration by total force
	glm::vec2 totalForce = FruitPhysics::calcTotalForce(game, fruit);
	// a = F / m
	fruit->acceleration = totalForce / fruit->getMass();

	// Update velocity by acceleration
	fruit->velocity += fruit->acceleration * dt;

	// Update position by velocity
	fruit->position += fruit->velocity * dt;
	*/

	bool showDDL;
	if (FruitPhysics::tickFruitGameoverTimer(game, dt, &showDDL))
	{
		game->gameover();
	}
	if (showDDL)
	{
		game->deadLine->show();
	}
	else
	{
		game->deadLine->hide();
	}
}

glm::vec2 FruitPhysics::calcTotalForce(WatermelonGame* game, FruitObject* fruit)
{
	glm::vec2 totalForce = FruitPhysics::calcForce_Gravity(game, fruit);
	totalForce += FruitPhysics::calcForce_ElasticFromBorder(game, fruit);
	totalForce += FruitPhysics::calcForce_ElasticFromFruit(game, fruit);
	// TODO: Other types of force

	return totalForce;
}

glm::vec2 FruitPhysics::calcForce_Gravity(WatermelonGame* game, FruitObject* fruit)
{
	// G = mg
	return glm::vec2(0.0f, -(fruit->getMass() * GameConfig::GravityAcceleration));
}

glm::vec2 FruitPhysics::calcForce_ElasticFromBorder(WatermelonGame* game, FruitObject* fruit)
{
	glm::vec2 force = glm::vec2();
	float elasticCoefficient = fruit->getElasticCoefficient();
	float radius = fruit->getRadius();
	float xPos = fruit->position.x;
	float yPos = fruit->position.y;
	glm::vec2 velocity = fruit->velocity;
	float overlapping, value;
	// Top border is not considered

	// Left border
	overlapping = game->borderLeft - (xPos - radius);
	if (overlapping > 0)
	{
		value = overlapping * elasticCoefficient;
		if (velocity.x > 0) value *= 0.25f;
		force += glm::vec2(value, 0.0f);
	}

	// Bottom border
	overlapping = game->borderBottom - (yPos - radius);
	if (overlapping > 0)
	{
		value = overlapping * elasticCoefficient;
		if (velocity.y > 0)value *= 0.25f;
		force += glm::vec2(0.0f, value);
	}

	// Right border
	overlapping = (xPos + radius) - game->borderRight;
	if (overlapping > 0)
	{
		value = overlapping * elasticCoefficient;
		if (velocity.x < 0) value *= 0.25f;
		force += glm::vec2(-value, 0.0f);
	}

	return force;
}

glm::vec2 FruitPhysics::calcForce_ElasticFromFruit(WatermelonGame* game, FruitObject* fruit)
{
	glm::vec2 force = glm::vec2();
	std::vector<FruitObject*>::iterator ite = game->fruitObjects.begin();
	for (; ite != game->fruitObjects.end(); ite++)
	{
		FruitObject* targetFruit = *ite;
		if (targetFruit != fruit && !targetFruit->isDummy)
		{
			glm::vec2 distanceVec = fruit->position - targetFruit->position;
			float distance = glm::length(distanceVec);
			float radiusThis = fruit->getRadius();
			float radiusTarget = targetFruit->getRadius();
			if (distance < radiusThis + radiusTarget)
			{
				float overlapping = radiusThis + radiusTarget - distance;
				float value = (fruit->getElasticCoefficient() + targetFruit->getElasticCoefficient()) / 2.0f * overlapping;
				if (glm::dot(fruit->velocity, distanceVec) > 0)
				{
					value *= 0.25f;
				}
				glm::vec2 singleForce = -glm::vec2(distanceVec);
				glm::normalize(singleForce);
				force += glm::normalize(distanceVec) * value;
			}
		}
	}
	return force;
}

void FruitPhysics::checkFruitMerge(WatermelonGame* game)
{
	bool needToCheckAgain = false;
	do
	{
		needToCheckAgain = false;
		int len = (int)game->fruitObjects.size();
		for (int i = 0; i < len - 1; i++)
		{
			FruitObject* fruitA = game->fruitObjects[i];
			if (!fruitA->isDummy && fruitA->getLevel() < GameConfig::MaxFruitLevel)
			{
				for (int j = i + 1; j < len; j++)
				{
					FruitObject* fruitB = game->fruitObjects[j];
					if (!fruitB->isDummy && fruitA->getLevel() == fruitB->getLevel())
					{
						float distance = glm::length(fruitA->position - fruitB->position);
						distance -= fruitA->getRadius() + fruitB->getRadius();
						if (distance <= GameConfig::MergingDistance)
						{
							FruitPhysics::mergeFruit(game, fruitA, fruitB);
							needToCheckAgain = true;
							break;
						}
					}
				}
				if (needToCheckAgain) break;
			}
		}
	} while (needToCheckAgain);
}

FruitObject* FruitPhysics::mergeFruit(WatermelonGame* game, FruitObject* fruitA, FruitObject* fruitB)
{
	glm::vec2 newFruitPos = fruitB->position + (fruitA->position - fruitB->position) / 2.0f;
	FruitObject* newFruit = game->createFruitAt(fruitA->getLevel() + 1, newFruitPos);
	newFruit->radiusScale = GameConfig::RadiusScaleAfterMerge;
	game->score += fruitA->getLevel();
	game->destroyFruit(fruitA);
	game->destroyFruit(fruitB);
	return newFruit;
}

/// <summary>
/// Ticks the gameover timer of fruits and check whether the game is over
/// </summary>
/// <param name="game">Game object</param>
/// <param name="dt">Delta time</param>
/// <returns>Boolean indicates whether the game is over</returns>
bool FruitPhysics::tickFruitGameoverTimer(WatermelonGame* game, float dt, bool* showDeadline)
{
	bool result = false;
	bool showDDL = false;
	float deadlineYPos = game->borderTop - GameConfig::DeadLineToTop;
	float deadlineShowingYPos = deadlineYPos - GameConfig::DeadLineShowingDistance;
	for (FruitObject* fruit : game->fruitObjects)
	{
		if (!fruit->isDummy)
		{
			float fruitTop = fruit->position.y + fruit->getRadius();
			if (fruitTop >= deadlineYPos)
			{
				fruit->gameoverTimer += dt;
			}
			else
			{
				fruit->gameoverTimer -= dt;
				if (fruit->gameoverTimer < 0) fruit->gameoverTimer = 0.0f;
			}
			if (fruitTop >= deadlineShowingYPos && glm::length(fruit->velocity) <= 2.0f)
			{
				showDDL = true;
			}
			if (fruit->gameoverTimer >= GameConfig::GameoverTimerMax)
			{
				result = true;
			}
		}
	}
	*showDeadline = showDDL;
	return result;
}
