#include "Object.h"


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
	needChangeColor = false;

	scale = 1.f;
}

Object::Object(Component *component) : component(component)
{
	index = -1;

	xCoordinate = 0;
	yCoordinate = 0;

	healthPoints = -1;

	needDraw = true;
	needChangeColor = false;

	scale = 1.f;
}

Object::Object(Component *component, int index) : component(component), index(index)
{
	xCoordinate = 0;
	yCoordinate = 0;

	healthPoints = -1;

	needDraw = true;
	needChangeColor = false;

	scale = 1.f;
}


Object::~Object()
{

}


Component *Object::getComponent()
{
	return component;
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


int Object::getHealth()
{
	return healthPoints;
}

void Object::setHeath(int health)
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


float Object::getScale()
{
	return scale;
}

void Object::setScale(float scaleCopy)
{
	scale = scaleCopy;
}


ComponentParameter *Object::getComponentParameter()
{
	return component->getStruct();
}


Object *Object::getAddition()
{
	return nullptr;
}
