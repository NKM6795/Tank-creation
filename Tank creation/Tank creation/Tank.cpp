#include "Tank.h"


Tank::Tank(int dataArraySize, int dimension) : dataArraySize(dataArraySize), dimension(dimension)
{
	xOffset = 0;
	yOffset = 0;

	for (int i = 0; i < dataArraySize; ++i)
	{
		vector<ViewableObject *> temp(dataArraySize, nullptr);

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
				Vector2int position = objects.back().back()->getPosition() / 20;

				ViewableObject *object = objects[position.x][position.y];

				int widht = object->getComponentParameter()->width,
					height = object->getComponentParameter()->height;

				delete object;

				for (int l = 0; l < widht; ++l)
				{
					for (int k = 0; k < height; ++k)
					{
						objects[position.x + l][position.y + k] = nullptr;
					}
				}
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
	xOffset = offset.x;
	yOffset = offset.y;
}

void Tank::setOffset(int x, int y)
{
	xOffset = x;
	yOffset = y;
}

int Tank::getDimension()
{
	return dimension;
}

void Tank::setDimension(int dim)
{
	dimension = dim;
}

vector<vector<ViewableObject *> > &Tank::getViewableObjects()
{
	return objects;
}


ViewableObject *Tank::getViewableObject(Vector2int mousePosition)
{
	mousePosition = mousePosition - getOffset();

	int i = mousePosition.x / 20,
		j = mousePosition.y / 20;

	if (i < 0 || j < 0 || i >= dataArraySize || j >= dataArraySize)
	{
		return nullptr;
	}

	return objects[i][j];
}


vector<vector<bool> > Tank::getSmallTank(vector<vector<ViewableObject *> > &objectsCopy)
{
	vector<vector<bool> > smallTank(objectsCopy.size(), vector<bool>(objectsCopy.size(), false));

	for (int i = 0; i < int(objectsCopy.size()); ++i)
	{
		for (int j = 0; j < int(objectsCopy.size()); ++j)
		{
			if (objectsCopy[i][j] != nullptr && objectsCopy[i][j]->getHealth() > 0)
			{
				smallTank[i][j] = true;
			}
		}
	}

	return smallTank;
}

vector<vector<bool> > Tank::getSmallTank()
{
	return getSmallTank(objects);
}



int getLengthBetweenTanks(Tank &left, Tank &right)
{
	vector<vector<bool> > smallLeftTank = Tank::getSmallTank(left.getViewableObjects()),
		smallRightTank = Tank::getSmallTank(right.getViewableObjects());
	
	int number = int(smallLeftTank.size());

	int result = 2 * number;
	for (int j = 0; j < number; ++j)
	{
		int last = -1;
		for (int i = 0; i < number; ++i)
		{
			if (smallLeftTank[i][j])
			{
				last = i;
			}
		}

		if (last != -1)
		{
			last = number - last - 1;
			for (int i = number - 1; i >= 0; --i)
			{
				if (smallRightTank[i][j])
				{
					result = min(number - i - 1 + last, result);
				}
			}
		}
	}

	return result;
}