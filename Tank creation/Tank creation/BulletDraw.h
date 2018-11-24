#pragma once


#include "ComponentDraw.h"
#include "Bullet.h"


class BulletDraw : public ComponentDraw
{
	Texture *texture;
	Sprite *sprite;
	int numberOfVariant;

public:
	BulletDraw(ComponentParameter *component);

	~BulletDraw();

	void draw(RenderTexture &renderTexture, long timer, ViewableObject *object, int compulsoryDrawing = false);
};