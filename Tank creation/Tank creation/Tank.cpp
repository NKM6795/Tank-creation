#include "Tank.h"


Tank::Tank(int dataArraySize) : dataArraySize(dataArraySize)
{
	xOffset = 0;
	yOffset = 0;

	for (int i = 0; i < dataArraySize; ++i)
	{
		vector<Object *> temp(dataArraySize, nullptr);

		objects.push_back(temp);
	}
}

Tank::~Tank()
{
	while (objects.size() > 0)
	{
		while (objects.back().size() > 0)
		{
			if (objects.back().back() != nullptr)
			{
				delete objects.back().back();
			}
			objects.back().pop_back();
		}
		objects.pop_back();
	}
}


Vector2int Tank::getOffset()
{
	return Vector2int(xOffset, yOffset);
}

void Tank::setOffset(Vector2int offset)
{
	yOffset = offset.x;
	yOffset = offset.y;
}

void Tank::setOffset(int x, int y)
{
	yOffset = x;
	yOffset = y;
}


vector<vector<Object *> > &Tank::getObjects()
{
	return objects;
}