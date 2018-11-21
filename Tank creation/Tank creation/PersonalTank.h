#pragma once


#include "TankEditor.h"


class PersonalTank
{
	vector<vector<ViewableObject *> > *objects;

	int xOffset,
		yOffset;

	Vector2int globalOffset;
	int position;

	int dataArraySize;

	bool needDrive;
	bool driveRight;

	int speed;
	int maxSpeed;

public:
	PersonalTank(vector<vector<ViewableObject *> > &objects, int dataArraySize = 30);

	~PersonalTank();

	Vector2int getOffset();
	void setOffset(Vector2int offset);
	void setOffset(int x, int y);

	Vector2int getGlobalOffset();
	Vector2int getOffsetForTank();

	void setDrive(bool right);
	
	int getSpeed();
	int getMaxSpeed();

	void work(Vector2int mousePosition, bool isPressed, long timer, int fps, bool rightIsPressed = false);

	void download(string fileName, vector<Component *> &components);
};