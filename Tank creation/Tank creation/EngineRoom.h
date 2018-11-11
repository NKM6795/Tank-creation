#pragma once


#include "Object.h"


class EngineRoomComponent : public Component
{


public:
	EngineRoomComponent(string objectName, string typeName, string identifierName, int numberOfVariant, int healthPoints);


};


class EngineRoom : public Object
{
	Object **additions;

public:
	EngineRoom();
	EngineRoom(Component *component);
	EngineRoom(Component *component, int index);


};


class AdditionToEngineRoom : public Object
{
	Object *main;

public:
	AdditionToEngineRoom(Object *main);


	Vector2int getPosition();
	void setPosition(Vector2int position);
	void setPosition(int x, int y);

	int getHealth();
	void setHeath(int health);

	int getIndex();
	void setIndex(int i);

	ComponentParameter *getComponentParameter();
};