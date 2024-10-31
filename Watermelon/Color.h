#pragma once

struct ColorRGBA
{
	float r;
	float g;
	float b;
	float a;
};

struct ColorRGB
{
	float r;
	float g;
	float b;
};

// Color const
#define COLOR_TRANSPARENT { 0.0f, 0.0f, 0.0f, 0.0f };
#define COLOR_SOLID_WHITE { 1.0f, 1.0f, 1.0f, 1.0f };
