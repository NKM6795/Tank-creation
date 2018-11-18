#pragma once


#include "WorkWithWindow.h"
#include "PersonalTank.h"


class Battle : public WorkWithWindow
{
	vector<Component *> components;

	Tank tank;
	PersonalTank *personalTank;

public:
	Battle(string &fileName, Graphic *forCopyWindow, string tankName);

	~Battle();

	void work();
};