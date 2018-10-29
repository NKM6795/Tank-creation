#include "BaseElement.h"


bool inArea(int width, int height, int xCoordinate, int yCoordinate, int x, int y)
{
	return (x >= xCoordinate - width / 2) && (x <= xCoordinate + width / 2) && (y > yCoordinate - height / 2) && (y < yCoordinate + height / 2);
}

bool inArea(int width, int height, int xCoordinate, int yCoordinate, Vector2int position)
{
	return inArea(width, height, xCoordinate, yCoordinate, position.x, position.y);
}

float getLength(float x1, float y1, float x2, float y2)
{
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}