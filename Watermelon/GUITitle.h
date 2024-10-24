#pragma once

#include "GUIObject.h"

#include "GameBackground.h"
#include "GameTitleImage.h"
#include "UIButton.h"

class GUITitle : public GUIObject
{
public:
	GUITitle(TextureManager* textureManager, float borderTop, float borderRight);
	~GUITitle();
	void render(TextureManager* textureManager);
	void preRender(float dtFrame);
	void onMouseDown(float x, float y);
	void onMouseUp(float x, float y);
	void onMouseMove(float x, float y);

private:
	GameTitleImage* gameTitleImage;
	GameBackground* gameBackground;
	UIButton* startButton;

	static void startButtonOnClick();
};

