#include "Object.h"


Object::Object()
{
	component = nullptr;

	xCoordinate = 0;
	yCoordinate = 0;

	healthPoints = -1;

	needDraw = true;
}

Object::Object(Component *component) : component(component)
{
	xCoordinate = 0;
	yCoordinate = 0;

	healthPoints = -1;

	needDraw = true;
}


Object::~Object()
{

}


Vector2int Object::getPosition()
{
	return Vector2int(xCoordinate, yCoordinate);
}

void Object::setPosition(Vector2int position)
{
	xCoordinate = position.x;
	yCoordinate = position.y;
}

void Object::setPosition(int x, int y)
{
	xCoordinate = x;
	yCoordinate = y;
}


float Object::getHealth()
{
	return healthPoints;
}

void Object::setHeath(float health)
{
	healthPoints = health;
}


ComponentParameter *Object::getComponentParameter()
{
	return component->getStruct();
}
