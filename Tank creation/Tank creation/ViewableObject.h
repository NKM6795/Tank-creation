#pragma once


#include "BaseElement.h"


struct ComponentParameter
{
	string name;

	string objectName;
	string typeName;
	string identifierName;
	int numberOfVariant;

	int healthPoints;
	int cost;

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
	vector<int> indexOfComponents;

	int backgroundIndex;

	int width,
		height;

	vector<Vector2int> dimensions;
	vector<Vector2int> offsets;
};


class Component
{
protected:
	ComponentParameter *component;

public:
	Component(string name, string objectName, string typeName, string identifierName, int numberOfVariant, int width = 1, int height = 1);

	virtual ~Component();

	ComponentParameter *getStruct();
};


class ViewableObject
{
protected:
	int index;

	Component *component;

	int xCoordinate,
		yCoordinate;

	int healthPoints;

	float scale;

public:
	bool needDraw;
	bool needDrawSeparately;
	int needChangeColor;
	float speed;
	float tiltAngle;
	long timerForObject;
	bool canDoDamageToItself;
	int damage;


	ViewableObject();
	ViewableObject(Component *component);
	ViewableObject(Component *component, int index);

	virtual ~ViewableObject();

	virtual Component *getComponent();

	virtual Vector2int getPosition();
	virtual void setPosition(Vector2int position);
	virtual void setPosition(int x, int y);
	virtual Vector2float getBulletPosition(bool old = false);
	virtual void setBulletPosition(Vector2float position);

	virtual int getHealth();
	virtual void setHeath(int health);

	virtual int getIndex();
	virtual void setIndex(int i);

	virtual float getScale();
	virtual void setScale(float scale);

	virtual ComponentParameter *getComponentParameter();

	virtual ViewableObject *getAddition();
	virtual ViewableObject *getFather();
};
