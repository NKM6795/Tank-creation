#pragma once


#include "ComponentDraw.h"
#include "SmallBlock.h"


class SmallBlockDraw : public ComponentDraw
{
	Texture *smallBlockTexture;
	Sprite *smallBlockSprite;
	int numberOfVariant;

public:
	SmallBlockDraw(ComponentParameter *component);

	~SmallBlockDraw();

	void draw(RenderTexture &renderTexture, long timer, Object *object);
};