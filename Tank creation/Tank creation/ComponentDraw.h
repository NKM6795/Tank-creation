#pragma once


#include "BasicElementDraw.h"
#include "Component.h"


class ComponentDraw
{

public:
	ComponentDraw() {}
	virtual ~ComponentDraw() {}

	virtual void draw(RenderTexture &renderTexture, long timer) = 0;
};