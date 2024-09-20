#pragma once

#include "UIComponent.h"

class DeadLine : public UIComponent
{
public:
	DeadLine(float yPos, float width, float height);
	int getTextureIndex();
	void tick(float dt);
	void show();
	void hide();
	void render(TextureManager* textureManager);

private:
	bool visible;
	float renderStage;
};
