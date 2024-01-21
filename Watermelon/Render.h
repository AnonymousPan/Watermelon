#pragma once

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "WatermelonGame.h"
#include "FruitObject.h"
#include "VertexData.h"
#include "TextureManager.h"

GLFWwindow* renderInit(int width, int height, const char* title);

bool initializeGlfw();
bool initializeGlad();
GLFWwindow* glCreateWindow(int width, int height, const char* title);

namespace Render
{
	extern unsigned int glObject_FruitShaderProgram;
	extern unsigned int glObject_FruitVertexBuffer;
	extern unsigned int glObject_FruitVertexArray;

	extern unsigned int glUniformLocation_FruitTrans;
	extern unsigned int glUniformLocation_FruitColor;

	bool loadShaderFromFile(unsigned int* shaderObject, GLenum type, const char* filename);
	bool loadShaderProgram(
		unsigned int* programObject,
		const char* vertexShaderFilename,
		const char* fragmentShaderFilename,
		const char* geometryShaderFilename);

	bool initializeBuffers();
	bool initializeShaders();

	void clearBackground();

	void renderFruitObject(TextureManager* textureManager, FruitObject* fruit);
};
