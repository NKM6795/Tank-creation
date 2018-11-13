#pragma once


#include "Tank.h"


class TankEditor
{
	vector<vector<Object *> > *objects;

	int xOffset,
		yOffset;

	int dataArraySize;

	bool checkFreePlace(vector<vector<bool> > &smallTank, int widht, int height, int i, int j);

public:
	TankEditor(vector<vector<Object *> > &objects, int dataArraySize = 30);

	~TankEditor();

	Vector2int getOffset();
	void setOffset(Vector2int offset);
	void setOffset(int x, int y);

	static Object *getObject(Component *component, int index);

	Vector2int getFreePlace(Component *component, Vector2int mousePosition);
	Object *getFreePlace(Component *component, int index, Vector2int mousePosition);
};