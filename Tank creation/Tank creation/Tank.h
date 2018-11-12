#pragma once


#include "Background.h"
#include "SmallBlock.h"
#include "BigBlock.h"
#include "EngineRoom.h"
#include "Track.h"
#include "Gun.h"


class Tank
{
protected:
	vector<vector<Object *> > objects;

	int xOffset,
		yOffset;

	int dataArraySize;

	int dimension;

public:
	Tank(int dataArraySize = 30, int dimension = 600);

	~Tank();

	virtual Vector2int getOffset();
	virtual void setOffset(Vector2int offset);
	virtual void setOffset(int x, int y);

	virtual int getDimension();
	virtual void setDimension(int dim);

	virtual vector<vector<Object *> > &getObjects();
};