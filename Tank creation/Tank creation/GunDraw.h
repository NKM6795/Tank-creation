#pragma once


#include "ComponentDraw.h"
#include "BackgroundDraw.h"
#include "Gun.h"


class GunDraw : public ComponentDraw
{
	Texture *barrelTexture;
	Sprite *barrelSprite;
	int numberOfVariantbarrel;

	Texture *handholdTexture;
	Sprite *handholdSprite;
	int numberOfVarianthandhold;

	int xOffsetForBarrel,
		yOffsetForBarrel;
	int xOriginForBarrel,
		yOriginForBarrel;

	ComponentDraw *background;

public:
	GunDraw(ComponentParameter *component, ComponentDraw *background = nullptr);

	~GunDraw();

	void draw(RenderTexture &renderTexture, long timer, ViewableObject *object, int compulsoryDrawing = false);
};