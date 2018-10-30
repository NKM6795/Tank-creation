#pragma once


#include "WorkWithWindow.h"


class NotificationWindow : public WorkWithWindow
{
protected:
	int width;
	int height;
	
	bool needInputField;
	string inputField;

public:
	NotificationWindow(string &fileName);

	NotificationWindow(string &fileName, Graphic *forCopyWindow);


	virtual void work() = 0;
};