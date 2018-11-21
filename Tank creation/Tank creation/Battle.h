#pragma once


#include "WorkWithWindow.h"
#include "PersonalTank.h"


class Battle : public WorkWithWindow
{
	vector<Component *> components;

	int fieldWidthForBattle;

	vector<Vector2int> positionsOfBackground;
	vector<ViewableObject *> objects;

	int positionForBackground;
	int positionForSpeedometer;

	Tank tank;
	PersonalTank *personalTank;

	void updateObjects();

public:
	Battle(string &fileName, Graphic *forCopyWindow, string tankName);

	~Battle();

	void work();
};