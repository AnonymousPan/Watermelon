#include "WatermelonGame.h"

WatermelonGame::WatermelonGame()
{
	this->windowWidth = GameConfig::GameWindowWidth;
	this->windowHeight = GameConfig::GameWindowHeight;
	this->windowTitle = "Watermelon";
	this->gameWindow = nullptr;
	this->textureManager = new TextureManager(32);
	this->calcBorder();
	this->currentTickTime = 0.0f;
	this->previousTickTime = 0.0f;
	this->movingDummyFruit = false;
	this->dummyFruitCooldown = -1.0f;
	this->currentDummyFruit = nullptr;
	this->score = 0;
	this->gameoverFlag = false;

	this->gameBackground = new GameBackground(this->borderRight, this->borderTop);
	this->deadLine = new DeadLine(this->borderTop - GameConfig::DeadLineToTop, this->borderRight, 0.01f);
}

WatermelonGame::~WatermelonGame()
{
	delete(this->textureManager);
	delete(this->gameBackground);
	delete(this->deadLine);
}

bool WatermelonGame::init()
{
	srand((unsigned int)time(0));
	GLFWwindow* glWindow = renderInit(
		this->windowWidth,
		this->windowHeight,
		this->windowTitle);
	if (glWindow == NULL) return false;
	this->gameWindow = glWindow;
	this->loadTexture();

	this->currentTickTime = (float)glfwGetTime();
	this->previousTickTime = this->currentTickTime;

	this->createDummyFruit();

	return true;
}

bool WatermelonGame::gameShouldExit()
{
	return glfwWindowShouldClose(this->gameWindow);
}

void WatermelonGame::startMovingDummyFruit()
{
	this->movingDummyFruit = true;
}

void WatermelonGame::endMovingDummyFruit()
{
	if (this->movingDummyFruit)
	{
		this->dropDummyFruit();
	}
	this->movingDummyFruit = false;
}

void WatermelonGame::moveDummyFruit(float mouseX)
{
	if (this->movingDummyFruit && this->currentDummyFruit != nullptr)
	{
		this->currentDummyFruit->position.x = this->clampDummyFruitXPos(mouseX);
	}
}

void WatermelonGame::tick()
{
	this->previousTickTime = this->currentTickTime;
	this->currentTickTime = (float)glfwGetTime();
	float dt = this->currentTickTime - this->previousTickTime;

	if (!this->gameoverFlag)this->doTick(dt);
}

void WatermelonGame::exit()
{
	glfwTerminate();
}

void WatermelonGame::gameover()
{
	if (!this->gameoverFlag)
	{
		this->gameoverFlag = true;
		// TODO: A better gameover GUI
		MessageBoxA(NULL, "Game over!", "Watermelon", MB_ICONWARNING | MB_OK);
		this->resetGame();
	}
}

void WatermelonGame::resetGame()
{
	// Clear fruits
	for (FruitObject* fruit : this->fruitObjects)
	{
		delete fruit;
	}
	this->fruitObjects.clear();

	this->score = 0;
	this->gameoverFlag = false;

	this->createDummyFruit();
}

FruitObject* WatermelonGame::createFruitAt(int level, float x, float y)
{
	return this->createFruitAt((PFruitConfigEntry)&FruitConfigArray[level - 1], x, y);
}

FruitObject* WatermelonGame::createFruitAt(int level, glm::vec2 pos)
{
	return this->createFruitAt((PFruitConfigEntry)&FruitConfigArray[level - 1], pos);
}

FruitObject* WatermelonGame::createFruitAt(PFruitConfigEntry pFruitConfig, float x, float y)
{
	FruitObject* fruit = new FruitObject(pFruitConfig, x, y);
	this->fruitObjects.push_back(fruit);
	return fruit;
}

FruitObject* WatermelonGame::createFruitAt(PFruitConfigEntry pFruitConfig, glm::vec2 pos)
{
	FruitObject* fruit = new FruitObject(pFruitConfig, pos);
	this->fruitObjects.push_back(fruit);
	return fruit;
}

void WatermelonGame::destroyFruit(FruitObject* fruit)
{
	auto ite = this->fruitObjects.begin();
	for (; ite != this->fruitObjects.end(); ite++)
	{
		if ((*ite) == fruit)
		{
			this->fruitObjects.erase(ite);
			delete fruit;
			return;
		}
	}
}

void WatermelonGame::loadTexture()
{
	for (int i = 0; i < 11; i++)
	{
		this->textureManager->loadTexture(i, FruitConfigArray[i].texturePath);
	}
	this->textureManager->loadSpecialTextures();
}

void WatermelonGame::calcBorder()
{
	if (this->windowHeight >= this->windowWidth)
	{
		// Vertical or square window
		this->borderTop = 1.0f;
		this->borderBottom = -1.0f;
		float lrBorder = static_cast<float>(this->windowWidth) / this->windowHeight;
		this->borderLeft = -lrBorder;
		this->borderRight = lrBorder;
	}
	else
	{
		// Horizontal window
		this->borderLeft = -1.0f;
		this->borderRight = 1.0f;
		float tbBorder = static_cast<float>(this->windowHeight) / this->windowWidth;
		this->borderTop = tbBorder;
		this->borderBottom = -tbBorder;
	}
}

void WatermelonGame::doTick(float dt)
{
	this->deadLine->tick(dt);
	
	float standardTickDT = 0.0005f;
	int ticks = (int)(dt / standardTickDT);
	for (int i = 0; i < ticks; i++)
	{
		tickFruits(this, standardTickDT);
	}

	float remainDT = dt - standardTickDT * ticks;
	tickFruits(this, remainDT);

	FruitPhysics::checkFruitMerge(this);

	if (this->dummyFruitCooldown >= 0)
	{
		if (this->dummyFruitCooldown - dt < 0)
		{
			this->createDummyFruit();
			this->dummyFruitCooldown = -1.0f;
		}
		else
		{
			this->dummyFruitCooldown -= dt;
		}
	}
}

float WatermelonGame::clampDummyFruitXPos(float value)
{
	if (currentDummyFruit == nullptr) return 0.0f;
	float xMin = this->borderLeft + this->currentDummyFruit->getRadius();
	if (value < xMin) return xMin;
	float xMax = this->borderRight - this->currentDummyFruit->getRadius();
	if (value > xMax) return xMax;
	return value;
}

void WatermelonGame::createDummyFruit()
{
	int level = rand() % (GameConfig::MaxLevelOfRandomGeneration) + 1;
	FruitObject* fruit = this->createFruitAt(level, 0.0f, this->borderTop - 0.1f);
	fruit->isDummy = true;
	this->currentDummyFruit = fruit;
}

void WatermelonGame::dropDummyFruit()
{
	if (this->currentDummyFruit != nullptr)
	{
		this->currentDummyFruit->isDummy = false;
		this->currentDummyFruit = nullptr;
		this->dummyFruitCooldown = GameConfig::DymmyFruitGenerationCooldown;
	}
}
