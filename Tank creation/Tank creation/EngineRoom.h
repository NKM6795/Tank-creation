#pragma once


#include "Object.h"


class EngineRoomComponent : public Component
{


public:
	EngineRoomComponent(string objectName, string typeName, string identifierName, int numberOfVariant, string typeName2, string identifierName2, int numberOfVariant2, 
		string typeName3, string identifierName3, int numberOfVariant3, int healthPoints, int xOffsetForRoom, int yOffsetForRoom, int xOffsetForPerson, int yOffsetForPerson);


};


class EngineRoom : public Object
{
	Object **additions;

public:
	EngineRoom();
	EngineRoom(Component *component);
	EngineRoom(Component *component, int index);

	~EngineRoom();
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