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
	extern unsigned int glObject_ScoreTextShaderProgram;
	extern unsigned int glObject_ScoreTextVertexBuffer;
	extern unsigned int glObject_ScoreTextVertexArray;

	extern unsigned int glUniformLocation_FruitTrans;
	extern unsigned int glUniformLocation_FruitColor;
	extern unsigned int glUniformLocation_ScoreTextTrans;
	extern unsigned int glUniformLocation_ScoreTextNumberIndex;

	bool loadShaderFromFile(unsigned int* shaderObject, GLenum type, const char* filename);
	bool loadShaderProgram(
		unsigned int* programObject,
		const char* vertexShaderFilename,
		const char* fragmentShaderFilename,
		const char* geometryShaderFilename);

	bool initializeBuffers();
	bool initializeShaders();
	void getUniformLocations();

	void clearBackground();

	void renderFruitObject(TextureManager* textureManager, FruitObject* fruit);
	void renderScoreText(TextureManager* textureManager, float x, float y, float textSize, int score);
	void renderScoreTextDigit(float x, float y, float textSize, int digit);
};
