#pragma once


#include "NotificationWindow.h"
#include "NotAvailable.h"


class RenameTank : public NotificationWindow
{

public:
	RenameTank(string &fileName, Graphic *forCopyWindow, string tankName = "");


	void work();
};