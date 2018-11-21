#pragma once


#include "NotificationWindow.h"


class NotAvailable : public NotificationWindow
{

public:
	NotAvailable(string &fileName, Graphic *forCopyWindow, string massage = "Not available");


	void work();
};