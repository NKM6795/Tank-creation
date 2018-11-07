#pragma once


#include "Component.h"


class Object
{
protected:
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

	ComponentParameter *getComponentParameter();
};
