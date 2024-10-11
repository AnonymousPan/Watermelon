#pragma once

#include "TextureManager.h"

class GUIObject
{
public:
	virtual void render(TextureManager* textureManager) = 0;
	virtual void onMouseDown(float x, float y) = 0;
	virtual void onMouseUp(float x, float y) = 0;
	virtual void onMouseMove(float x, float y) = 0;
};

