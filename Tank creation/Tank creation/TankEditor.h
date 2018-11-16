#pragma once


#include "Tank.h"


class TankEditor
{
	vector<vector<ViewableObject *> > *objects;

	int xOffset,
		yOffset;

	int dataArraySize;

	bool checkFreePlace(vector<vector<bool> > &smallTank, int widht, int height, int i, int j);

	void addViewableObjectOnPosition(Component *component, int index, Vector2int position);

	void dfs(vector<vector<bool> > &smallTank, int i, int j);

public:
	TankEditor(vector<vector<ViewableObject *> > &objects, int dataArraySize = 30);

	~TankEditor();

	Vector2int getOffset();
	void setOffset(Vector2int offset);
	void setOffset(int x, int y);

	static ViewableObject *getViewableObject(Component *component, int index);
	ViewableObject *getViewableObject(Vector2int mousePosition);

	static ViewableObject *getCopy(ViewableObject *object);

	Vector2int getFreePlace(Component *component, Vector2int mousePosition);
	ViewableObject *getFreePlace(Component *component, int index, Vector2int mousePosition);

	void addViewableObject(Component *component, int index, Vector2int mousePosition);

	void removeViewableObject(Vector2int mousePosition);

	void clear();

	bool completenessСheck();

	void save(string fileName);
	void download(string fileName, vector<Component *> &components);
};