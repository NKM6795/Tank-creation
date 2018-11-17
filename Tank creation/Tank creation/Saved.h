#pragma once


#include "NotificationWindow.h"


class Saved : public NotificationWindow
{

public:
	Saved(string &fileName, Graphic *forCopyWindow);


	void work();
};