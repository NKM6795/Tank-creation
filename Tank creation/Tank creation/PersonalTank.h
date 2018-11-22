#pragma once


#include "TankEditor.h"
#include "Allotment.h"


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

	vector<vector<Vector2int> > grupyAllocation;
	vector<Vector2int> highlightedItems;
	bool controlIsPressed;
	int numberIsPressed;

	void updateTracks();

	float getAngelForGun(ViewableObject *gun, Vector2int mousePosition);
	void updateGun(Vector2int mousePosition);

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

	ViewableObject *getViewableObject(Vector2int mousePosition);

	void setControlIsPressed(bool isPressed);
	void setNumberIsPressed(int unicode);

	bool needHighlighte();
	vector<ViewableObject *> getHighlightedGuns(vector<Component *> &components, int allotmentPositionInComponents);

	void work(Vector2int mousePosition, bool isPressed, long timer, int fps, bool rightIsPressed = false);

	void download(string fileName, vector<Component *> &components);
};