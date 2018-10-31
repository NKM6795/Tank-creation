#pragma once


#include "NotificationWindow.h"


class NotAvailable : public NotificationWindow
{

public:
	NotAvailable(string &fileName, Graphic *forCopyWindow);


	void work();
};