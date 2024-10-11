#include "GUIGamePlay.h"

GUIGamePlay::GUIGamePlay(WatermelonGame* gameObj)
{
	this->game = gameObj;
}

void GUIGamePlay::render(TextureManager* textureManager)
{
	Render::clearBackground();

	game->gameBackground->render(textureManager);

	for (FruitObject* fruit : game->fruitObjects)
	{
		Render::renderFruitObject(textureManager, fruit);
	}

	Render::renderScoreText(textureManager, game->borderLeft + 0.05f, game->borderTop - 0.05f, 0.1f, game->score);

	game->deadLine->render(textureManager);
}

void GUIGamePlay::onMouseDown(float x, float y)
{
	game->startMovingDummyFruit();
}

void GUIGamePlay::onMouseUp(float x, float y)
{
	game->endMovingDummyFruit();
}

void GUIGamePlay::onMouseMove(float x, float y)
{
	game->moveDummyFruit(x);
}
