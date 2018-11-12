#include "TankDraw.h"


TankDraw::TankDraw()
{

}

TankDraw::~TankDraw()
{

}

void TankDraw::draw(RenderTexture &renderTexture, long timer, vector<Object *> &objects, vector<ComponentDraw *> &components)
{
	objectDraw(renderTexture, timer, objects, components);
}