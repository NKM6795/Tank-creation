#pragma once


#include "ComponentDraw.h"
#include "BigBlock.h"


class BigBlockDraw : public ComponentDraw
{
	Texture *bigBlockTexture;
	Sprite *bigBlockSprite;
	int numberOfVariant;

public:
	BigBlockDraw(ComponentParameter *component);

	~BigBlockDraw();

	void draw(RenderTexture &renderTexture, long timer, Object *object);
};