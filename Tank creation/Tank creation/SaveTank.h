#pragma once


#include "NotificationWindow.h"
#include "NotAvailable.h"


class SaveTank : public NotificationWindow
{

public:
	SaveTank(string &fileName, Graphic *forCopyWindow);


	void work();
};