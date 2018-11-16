#pragma once


#include "WorkWithWindow.h"


class TankSelection : public WorkWithWindow
{
	vector<Component *> components;

	vector<Object *> objects;

	List *list;

public:
	TankSelection(string &fileName);

	TankSelection(string &fileName, Graphic *forCopyWindow);

	~TankSelection();

	void work();
};