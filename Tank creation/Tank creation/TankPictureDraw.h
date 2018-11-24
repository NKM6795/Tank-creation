#pragma once


#include "ComponentDraw.h"
#include "TankPicture.h"


class TankPictureDraw : public ComponentDraw
{
	Texture texture;
	Sprite sprite;

public:
	TankPictureDraw(ComponentParameter *component);

	~TankPictureDraw();

	void draw(RenderTexture &renderTexture, long timer, ViewableObject *object, int compulsoryDrawing = false);
};