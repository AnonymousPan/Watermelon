#include "TextureManager.h"

TextureManager::TextureManager(int capacity)
{
	this->capacity = capacity;
	this->textureGLObjects = (unsigned int*)malloc(capacity * sizeof(unsigned int));
	this->textureSizeList = (unsigned short*)malloc(capacity * 2 * sizeof(unsigned short));
	if (!this->textureGLObjects || !this->textureSizeList)
	{
		throw "TextureManager: malloc failed";
	}
	memset(this->textureGLObjects, 0, capacity * sizeof(unsigned int));
	memset(this->textureSizeList, 0, capacity * 2 * sizeof(unsigned short));
}

TextureManager::~TextureManager()
{
	if (this->textureGLObjects)
	{
		glDeleteTextures(this->capacity, this->textureGLObjects);
		free(this->textureGLObjects);
	}
	if (this->textureSizeList)
	{
		free(this->textureSizeList);
	}
}

unsigned int TextureManager::getTextureGLObject(int index)
{
	if (index < 0) index = this->capacity + index;
	if (index >= 0 && index < this->capacity)
	{
		return this->textureGLObjects[index];
	}
	else
	{
		return -1;
	}
}

void TextureManager::bindTexture(int index)
{
	if (index < 0) index = this->capacity + index;
	if (index >= 0 && index < this->capacity)
	{
		glBindTexture(GL_TEXTURE_2D, this->textureGLObjects[index]);
	}
}

bool TextureManager::getTextureSize(int index, unsigned short* width, unsigned short* height)
{
	if (index < 0) index = this->capacity + index;
	if (index >= 0 && index < this->capacity)
	{
		*width = this->textureSizeList[index * 2];
		*height = this->textureSizeList[index * 2 + 1];
		return true;
	}
	else
	{
		*width = 0;
		*height = 0;
		return false;
	}
}

void TextureManager::loadTexture(int index, const char* filename)
{
	if (index < 0) index = this->capacity + index;
	if (index < 0 || index >= this->capacity)
	{
		throw "Failed to load texture (invalid index)";
	}

	int width, height, channels;
	unsigned char* textureData = stbi_load(filename, &width, &height, &channels, 0);
	if (textureData == NULL)
	{
		throw "Failed to load texure";
	}
	
	int type;
	if (channels == 3)
	{
		type = GL_RGB;
	}
	else if (channels == 4)
	{
		type = GL_RGBA;
	}
	else
	{
		throw "Invalid texture (channels should be 3 or 4)";
	}

	if (width >= 65536 || height >= 65536)
	{
		throw "Texture is too large";
	}

	unsigned int glObj;
	glGenTextures(1, &glObj);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, glObj);
	glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, textureData);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(textureData);
	this->textureGLObjects[index] = glObj;
	this->textureSizeList[2 * index] = (unsigned short)width;
	this->textureSizeList[2 * index + 1] = (unsigned short)height;
}

void TextureManager::loadSpecialTextures()
{
	for (int i = 0; i < NUMBER_OF_SPECIAL_TEXTURES; i++)
	{
		this->loadTexture(SpecialTextures[i].index, SpecialTextures[i].imageFilePath);
	}
}
