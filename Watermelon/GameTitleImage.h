#pragma once

#include "UIComponent.h"

class GameTitleImage : public UIComponent
{
public:
	GameTitleImage(float borderTop, float borderRight);
	int getTextureIndex();
	void autoSize(TextureManager* textureManager, float width = 0.3f);
};

