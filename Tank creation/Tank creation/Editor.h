#pragma once


#include "WorkWithWindow.h"
#include "ExitFromEditor.h"
#include "NotAvailable.h"
#include "TankEditor.h"


class Editor : public WorkWithWindow
{
	int backgroundXCoordinate, backgroundYCoordinate, backgroundWidth, backgroundHeight;
	string backgroundNameOfPicture;

	vector<Component *> components;

	vector<Object *> objects;

	Tank tank;

	TankEditor *tankEditor;

public:
	Editor(string &fileName);

	Editor(string &fileName, Graphic *forCopyWindow);

	~Editor();

	void work();
};