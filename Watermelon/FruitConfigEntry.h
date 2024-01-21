#pragma once

typedef struct _tagFruitConfigEntry
{
	int level;
	const char* texturePath;
	float radius;
	float mass;
	float elasticCoefficient;
}
FruitConfigEntry, *PFruitConfigEntry;
