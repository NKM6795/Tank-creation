#pragma once


#include "NotificationWindow.h"
#include "RenameTank.h"
#include "Saved.h"
#include "CheckerOnTankExistence.h"


class SaveTank : public NotificationWindow
{
	string tankName;

public:
	SaveTank(string &fileName, Graphic *forCopyWindow);


	void work();
};