#include "PersonalTank.h"


PersonalTank::PersonalTank(vector<vector<ViewableObject *> > &objects, int dataArraySize) : objects(&objects), dataArraySize(dataArraySize)
{
	position = 0;

	needDrive = false;
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


Vector2int PersonalTank::getGlobalOffset()
{
	return globalOffset;
}

Vector2int PersonalTank::getOffsetForTank()
{
	return Vector2int(xOffset - globalOffset.x, yOffset - globalOffset.y + position);
}


void PersonalTank::setDrive(bool right)
{
	needDrive = true;
	driveRight = right;
}


void PersonalTank::work(Vector2int mousePosition, bool isPressed, long timer, int fps, bool rightIsPressed)
{
	if (needDrive)
	{
		needDrive = false;
		if (driveRight)
		{
			globalOffset.x -= 1;
		}
		else
		{
			globalOffset.x += 1;
		}
	}
}


void PersonalTank::download(string fileName, vector<Component *> &components)
{
	TankEditor tankEditor(*objects);

	tankEditor.download(fileName, components);
}