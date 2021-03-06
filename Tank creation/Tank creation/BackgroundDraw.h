#pragma once


#include "ComponentDraw.h"
#include "Background.h"


class BackgroundDraw : public ComponentDraw
{
	Texture *backgroundTexture;
	Sprite *backgroundSprite;
	int numberOfVariant;

public:
	BackgroundDraw(ComponentParameter *component);

	~BackgroundDraw();

	void draw(RenderTexture &renderTexture, long timer, ViewableObject *object, int compulsoryDrawing = false);
};


class BackgroundForBattleDraw : public ComponentDraw
{
	Texture *backgroundTexture;
	Sprite *backgroundSprite;
	int numberOfVariant;

public:
	BackgroundForBattleDraw(ComponentParameter *component);

	~BackgroundForBattleDraw();

	void draw(RenderTexture &renderTexture, long timer, ViewableObject *object, int compulsoryDrawing = false);
};