#pragma once


#include "PersonalTank.h"


class BotTank : public PersonalTank
{

	void updateTracks();

public:
	BotTank(vector<vector<ViewableObject *> > &objects, int fieldWidthForBattle, int screenWidth, int dataArraySize = 30);

	~BotTank();

	void setGlobalOffset(Vector2int offset);
	Vector2int getOffsetForTank();
	
	void work(long timer, int fps, vector<Component *> &components, int bulletPositionInComponents, vector<ViewableObject *> &bullets);
};
