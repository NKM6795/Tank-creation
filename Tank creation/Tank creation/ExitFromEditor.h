#pragma once


#include "NotificationWindow.h"


class ExitFromEditor : public NotificationWindow
{

public:
	ExitFromEditor(string &fileName, Graphic *forCopyWindow);


	void work();
};