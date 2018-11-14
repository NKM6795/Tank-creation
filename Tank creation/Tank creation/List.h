#pragma once


#include "Tank.h"
#include "Button.h"


class List
{
	vector<Object *> objects;

	int objectWidth,
		objectHeight;
	int fragmentHeight;

	int width,
		height;
	int xCoordinate,
		yCoordinate;

	int index;
	int position;
	float conversionFactor;

	bool needButton;
	Button *button;
	int deltaPosition;

	int separationThickness;

	bool activateAnAction;

	bool needDirect;
	bool up;

	void updateObject();

public:
	List(vector<Object *> objects, int width, int height, int xCoordinate, int yCoordinate, int objectWidth = 60, int objectHeight = 40, int fragmentHeight = 50, int separationThickness = 1);

	~List();

	int getIndex();

	int getPosition();

	Button *getButton();

	vector<Object *> &getObjects();

	Vector2int getOffset();
	void setOffset(Vector2int offset);
	void setOffset(int x, int y);

	void setDirect(bool up);

	int getFragmentHeight();

	int getWidth();
	int getHeight();

	void work(Vector2int mousePosition, bool isPressed, long timer, int fps);
	
	bool getActivateAnAction();
};