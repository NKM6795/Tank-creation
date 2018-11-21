#pragma once


#include "NotificationWindow.h"
#include "NotAvailable.h"
#include "SaveTank.h"
#include "TankEditor.h"

class ExitFromEditor : public NotificationWindow
{
	TankEditor *tankEditor;

	string tankName;

public:
	ExitFromEditor(string &fileName, Graphic *forCopyWindow, string tankName, TankEditor *tankEditor);


	void work();
};