#include "PersonalTank.h"


PersonalTank::PersonalTank(vector<vector<ViewableObject *> > &objects, int dataArraySize) : objects(&objects), dataArraySize(dataArraySize)
{

}

PersonalTank::~PersonalTank()
{

}


Vector2int PersonalTank::getOffset()
{
	return Vector2int(xOffset, yOffset);
}

void PersonalTank::setOffset(Vector2int offset)
{
	xOffset = offset.x;
	yOffset = offset.y;
}

void PersonalTank::setOffset(int x, int y)
{
	xOffset = x;
	yOffset = y;
}


void PersonalTank::download(string fileName, vector<Component *> &components)
{
	TankEditor tankEditor(*objects);

	tankEditor.download(fileName, components);
}