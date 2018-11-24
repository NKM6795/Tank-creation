#pragma once


#include "ComponentDraw.h"
#include "Allotment.h"


class AllotmentDraw : public ComponentDraw
{
	Texture texture;
	Sprite sprite;

public:
	AllotmentDraw(ComponentParameter *component);

	~AllotmentDraw();

	void draw(RenderTexture &renderTexture, long timer, ViewableObject *object, int compulsoryDrawing = false);
};