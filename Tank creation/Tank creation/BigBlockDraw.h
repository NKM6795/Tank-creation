#pragma once


#include "ComponentDraw.h"
#include "BackgroundDraw.h"
#include "BigBlock.h"


class BigBlockDraw : public ComponentDraw
{
	Texture *bigBlockTexture;
	Sprite *bigBlockSprite;
	int numberOfVariant;

	ComponentDraw *background;

public:
	BigBlockDraw(ComponentParameter *component, ComponentDraw *background);

	~BigBlockDraw();

	void draw(RenderTexture &renderTexture, long timer, Object *object);
};