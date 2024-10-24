#include "UIButton.h"

UIButton::UIButton(float x, float y, float width, float height, int textureIndex, ButtonShape btnShape)
{
	this->position = glm::vec2(x, y);
	this->shape = btnShape;
	switch (btnShape)
	{
	case UIButton::Rectangle:
		this->scale = glm::vec2(width / 2, height / 2);
		break;
	case UIButton::Round:
		this->scale = glm::vec2(width / 2, width / 2);
		break;
	default:
		throw "Invalid button shape";
	}
	this->isMouseOver = false;
	this->isMouseDown = false;
	this->mouseDownTimer = 0.0f;
	this->onClickCallback = nullptr;
	this->textureIndex = textureIndex;
	this->originalScaleX = this->scale.x;
	this->originalScaleY = this->scale.y;
}

UIButton::~UIButton()
{
}

int UIButton::getTextureIndex()
{
	return this->textureIndex;
}

void UIButton::setOnClickCallback(OnClickCallback onClick)
{
	this->onClickCallback = onClick;
}

void UIButton::preRender(float dt)
{
	if (this->isMouseDown)
	{
		this->mouseDownTimer = glm::clamp(this->mouseDownTimer + dt * UI_BUTTON_MOUSE_DOWN_TIMER_SCALER, 0.0f, 1.0f);
	}
	else
	{
		this->mouseDownTimer = glm::clamp(this->mouseDownTimer - dt * UI_BUTTON_MOUSE_DOWN_TIMER_SCALER, 0.0f, 1.0f);
	}

	float color = 1.0f - this->mouseDownTimer * 0.3f;
	if (this->isMouseOver) color += 0.1f;
	this->color.r = color;
	this->color.g = color;
	this->color.b = color;

	float scale = 1.0f - this->mouseDownTimer * 0.1f;
	this->scale = glm::vec2(this->originalScaleX * scale, this->originalScaleY * scale);
	
}

void UIButton::onMouseDown(float x, float y)
{
	if (this->isMouseInBound(x, y))
	{
		this->isMouseDown = true;
	}
}

void UIButton::onMouseUp(float x, float y)
{
	this->isMouseDown = false;
	if (this->isMouseInBound(x, y) && this->onClickCallback != nullptr)
	{
		this->onClickCallback();
	}
}

void UIButton::onMouseMove(float x, float y)
{
	this->isMouseOver = this->isMouseInBound(x, y);
}

bool UIButton::isMouseInBound(float x, float y)
{
	
	switch (this->shape)
	{
	case UIButton::Rectangle:
		return glm::abs(x - this->position.x) <= this->scale.x
			&& glm::abs(y - this->position.y) <= this->scale.y;
	case UIButton::Round:
		glm::vec2 pos = glm::vec2(x, y);
		return glm::length(pos - this->position) <= this->scale.x;
	default:
		return false;
	}
}
