#pragma once

#define TEXTURE_ID_BACKGROUND -1
#define TEXTURE_ID_SCORE_TEXT -2
#define TEXTURE_ID_GAME_TITLE -3
#define TEXTURE_ID_DEAD_LINE  -4
#define TEXTURE_ID_BTN_PLAY   -5
#define TEXTURE_ID_BTN_RETRY  -6

struct Texture
{
	int index;
	const char* imageFilePath;
};

#define NUMBER_OF_SPECIAL_TEXTURES 3

const Texture SpecialTextures[] = {
	{ TEXTURE_ID_BACKGROUND, "./DefaultTexture/Background.png" },
	{ TEXTURE_ID_SCORE_TEXT, "./DefaultTexture/ScoreText.png" },
	{ TEXTURE_ID_DEAD_LINE, "./DefaultTexture/DeadLine.png" }
};
