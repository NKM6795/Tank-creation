#pragma once


#include "NotificationWindow.h"


class ExitFromEditor : public NotificationWindow
{
	using NotificationWindow::needInputField;
	using NotificationWindow::inputField;

public:
	ExitFromEditor(string &fileName, Graphic *forCopyWindow);


	void work();
};