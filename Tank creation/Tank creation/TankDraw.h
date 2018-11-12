#pragma once


#include "ObjectDraw.h"


class TankDraw
{

public:
	TankDraw();

	~TankDraw();

	void draw(RenderTexture &renderTexture, long timer, vector<Object *> &objects, vector<ComponentDraw *> &components);
};