#pragma once


#include "WorkWithWindow.h"
#include "Editor.h"
#include "NotAvailable.h"


class MainMenu : public WorkWithWindow
{

public:
	MainMenu(string &fileName);

	~MainMenu();
		
	void work();
};