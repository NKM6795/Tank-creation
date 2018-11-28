#pragma once


#include "Tank.h"


class TankEditor
{
	vector<vector<ViewableObject *> > *objects;

	int xOffset,
		yOffset;

	int dataArraySize;

	bool needUpdateTank;

	int cost;

	bool checkFreePlace(vector<vector<bool> > &smallTank, int widht, int height, int i, int j);

	void addViewableObjectOnPosition(Component *component, int index, Vector2int position);

public:
	enum Direct
	{
		Nowhere,
		All,
		Up,
		Down,
		Left,
		Right
	};


	TankEditor(vector<vector<ViewableObject *> > &objects, int dataArraySize = 30);

	~TankEditor();

	int getCost();

	Vector2int getOffset();
	void setOffset(Vector2int offset);
	void setOffset(int x, int y);

	static ViewableObject *getViewableObject(Component *component, int index);
	ViewableObject *getViewableObject(Vector2int mousePosition);

	static ViewableObject *getCopy(ViewableObject *object);

	Vector2int getFreePlace(Component *component, Vector2int mousePosition);
	ViewableObject *getFreePlace(Component *component, int index, Vector2int mousePosition);

	bool addViewableObject(Component *component, int index, Vector2int mousePosition);

	bool removeViewableObject(Vector2int mousePosition);

	void clear();

	bool isEmpty();

	static void dfs(vector<vector<pair<Direct, Direct> > > &smallTank, int i, int j);
	static vector<vector<pair<Direct, Direct> > > getSmallTankForDfs(vector<vector<ViewableObject *> > &objectsForSmallTank);
	vector<vector<pair<Direct, Direct> > > getSmallTankForDfs();

	int completenessСheck();
	vector<ViewableObject *> getWrongObjects();

	bool getNeedUpdateTank();

	void save(string fileName);
	void download(string fileName, vector<Component *> &components);
};