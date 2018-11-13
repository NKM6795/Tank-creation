#pragma once


#include "Object.h"


class BigBlockComponent : public Component
{


public:
	BigBlockComponent(string objectName, string typeName, string identifierName, int numberOfVariant, int healthPoints, bool canRebound);


};


class BigBlock : public Object
{
	Object *addition;

public:
	BigBlock();
	BigBlock(Component *component);
	BigBlock(Component *component, int index);

	~BigBlock();

	Object *getAddition();
};


class AdditionToBigBlock : public Object
{
	Object *main;

public:
	AdditionToBigBlock(Object *main);


	Vector2int getPosition();
	void setPosition(Vector2int position);
	void setPosition(int x, int y);

	int getHealth();
	void setHeath(int health);

	int getIndex();
	void setIndex(int i);

	ComponentParameter *getComponentParameter();
};