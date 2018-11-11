#pragma once


#include "WorkWithWindow.h"
#include "Editor.h"
#include "NotAvailable.h"


class MainMenu : public WorkWithWindow
{
	vector<Component *> components;

	vector<Object *> objects;

public:
	MainMenu(string &fileName);

	~MainMenu();
		
	void work();
};