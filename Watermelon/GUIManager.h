#pragma once

#include "GUIObject.h"
#include "TextureManager.h"

#define GUI_MANAGER_CAPACITY 16

#define GUI_ID_NONE -1

#define GUI_ID_TITLE 1
#define GUI_ID_GAME_PLAY 2

class GUIManager
{
public:
	static GUIManager* instance;
	static bool init();

	GUIManager();
	~GUIManager();

	void render(TextureManager* textureManager);
	void preRender(float dtFrame);
	void onMouseDown(float x, float y);
	void onMouseUp(float x, float y);
	void onMouseMove(float x, float y);

	GUIObject* getCurrentGUI();
	int registerGUI(GUIObject* gui, int id = GUI_ID_NONE);
	bool unregisterGUI(int index);
	bool switchToGUIWithIndex(int index);
	bool switchToGUIWithID(int id);

private:
	struct RegisteredGUI
	{
		GUIObject* gui;
		int id;
	};

	int currentGUIIndex;
	RegisteredGUI* registeredGUIs;
};

