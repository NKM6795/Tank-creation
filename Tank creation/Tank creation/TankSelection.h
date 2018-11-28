#pragma once


#include "WorkWithWindow.h"


class TankSelection : public WorkWithWindow
{
	vector<Component *> components;

	vector<ViewableObject *> objects;

	int listWidth,
		listHeight;
	int listObjectWidth,
		listObjectHeight;
	int listFragmentHeight;
	Vector2int listPosition;
	List *list;

	void deleteSelectedElement();

public:
	TankSelection(string &fileName);

	TankSelection(string &fileName, Graphic *forCopyWindow, bool needToLimit = false);

	~TankSelection();

	void work();
};