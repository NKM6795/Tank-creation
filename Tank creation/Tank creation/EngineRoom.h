#pragma once


#include "ViewableObject.h"


class EngineRoomComponent : public Component
{


public:
	EngineRoomComponent(string name, string objectName, string typeName, string identifierName, int numberOfVariant, string typeName2, string identifierName2, int numberOfVariant2,
		string typeName3, string identifierName3, int numberOfVariant3, int healthPoints, int xOffsetForRoom, int yOffsetForRoom, int xOffsetForPerson, int yOffsetForPerson, int width, int height, int cost = 0);


};


class EngineRoom : public ViewableObject
{
	ViewableObject *addition;

public:
	EngineRoom();
	EngineRoom(Component *component);
	EngineRoom(Component *component, int index);

	~EngineRoom();

	ViewableObject *getAddition();
};


class AdditionToEngineRoom : public ViewableObject
{
	ViewableObject *main;

public:
	AdditionToEngineRoom(ViewableObject *main);


	Vector2int getPosition();
	void setPosition(Vector2int position);
	void setPosition(int x, int y);

	int getHealth();
	void setHeath(int health);

	int getIndex();
	void setIndex(int i);

	ComponentParameter *getComponentParameter();
};