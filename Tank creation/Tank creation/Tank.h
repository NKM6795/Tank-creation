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

public:
	Tank(int dataArraySize = 30);

	~Tank();

	virtual Vector2int getOffset();
	virtual void setOffset(Vector2int offset);
	virtual void setOffset(int x, int y);

	virtual vector<vector<Object *> > &getObjects();
};