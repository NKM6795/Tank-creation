#include "TankEditor.h"


bool TankEditor::checkFreePlace(vector<vector<bool> > &smallTank, int widht, int height, int i, int j)
{
	if (i < 0 || j < 0 || i + widht > int(smallTank.size()) || j + height > int(smallTank.size()))
	{
		return false;
	}
	else
	{
		for (int l = i; l < i + widht; ++l)
		{
			for (int k = j; k < j + height; ++k)
			{
				if (smallTank[l][k])
				{
					return false;
				}
			}
		}
		return true;
	}
}


TankEditor::TankEditor(vector<vector<Object *> > &objects, int dataArraySize) : objects(&objects), dataArraySize(dataArraySize)
{

}

TankEditor::~TankEditor()
{

}


Vector2int TankEditor::getOffset()
{
	return Vector2int(xOffset, yOffset);
}

void TankEditor::setOffset(Vector2int offset)
{
	xOffset = offset.x;
	yOffset = offset.y;
}

void TankEditor::setOffset(int x, int y)
{
	xOffset = x;
	yOffset = y;
}


Object *TankEditor::getObject(Component *component, int index)
{
	Object *newObject = nullptr;

	if (typeid(*component) == typeid(BackgroundComponent))
	{
		newObject = new Background(component, index);
	}
	else if (typeid(*component) == typeid(SmallBlockComponent))
	{
		newObject = new SmallBlock(component, index);
	}
	else if (typeid(*component) == typeid(BigBlockComponent))
	{
		newObject = new BigBlock(component, index);
	}
	else if (typeid(*component) == typeid(EngineRoomComponent))
	{
		newObject = new EngineRoom(component, index);
	}
	else if (typeid(*component) == typeid(TrackComponent))
	{
		newObject = new Track(component, index);
	}
	else if (typeid(*component) == typeid(GunComponent))
	{
		newObject = new Gun(component, index);
	}

	return newObject;
}


Vector2int TankEditor::getFreePlace(Component *component, Vector2int mousePosition)
{
	vector<vector<bool> > smallTank = Tank::getSmallTank(*objects);

	mousePosition = mousePosition - getOffset();

	int widht = component->getStruct()->width,
		height = component->getStruct()->height;
	
	float x = float(mousePosition.x) / 20,
		y = float(mousePosition.y) / 20;

	float maxR = sqrt(47.f * 47.f + 33.f * 33.f);

	int tempI = (widht % 2 == 1) ? int(x - widht / 2) : int(x + 1.5f - widht / 2),
		tempJ = (height % 2 == 1) ? int(y - height / 2) : int(y + 1.5f - height / 2);

	for (float r = 0; r < maxR; r += 0.05f)
	{
		int oldI = -1,
			oldJ = -1;
		for (float phi = 0; phi < 2.f * PI; phi += PI / 90.f)
		{
			int i = (widht % 2 == 1) ? int(x + r * sin(phi) - widht / 2) : int(x + r * sin(phi) + 1.5f - widht / 2),
				j = (height % 2 == 1) ? int(y + r * cos(phi) - height / 2) : int(y + r * cos(phi) + 1.5f - height / 2);

			if (checkFreePlace(smallTank, widht, height, i, j))
			{
				if (oldI == -1)
				{
					oldI = i;
					oldJ = j;
				}

				if (((i - tempI) * (i - tempI) + (j - tempJ) * (j - tempJ)) < ((oldI - tempI) * (oldI - tempI) + (oldJ - tempJ) * (oldJ - tempJ)))
				{
					oldI = i;
					oldJ = j;
				}
			}
		}

		if (oldI != -1)
		{
			return Vector2int(oldI, oldJ);
		}
	}

	return Vector2int(-1, -1);
}

Object *TankEditor::getFreePlace(Component *component, int index, Vector2int mousePosition)
{
	Vector2int position = getFreePlace(component, mousePosition);

	if (position.x == -1)
	{
		return nullptr;
	}
	else
	{
		Object *newObject = getObject(component, index);
		newObject->setPosition(position * 20 + getOffset());
		newObject->setHeath(component->getStruct()->healthPoints);
		newObject->needChangeColor = true;

		return newObject;
	}
}

void TankEditor::addObject(Component *component, int index, Vector2int mousePosition)
{
	Vector2int position = getFreePlace(component, mousePosition);

	if (position.x == -1)
	{
		return;
	}
	else
	{
		(*objects)[position.x][position.y] = getObject(component, index);
		(*objects)[position.x][position.y]->setPosition(position * 20);
		(*objects)[position.x][position.y]->setHeath(component->getStruct()->healthPoints);
	}
}
