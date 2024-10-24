#include "GUITitle.h"

#include "GUIManager.h"

GUITitle::GUITitle(TextureManager* textureManager, float borderTop, float borderRight)
{
	this->gameTitleImage = new GameTitleImage(borderTop, borderRight);
	this->gameBackground = new GameBackground(borderRight, borderTop);
	this->gameTitleImage->autoSize(textureManager, 0.5f);

	this->startButton = new UIButton(0.0f, -0.2f, 0.5f, 0.5f, TEXTURE_ID_BTN_PLAY, UIButton::ButtonShape::Round);
	this->startButton->setOnClickCallback(this->startButtonOnClick);
}

GUITitle::~GUITitle()
{
	delete this->gameTitleImage;
	delete this->gameBackground;
	delete this->startButton;
}

void GUITitle::render(TextureManager* textureManager)
{
	this->gameBackground->render(textureManager);
	this->gameTitleImage->render(textureManager);
	this->startButton->render(textureManager);
}

void GUITitle::preRender(float dtFrame)
{
	this->startButton->preRender(dtFrame);
}

void GUITitle::onMouseDown(float x, float y)
{
	this->startButton->onMouseDown(x, y);
}

void GUITitle::onMouseUp(float x, float y)
{
	this->startButton->onMouseUp(x, y);
}

void GUITitle::onMouseMove(float x, float y)
{
	this->startButton->onMouseMove(x, y);
}

void GUITitle::startButtonOnClick()
{
	GUIManager::instance->switchToGUIWithID(GUI_ID_GAME_PLAY);
}
