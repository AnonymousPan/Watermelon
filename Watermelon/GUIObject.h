#pragma once

#include "TextureManager.h"

class GUIObject
{
public:
	virtual void render(TextureManager* textureManager) = 0;
	/// <summary>
	/// Called before render() to process updates (e.g. animations)
	/// </summary>
	/// <param name="dtFrame">Delta time (in seconds) from last frame</param>
	virtual void preRender(float dtFrame) {}
	virtual void onMouseDown(float x, float y) {}
	virtual void onMouseUp(float x, float y) {}
	virtual void onMouseMove(float x, float y) {}
};

