#pragma once


#include "WorkWithWindow.h"
#include "ExitFromEditor.h"
#include "NotAvailable.h"
#include "TankEditor.h"
#include "SaveTank.h"
#include "RenameTank.h"


class Editor : public WorkWithWindow
{
	int backgroundXCoordinate, backgroundYCoordinate, backgroundWidth, backgroundHeight;
	string backgroundNameOfPicture;

	vector<Component *> components;
	vector<ViewableObject *> objects;
	pair<Vector2int, Vector2int> oldViewableObject;
	
	bool tankIsChanged;
	Tank tank;
	TankEditor *tankEditor;

	int listWidth,
		listHeight;
	Vector2int listPosition;
	List *list;

public:
	Editor(string &fileName);

	Editor(string &fileName, Graphic *forCopyWindow, string tankName = "");

	~Editor();

	void work();
};