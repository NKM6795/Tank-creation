#pragma once


#include "NotificationWindow.h"
#include "NotAvailable.h"
#include "SaveTank.h"


class ExitFromEditor : public NotificationWindow
{
	bool canSave;

	string tankName;

public:
	ExitFromEditor(string &fileName, Graphic *forCopyWindow, string tankName, bool canSave);


	void work();
};