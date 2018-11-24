#pragma once


#include "BasicElementDraw.h"
#include "ViewableObject.h"


class ComponentDraw
{

public:
	ComponentDraw() {}
	virtual ~ComponentDraw() {}

	//compulsoryDrawing:
	//0 - false
	//1 - All except selected guns
	//-1 - All selected guns
	virtual void draw(RenderTexture &renderTexture, long timer, ViewableObject *object, int compulsoryDrawing = false) = 0;
};