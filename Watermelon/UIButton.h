#pragma once

#include "UIComponent.h"

#define UI_BUTTON_MOUSE_DOWN_TIMER_SCALER 10.0f

class UIButton : public UIComponent
{
public:
	typedef void (*OnClickCallback)(void);
	enum ButtonShape
	{
		Rectangle,
		Round
	};

	UIButton(float x, float y, float width, float height, int textureIndex, ButtonShape btnShape);
	~UIButton();
	int getTextureIndex();
	void setOnClickCallback(OnClickCallback onClick);
	void preRender(float dt);
	void onMouseDown(float x, float y);
	void onMouseUp(float x, float y);
	void onMouseMove(float x, float y);
	
private:
	bool isMouseInBound(float x, float y);

	OnClickCallback onClickCallback;
	int textureIndex;
	ButtonShape shape;
	bool isMouseOver;
	bool isMouseDown;
	// Indicates the time mouse pressed, max = 1.0f
	float mouseDownTimer;
	float originalScaleX;
	float originalScaleY;
};

