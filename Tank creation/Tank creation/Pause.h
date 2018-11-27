#pragma once


#include "NotificationWindow.h"


class Pause : public NotificationWindow
{

public:
	Pause(string &fileName, Graphic *forCopyWindow);


	void work();
};