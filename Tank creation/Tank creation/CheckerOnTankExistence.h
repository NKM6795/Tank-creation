#pragma once


#include "NotificationWindow.h"


class CheckerOnTankExistence : public NotificationWindow
{

public:
	CheckerOnTankExistence(string &fileName, Graphic *forCopyWindow);


	void work();
};