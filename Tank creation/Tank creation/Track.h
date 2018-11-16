#pragma once


#include "ViewableObject.h"


class TrackComponent : public Component
{


public:
	TrackComponent(string name, string objectName, string typeName, string identifierName, int numberOfVariant, int healthPoints, int width, int height);


};


class Track : public ViewableObject
{
	ViewableObject *addition;

public:
	Track();
	Track(Component *component);
	Track(Component *component, int index);

	~Track();

	ViewableObject *getAddition();
};


class AdditionToTrack : public ViewableObject
{
	ViewableObject *main;

public:
	AdditionToTrack(ViewableObject *main);


	Vector2int getPosition();
	void setPosition(Vector2int position);
	void setPosition(int x, int y);

	int getHealth();
	void setHeath(int health);

	int getIndex();
	void setIndex(int i);

	ComponentParameter *getComponentParameter();
};