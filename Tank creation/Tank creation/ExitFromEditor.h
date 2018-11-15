#pragma once


#include "NotificationWindow.h"
#include "NotAvailable.h"
#include "SaveTank.h"


class ExitFromEditor : public NotificationWindow
{
	bool canSave;

public:
	ExitFromEditor(string &fileName, Graphic *forCopyWindow, bool canSave);


	void work();
};