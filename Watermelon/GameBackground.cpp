#include "GameBackground.h"

GameBackground::GameBackground(float width, float height) : UIComponent()
{
	this->position = glm::vec2();
	this->scale = glm::vec2(width, height);
}

int GameBackground::getTextureIndex()
{
	return TEXTURE_ID_BACKGROUND;
}
