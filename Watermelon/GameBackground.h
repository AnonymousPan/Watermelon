#pragma once
#include "UIComponent.h"

class GameBackground : public UIComponent
{
public:
	GameBackground(float width, float height);
	int getTextureIndex();
};

