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


Vector2int TankEditor::getFreePlace(Component &component, Vector2int mousePosition)
{
	vector<vector<bool> > smallTank = Tank::getSmallTank(*objects);

	mousePosition = mousePosition - getOffset();

	int widht = component.getStruct()->width,
		height = component.getStruct()->height;
	
	float x = float(mousePosition.x),
		y = float(mousePosition.y);

	float maxR = sqrt(47.f * 47.f + 33.f * 33.f);

	for (float r = 0; r < maxR; r += 1.f)
	{
		for (float phi = 0; phi < 2.f * PI; phi += PI / 100.f)
		{
			int i = (widht % 2 == 1) ? int(x + r * sin(phi) - widht / 2) : int(x + r * sin(phi) + 1.5f - widht / 2),
				j = (height % 2 == 1) ? int(y + r * cos(phi) - height / 2) : int(y + r * cos(phi) + 1.5f - height / 2);

			if (checkFreePlace(smallTank, widht, height, i, j))
			{
				return Vector2int(i, j);
			}
		}
	}

	return Vector2int(-1, -1);
}
