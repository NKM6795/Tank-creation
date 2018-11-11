#pragma once


#include "BaseElement.h"


struct ComponentParameter
{
	string objectName;
	string typeName;
	string identifierName;
	int numberOfVariant;

	int healthPoints;

	bool canRebound;
};


class Component
{
protected:
	ComponentParameter *component;

public:
	Component(string objectName, string typeName, string identifierName, int numberOfVariant);

	virtual ~Component();

	ComponentParameter *getStruct();
};


class Object
{
protected:
	int index;

	Component *component;

	int xCoordinate,
		yCoordinate;

	int healthPoints;

public:
	bool needDraw;

	Object();
	Object(Component *component);
	Object(Component *component, int index);

	virtual ~Object();

	virtual Vector2int getPosition();
	virtual void setPosition(Vector2int position);
	virtual void setPosition(int x, int y);

	virtual int getHealth();
	virtual void setHeath(int health);

	virtual int getIndex();
	virtual void setIndex(int i);

	virtual ComponentParameter *getComponentParameter();
};
