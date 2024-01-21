#pragma once

#include "FruitConfigEntry.h"

namespace GameConfig
{
	const int MaxFruitLevel = 11;
	const float GravityAcceleration = 10.0f;
	const float DefaultFruitElasticCoefficient = 1000.0f;
	const int MaxLevelOfRandomGeneration = 5;
	const float DymmyFruitGenerationCooldown = 0.1f;
	const float MergingDistance = 0.025f;
}

// Grape
const FruitConfigEntry FruitConfig_1 = {
	1,
	"./DefaultTexture/0.png",
	0.052f,
	0.001f,
	GameConfig::DefaultFruitElasticCoefficient
};

// Strawberry(?)
const FruitConfigEntry FruitConfig_2 = {
	2,
	"./DefaultTexture/1.png",
	0.080f,
	0.002f,
	GameConfig::DefaultFruitElasticCoefficient
};

// Orange
const FruitConfigEntry FruitConfig_3 = {
	3,
	"./DefaultTexture/2.png",
	0.096f,
	0.004f,
	GameConfig::DefaultFruitElasticCoefficient
};

// Lemon
const FruitConfigEntry FruitConfig_4 = {
	4,
	"./DefaultTexture/3.png",
	0.119f,
	0.008f,
	GameConfig::DefaultFruitElasticCoefficient
};

// Kiwi
const FruitConfigEntry FruitConfig_5 = {
	5,
	"./DefaultTexture/4.png",
	0.153f,
	0.016f,
	GameConfig::DefaultFruitElasticCoefficient
};

// Tomato
const FruitConfigEntry FruitConfig_6 = {
	6,
	"./DefaultTexture/5.png",
	0.183f,
	0.032f,
	GameConfig::DefaultFruitElasticCoefficient
};

// Peach
const FruitConfigEntry FruitConfig_7 = {
	7,
	"./DefaultTexture/6.png",
	0.220f,
	0.064f,
	GameConfig::DefaultFruitElasticCoefficient
};

// Pineapple
const FruitConfigEntry FruitConfig_8 = {
	8,
	"./DefaultTexture/7.png",
	0.240f,
	0.128f,
	GameConfig::DefaultFruitElasticCoefficient
};

// Coconut
const FruitConfigEntry FruitConfig_9 = {
	9,
	"./DefaultTexture/8.png",
	0.255f,
	0.256f,
	GameConfig::DefaultFruitElasticCoefficient
};

// Half watermelon
const FruitConfigEntry FruitConfig_10 = {
	10,
	"./DefaultTexture/9.png",
	0.308f,
	0.512f,
	GameConfig::DefaultFruitElasticCoefficient
};

// Whole watermelon
const FruitConfigEntry FruitConfig_11 = {
	11,
	"./DefaultTexture/10.png",
	0.408f,
	1.024f,
	GameConfig::DefaultFruitElasticCoefficient
};

const FruitConfigEntry FruitConfigArray[] = {
	FruitConfig_1,
	FruitConfig_2,
	FruitConfig_3,
	FruitConfig_4,
	FruitConfig_5,
	FruitConfig_6,
	FruitConfig_7,
	FruitConfig_8,
	FruitConfig_9,
	FruitConfig_10,
	FruitConfig_11
};
