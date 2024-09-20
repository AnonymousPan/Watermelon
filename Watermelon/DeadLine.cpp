#include "DeadLine.h"

#include "GameConfig.h"

DeadLine::DeadLine(float yPos, float width, float height) : UIComponent()
{
	this->position = glm::vec2(0, yPos);
	this->scale = glm::vec2(width, height);
	this->visible = false;
	this->renderStage = 0.0f;
}

int DeadLine::getTextureIndex()
{
	return TEXTURE_ID_DEAD_LINE;
}

void DeadLine::tick(float dt)
{
	if (this->visible)
	{
		this->color.a = 0.5f - glm::cos(this->renderStage * GameConfig::DeadLineBlinkingSpeed) / 2.0f;
		this->renderStage += dt;
	}
}

void DeadLine::show()
{
	this->visible = true;
}

void DeadLine::hide()
{
	this->visible = false;
	this->renderStage = 0.0f;
}

void DeadLine::render(TextureManager* textureManager)
{
	if (this->visible)
	{
		this->UIComponent::render(textureManager);
	}
}
