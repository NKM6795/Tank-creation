#include "PersonalTank.h"


PersonalTank::PersonalTank(vector<vector<ViewableObject *> > &objects, int dataArraySize) : objects(&objects), dataArraySize(dataArraySize)
{
	position = 0;

	needDrive = false;

	speed = 0;
	maxSpeed = 36;
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
	setOffset(offset.x, offset.y);
}

void PersonalTank::setOffset(int x, int y)
{
	xOffset = x;
	position = 0;
	yOffset = y;
}


Vector2int PersonalTank::getGlobalOffset()
{
	return globalOffset;
}

Vector2int PersonalTank::getOffsetForTank()
{
	return Vector2int(xOffset - globalOffset.x, yOffset - globalOffset.y);
}


void PersonalTank::setDrive(bool right)
{
	needDrive = true;
	driveRight = right;
}


int PersonalTank::getSpeed()
{
	return speed;
}

int PersonalTank::getMaxSpeed()
{
	return maxSpeed;
}


void PersonalTank::work(Vector2int mousePosition, bool isPressed, long timer, int fps, bool rightIsPressed)
{
	if (needDrive)
	{
		needDrive = false;
		if (driveRight)
		{
			speed += maxSpeed / 6;
			speed = min(speed, maxSpeed);
		}
		else
		{
			speed -= maxSpeed / 6;
			speed = max(speed, -maxSpeed);
		}
	}


}


void PersonalTank::download(string fileName, vector<Component *> &components)
{
	TankEditor tankEditor(*objects);

	tankEditor.download(fileName, components);
}