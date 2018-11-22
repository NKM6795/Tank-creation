#include "PersonalTank.h"


PersonalTank::PersonalTank(vector<vector<ViewableObject *> > &objects, int fieldWidthForBattle, int screenWidth, int dataArraySize) : objects(&objects), fieldWidthForBattle(fieldWidthForBattle), screenWidth(screenWidth), dataArraySize(dataArraySize)
{
	position = 0;

	needDrive = false;

	speed = 0;
	maxSpeed = 6;

	timerForSpeed = 0;
}

PersonalTank::~PersonalTank()
{

}


void PersonalTank::updateTracks()
{
	for (int i = 0; i < int((*objects).size()); ++i)
	{
		for (int j = 0; j < int((*objects).size()); ++j)
		{
			if ((*objects)[i][j] != nullptr && typeid(*(*objects)[i][j]) == typeid(Track))
			{
				(*objects)[i][j]->getComponentParameter()->backgroundIndex = ((*objects)[i][j]->getComponentParameter()->backgroundIndex + maxSpeed * (*objects)[i][j]->getComponentParameter()->numberOfVariant + speed / abs(speed)) % (*objects)[i][j]->getComponentParameter()->numberOfVariant;
			}
		}
	}
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
	if (position == 0)
	{
		return Vector2int(xOffset, yOffset);
	}
	return Vector2int(xOffset + position, yOffset - globalOffset.y);
}


Vector2int PersonalTank::getBorder()
{
	vector<vector<bool> > smallTank = Tank::getSmallTank(*objects);

	Vector2int result(dataArraySize, -1);

	for (int i = 0; i < int(smallTank.size()); ++i)
	{
		for (int j = 0; j < int(smallTank.size()); ++j)
		{
			if (smallTank[i][j])
			{
				result.x = min(result.x, i);
				result.y = max(result.y, i);
			}
		}
	}
	return result;
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

	if (speed != 0 && timer - timerForSpeed >= 100 - (100 * abs(speed)) / maxSpeed)
	{
		timerForSpeed = timer;
		updateTracks();

		globalOffset.x -= speed / abs(speed);
		Vector2int border = getBorder() * 20;
		border.y += 20;

		if (globalOffset.x <= 0 && globalOffset.x >= -(fieldWidthForBattle - screenWidth))
		{
			if (position < 0)
			{
				globalOffset.x = 0;
				position += 1;
			}
			else if (position > 0)
			{
				globalOffset.x = -(fieldWidthForBattle - screenWidth);
				position -= 1;
			}
			else
			{
				position = 0;
			}
		}
		else if (globalOffset.x > 0)
		{
			position -= 1;
			globalOffset.x = 0;
			if (position < -xOffset - border.x)
			{
				position = -xOffset - border.x;
			}
		}
		else if (globalOffset.x < -(fieldWidthForBattle - screenWidth))
		{
			position += 1;
			globalOffset.x = -(fieldWidthForBattle - screenWidth);
			if (position > screenWidth - xOffset - border.y)
			{
				position = screenWidth - xOffset - border.y;
			}
		}

	}
}


void PersonalTank::download(string fileName, vector<Component *> &components)
{
	TankEditor tankEditor(*objects);

	tankEditor.download(fileName, components);
}