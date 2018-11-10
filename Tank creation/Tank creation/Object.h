#pragma once


#include "BaseElement.h"


struct ComponentParameter
{
	string objectName;
	string typeName;
	string identifierName;
	int numberOfVariant;
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

	float healthPoints;

public:
	bool needDraw;

	Object();
	Object(Component *component);

	~Object();

	Vector2int getPosition();
	void setPosition(Vector2int position);
	void setPosition(int x, int y);

	float getHealth();
	void setHeath(float health);

	int getIndex();
	void setIndex(int i);

	ComponentParameter *getComponentParameter();
};
