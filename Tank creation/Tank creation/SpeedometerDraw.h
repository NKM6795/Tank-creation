#pragma once


#include "ComponentDraw.h"
#include "Speedometer.h"


class SpeedometerDraw : public ComponentDraw
{
	Texture *panelTexture;
	Sprite *panelSprite;

	Texture *leverTexture;
	Sprite *leverSprite;
	Vector2int offset;

	Texture *speedometerTexture;
	Sprite *speedometerSprite;
	int numberOfVariant;

public:
	SpeedometerDraw(ComponentParameter *component);

	~SpeedometerDraw();

	void draw(RenderTexture &renderTexture, long timer, ViewableObject *object, int compulsoryDrawing = false);
};