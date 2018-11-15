#pragma once


#include "WorkWithWindow.h"
#include "ExitFromEditor.h"
#include "NotAvailable.h"
#include "TankEditor.h"
#include "SaveTank.h"


class Editor : public WorkWithWindow
{
	int backgroundXCoordinate, backgroundYCoordinate, backgroundWidth, backgroundHeight;
	string backgroundNameOfPicture;

	vector<Component *> components;
	vector<Object *> objects;
	pair<Vector2int, Vector2int> oldObject;

	Tank tank;
	TankEditor *tankEditor;

	List *list;

public:
	Editor(string &fileName);

	Editor(string &fileName, Graphic *forCopyWindow);

	~Editor();

	void work();
};