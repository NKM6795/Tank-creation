#include "ViewableObject.h"


Component::Component(string name, string objectName, string typeName, string identifierName, int numberOfVariant, int width, int height)
{
	component = new ComponentParameter;

	component->name = name;

	component->objectName = objectName;
	component->typeName = typeName;
	component->identifierName = identifierName;
	component->numberOfVariant = numberOfVariant;

	component->width = width;
	component->height = height;

	component->canRebound = false;

	component->backgroundIndex = 0;
}

Component::~Component()
{
	delete component;
}


ComponentParameter *Component::getStruct()
{
	return component;
}



ViewableObject::ViewableObject()
{
	index = -1;

	component = nullptr;

	xCoordinate = 0;
	yCoordinate = 0;

	healthPoints = -1;

	needDraw = true;
	needChangeColor = 0;
	tiltAngle = 0.f;
	speed = 0.f;

	scale = 1.f;
}

ViewableObject::ViewableObject(Component *component) : component(component)
{
	index = -1;

	xCoordinate = 0;
	yCoordinate = 0;

	healthPoints = -1;

	needDraw = true;
	needChangeColor = false;

	scale = 1.f;
}

ViewableObject::ViewableObject(Component *component, int index) : component(component), index(index)
{
	xCoordinate = 0;
	yCoordinate = 0;

	healthPoints = -1;

	needDraw = true;
	needChangeColor = 0;
	tiltAngle = 0.f;
	speed = 0.f;

	scale = 1.f;

	timerForObject = 0;

	canDoDamageToItself = false;
}


ViewableObject::~ViewableObject()
{

}


Component *ViewableObject::getComponent()
{
	return component;
}


Vector2int ViewableObject::getPosition()
{
	return Vector2int(xCoordinate, yCoordinate);
}

void ViewableObject::setPosition(Vector2int position)
{
	xCoordinate = position.x;
	yCoordinate = position.y;
}

void ViewableObject::setPosition(int x, int y)
{
	xCoordinate = x;
	yCoordinate = y;
}

Vector2float ViewableObject::getBulletPosition(bool old)
{
	return Vector2float(getPosition());
}

void ViewableObject::setBulletPosition(Vector2float position)
{
	setPosition(position);
}


int ViewableObject::getHealth()
{
	return healthPoints;
}

void ViewableObject::setHeath(int health)
{
	healthPoints = health;
}


int ViewableObject::getIndex()
{
	return index;
}

void ViewableObject::setIndex(int i)
{
	index = i;
}


float ViewableObject::getScale()
{
	return scale;
}

void ViewableObject::setScale(float scaleCopy)
{
	scale = scaleCopy;
}


ComponentParameter *ViewableObject::getComponentParameter()
{
	return component->getStruct();
}


ViewableObject *ViewableObject::getAddition()
{
	return nullptr;
}

ViewableObject *ViewableObject::getFather()
{
	return nullptr;
}
