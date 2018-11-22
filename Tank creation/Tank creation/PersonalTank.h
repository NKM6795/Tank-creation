#pragma once


#include "TankEditor.h"


class PersonalTank
{
	vector<vector<ViewableObject *> > *objects;

	int xOffset,
		yOffset;

	Vector2int globalOffset;
	int position;
	int fieldWidthForBattle;
	int screenWidth;

	int dataArraySize;

	bool needDrive;
	bool driveRight;

	int speed;
	int maxSpeed;
	long timerForSpeed;

	void updateTracks();

public:
	PersonalTank(vector<vector<ViewableObject *> > &objects, int fieldWidthForBattle, int screenWidth, int dataArraySize = 30);

	~PersonalTank();

	Vector2int getOffset();
	void setOffset(Vector2int offset);
	void setOffset(int x, int y);

	Vector2int getGlobalOffset();
	Vector2int getOffsetForTank();

	Vector2int getBorder();

	void setDrive(bool right);
	
	int getSpeed();
	int getMaxSpeed();

	void work(Vector2int mousePosition, bool isPressed, long timer, int fps, bool rightIsPressed = false);

	void download(string fileName, vector<Component *> &components);
};