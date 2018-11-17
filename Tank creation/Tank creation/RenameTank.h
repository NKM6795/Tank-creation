#pragma once


#include "NotificationWindow.h"
#include "NotAvailable.h"
#include "CheckerOnTankExistence.h"


class RenameTank : public NotificationWindow
{
	string tankName;

public:
	RenameTank(string &fileName, Graphic *forCopyWindow, string tankName = "");


	void work();
};