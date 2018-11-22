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

float getAngel(float x1, float y1, float x2, float y2)
{
	float result = (y2 <= y1 ? 0 : 180) + (y2 <= y1 ? 1 : -1) * asin((x2 - x1) / sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1))) * (180 / PI);
	return result < 0 ? result + 360.f : result;
}

float getAngel(int x1, int y1, int x2, int y2)
{
	return getAngel(float(x1), float(y1), float(x2), float(y2));
}

float getAngel(Vector2int first, Vector2int second)
{
	return getAngel(first.x, first.y, second.x, second.y);
}