#pragma once


#include "BasicElementDraw.h"
#include "Object.h"


class ComponentDraw
{

public:
	ComponentDraw() {}
	virtual ~ComponentDraw() {}

	virtual void draw(RenderTexture &renderTexture, long timer, Object *object) = 0;
};