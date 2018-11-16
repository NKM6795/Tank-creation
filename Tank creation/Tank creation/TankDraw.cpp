#include "TankDraw.h"


TankDraw::TankDraw()
{

}

TankDraw::~TankDraw()
{

}

void TankDraw::draw(RenderTexture &renderTexture, long timer, Tank &tank, vector<ComponentDraw *> &components)
{
	for (int i = 0; i < int(tank.getViewableObjects().size()); ++i)
	{
		objectDraw(renderTexture, timer, tank.getViewableObjects()[i], components);
	}
}

void TankDraw::save(string fileName, long timer, Tank &tank, vector<ComponentDraw *> &components)
{
	fileName = "Data/Tanks/" + fileName + ".png";

	RenderTexture renderForSave;
	renderForSave.create(tank.getDimension(), tank.getDimension());
	renderForSave.clear(Color(89, 85, 83));

	draw(renderForSave, timer, tank, components);
	renderForSave.display();

	Image image;
	image.create(tank.getDimension(), tank.getDimension());
	image.copy(renderForSave.getTexture().copyToImage(), 0, 0, IntRect(0, 0, tank.getDimension(), tank.getDimension()), true);

	image.saveToFile(fileName);
}
