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

	string typeName2;
	string identifierName2;
	int numberOfVariant2;

	string typeName3;
	string identifierName3;
	int numberOfVariant3;

	int xOffsetForRoom,
		yOffsetForRoom;
	int xOffsetForPerson,
		yOffsetForPerson;

	bool horizontally;
	int damage;
	int bulletSpeed;
	int reload;
	int xOffsetForBarrel,
		yOffsetForBarrel;
	int xOriginForBarrel,
		yOriginForBarrel;
	float tiltAngle;

	int backgroundIndex;

	int width,
		height;
};


class Component
{
protected:
	ComponentParameter *component;

public:
	Component(string objectName, string typeName, string identifierName, int numberOfVariant, int width = 1, int height = 1);

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
	bool needChangeColor;

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
