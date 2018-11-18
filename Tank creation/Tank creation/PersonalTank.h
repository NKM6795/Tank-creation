#pragma once


#include "TankEditor.h"


class PersonalTank
{
	vector<vector<ViewableObject *> > *objects;

	int xOffset,
		yOffset;

	int dataArraySize;

public:
	PersonalTank(vector<vector<ViewableObject *> > &objects, int dataArraySize = 30);

	~PersonalTank();

	Vector2int getOffset();
	void setOffset(Vector2int offset);
	void setOffset(int x, int y);

	void download(string fileName, vector<Component *> &components);
};