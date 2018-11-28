#pragma once


#include "WorkWithWindow.h"
#include "Editor.h"
#include "NotAvailable.h"
#include "TankSelection.h"
#include "Battle.h"
#include "Tutorial.h"


class MainMenu : public WorkWithWindow
{
	bool needOpenBattle;

public:
	MainMenu(string &fileName);

	~MainMenu();
		
	void work();
};