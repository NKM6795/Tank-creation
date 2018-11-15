#pragma once


#include "ObjectDraw.h"
#include "Tank.h"


class TankDraw
{

public:
	TankDraw();

	~TankDraw();

	void draw(RenderTexture &renderTexture, long timer, Tank &tank, vector<ComponentDraw *> &components);

	void save(string fileName, long timer, Tank &tank, vector<ComponentDraw *> &components);
};