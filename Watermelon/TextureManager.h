#pragma once

#include <concrt.h>
#include <glad/glad.h>
#include "stb_image.h"

class TextureManager
{
public:
	TextureManager(int capacity);
	~TextureManager();
	void loadTexture(int index, const char* filename);
	unsigned int getTextureGLObject(int index);
	void bindTexture(int index);
private:
	int capacity;
	unsigned int* textureGLObjects;
};

