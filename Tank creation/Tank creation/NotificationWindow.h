#pragma once


#include "WorkWithWindow.h"


class NotificationWindow : public WorkWithWindow
{
protected:
	int width;
	int height;
	
	bool needInputField;
	int notificationXCoordinate;
	int notificationYCoordinate;
	int notificationCharacterSize;
	int maxSizeOfText;
	string inputField;
	string fontNameForNotification;

	void inputText(int unicode);

public:
	NotificationWindow(string &fileName, Graphic *forCopyWindow);


	virtual void work() = 0;
};