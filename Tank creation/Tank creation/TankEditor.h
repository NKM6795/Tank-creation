#pragma once


#include "Tank.h"


class TankEditor
{
	vector<vector<Object *> > *objects;

	int dataArraySize;

public:
	TankEditor(vector<vector<Object *> > &objects, int dataArraySize = 30);

	~TankEditor();


};