#pragma once


#include "TankEditor.h"
#include "Allotment.h"
#include "Bullet.h"
#include "WorkWithBullet.h"


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

	bool highlightingUpdated;
	bool needUpdateTank;
	vector<vector<Vector2int> > grupyAllocation;
	vector<Vector2int> highlightedItems;
	bool controlIsPressed;
	int numberIsPressed;

	bool needAddBullet;
	vector<ViewableObject *> bullets;

	void updateTracks();

	float getAngelForGun(ViewableObject *gun, Vector2int mousePosition);
	void updateGun(Vector2int mousePosition);

	float getSpeedForVerticalGun(Vector2float first, Vector2float second, float angel);
	bool checkYCoordinate(Vector2float first, Vector2float second, float angel, float speedOfBullet);
	//return:
	//0 - ok
	//1 - need to turn left
	//-1 - need to turn right
	int checkToGetIntoHimself(float angel, float speedOfBullet, Vector2float position);
	void makeShots(Vector2int mousePosition, vector<Component *> &components, int bulletPositionInComponents, long timer);

	void removeHangingObjects();

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

	bool getHighlightingUpdated(bool updated = false);
	bool getNeedUpdateTank();

	bool needHighlighte();
	vector<ViewableObject *> getHighlightedGuns(vector<Component *> &components, int allotmentPositionInComponents);

	bool getNeedAddBullet();
	vector<ViewableObject *> getBullets();

	void work(Vector2int mousePosition, bool isPressed, long timer, int fps, vector<Component *> &components, int bulletPositionInComponents, vector<ViewableObject *> &bullets, bool rightIsPressed = false);

	void download(string fileName, vector<Component *> &components);
};