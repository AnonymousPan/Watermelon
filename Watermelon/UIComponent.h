#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "TextureManager.h"
#include "Color.h"

class UIComponent
{
public:
	UIComponent();
	virtual void render(TextureManager* textureManager);
	virtual int getTextureIndex() = 0;

	glm::vec2 position;
	glm::vec2 scale;
	ColorRGBA color;
};
