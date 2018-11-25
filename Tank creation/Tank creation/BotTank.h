#pragma once


#include "PersonalTank.h"


class BotTank : public PersonalTank
{

public:
	BotTank(vector<vector<ViewableObject *> > &objects, int fieldWidthForBattle, int screenWidth, int dataArraySize = 30);

	~BotTank();

};
