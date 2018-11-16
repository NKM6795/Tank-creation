#pragma once


#include "ViewableObject.h"


class BigBlockComponent : public Component
{


public:
	BigBlockComponent(string name, string objectName, string typeName, string identifierName, int numberOfVariant, int healthPoints, bool canRebound);


};


class BigBlock : public ViewableObject
{
	ViewableObject *addition;

public:
	BigBlock();
	BigBlock(Component *component);
	BigBlock(Component *component, int index);

	~BigBlock();

	ViewableObject *getAddition();
};


class AdditionToBigBlock : public ViewableObject
{
	ViewableObject *main;

public:
	AdditionToBigBlock(ViewableObject *main);


	Vector2int getPosition();
	void setPosition(Vector2int position);
	void setPosition(int x, int y);

	int getHealth();
	void setHeath(int health);

	int getIndex();
	void setIndex(int i);

	ComponentParameter *getComponentParameter();
};