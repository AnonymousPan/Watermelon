#pragma once

#include <time.h>
#include <vector>

#include <Windows.h>

#include "Render.h"
#include "TextureManager.h"
#include "FruitObject.h"
#include "GameConfig.h"
#include "FruitPhysics.h"

#include "GameBackground.h"
#include "DeadLine.h"

class WatermelonGame
{
public:
	WatermelonGame();
	~WatermelonGame();
	bool init();
	bool gameShouldExit();
	void gameLoop();
	void exit();
	void cursorPosCallback(double x, double y);
	void gameover();

	FruitObject* createFruitAt(int level, float x, float y);
	FruitObject* createFruitAt(int level, glm::vec2 pos);
	FruitObject* createFruitAt(PFruitConfigEntry pFruitConfig, float x, float y);
	FruitObject* createFruitAt(PFruitConfigEntry pFruitConfig, glm::vec2 pos);
	void destroyFruit(FruitObject* fruit);

	int windowWidth, windowHeight;
	const char* windowTitle;
	GLFWwindow* gameWindow;
	TextureManager* textureManager;
	float currentTickTime, previousTickTime;
	float borderLeft, borderRight, borderBottom, borderTop;
	std::vector<FruitObject*> fruitObjects;
	int score;

	GameBackground* gameBackground;
	DeadLine* deadLine;

private:
	void loadTexture();
	void calcBorder();
	void doRender();
	void doTick(float dt);
	void processInput();

	float clampDummyFruitXPos(float value);
	void createDummyFruit();
	void dropDummyFruit();	

	bool gameoverFlag;

	bool movingDummyFruit;
	float dummyFruitCooldown;
	FruitObject* currentDummyFruit;
};

