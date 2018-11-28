#pragma once


#include "ViewableObject.h"


class GunComponent : public Component
{


public:
	GunComponent(string name, string objectName, string typeName, string identifierName, int numberOfVariant, string typeName2, string identifierName2, int numberOfVariant2,
		bool horizontally, int damage, int bulletSpeed, int reload, int xOffsetForBarrel, int yOffsetForBarrel, int xOriginForBarrel, int yOriginForBarrel, int healthPoints, int backgroundIndex, int width, int height, vector<int> indexOfComponents = vector<int>(0), int cost = 0);


};


class Gun : public ViewableObject
{
	ViewableObject *addition;

public:
	Gun();
	Gun(Component *component);
	Gun(Component *component, int index);

	~Gun();

	ViewableObject *getAddition();
};


class AdditionToGun : public ViewableObject
{
	ViewableObject *main;

public:
	AdditionToGun(ViewableObject *main);


	Vector2int getPosition();
	void setPosition(Vector2int position);
	void setPosition(int x, int y);

	int getHealth();
	void setHeath(int health);

	int getIndex();
	void setIndex(int i);

	ComponentParameter *getComponentParameter();
};