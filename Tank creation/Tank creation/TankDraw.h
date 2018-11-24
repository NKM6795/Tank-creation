#pragma once


#include "ViewableObjectDraw.h"
#include "Tank.h"


class TankDraw
{

public:
	TankDraw();

	~TankDraw();

	void draw(RenderTexture &renderTexture, long timer, Tank &tank, vector<ComponentDraw *> &components, int compulsoryDrawing = false);

	void save(string fileName, long timer, Tank &tank, vector<ComponentDraw *> &components);
};