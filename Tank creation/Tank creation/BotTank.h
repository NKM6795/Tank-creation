#pragma once


#include "PersonalTank.h"


class BotTank : public PersonalTank
{
	bool needAnalysis;
	long timerForAnalysis;

	Vector2int oldPositionOfPersonalTank;

	vector<Vector2int> prisesPosition;
	vector<ViewableObject *> prises;

	Vector2int getPositionInBot(Vector2int positionForConvert);

	void analysis(Tank &personalTank, Vector2int personalPosition);

	void makeShots(Vector2int mousePosition, vector<Component *> &components, int bulletPositionInComponents, long timer);

	void updateTracks();

public:
	BotTank(vector<vector<ViewableObject *> > &objects, int fieldWidthForBattle, int screenWidth, int dataArraySize = 30);

	~BotTank();

	void setGlobalOffset(Vector2int offset);
	Vector2int getOffsetForTank();

	Vector2int getBorder();
	
	void work(long timer, int fps, int lengthBetweenTanks, Vector2int personalPosition, vector<Component *> &components, int bulletPositionInComponents, vector<ViewableObject *> &bullets, Tank &personalTank);
};
