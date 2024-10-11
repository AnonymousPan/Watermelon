#pragma once

#include "GUIObject.h"

#include "WatermelonGame.h"
#include "Render.h"

class GUIGamePlay : public GUIObject
{
public:
	GUIGamePlay(WatermelonGame* gameObj);
	void render(TextureManager* textureManager);
	void onMouseDown(float x, float y);
	void onMouseUp(float x, float y);
	void onMouseMove(float x, float y);

private:
	WatermelonGame* game;
};

