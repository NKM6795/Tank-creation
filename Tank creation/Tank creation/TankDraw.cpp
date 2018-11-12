#include "TankDraw.h"


TankDraw::TankDraw()
{

}

TankDraw::~TankDraw()
{

}

void TankDraw::draw(RenderTexture &renderTexture, long timer, Tank &tank, vector<ComponentDraw *> &components)
{
	for (int i = 0; i < int(tank.getObjects().size()); ++i)
	{
		objectDraw(renderTexture, timer, tank.getObjects()[i], components);
	}
}