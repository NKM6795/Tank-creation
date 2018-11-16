#pragma once


#include "BasicElementDraw.h"
#include "ViewableObject.h"


class ComponentDraw
{

public:
	ComponentDraw() {}
	virtual ~ComponentDraw() {}

	virtual void draw(RenderTexture &renderTexture, long timer, ViewableObject *object) = 0;
};