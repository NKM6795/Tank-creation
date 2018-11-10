#include "Object.h"


Component::Component(string objectName, string typeName, string identifierName, int numberOfVariant)
{
	component = new ComponentParameter;

	component->objectName = objectName;
	component->typeName = typeName;
	component->identifierName = identifierName;
	component->numberOfVariant = numberOfVariant;
}

Component::~Component()
{
	delete component;
}


ComponentParameter *Component::getStruct()
{
	return component;
}



Object::Object()
{
	index = -1;

	component = nullptr;

	xCoordinate = 0;
	yCoordinate = 0;

	healthPoints = -1;

	needDraw = true;
}

Object::Object(Component *component) : component(component)
{
	index = -1;

	xCoordinate = 0;
	yCoordinate = 0;

	healthPoints = -1;

	needDraw = true;
}

Object::Object(Component *component, int index) : component(component), index(index)
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


int Object::getIndex()
{
	return index;
}

void Object::setIndex(int i)
{
	index = i;
}


ComponentParameter *Object::getComponentParameter()
{
	return component->getStruct();
}
