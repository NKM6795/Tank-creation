#include "NotificationWindow.h"


NotificationWindow::NotificationWindow(string &fileName) : WorkWithWindow(fileName)
{
	fileIn.close();
}

NotificationWindow::NotificationWindow(string &fileName, Graphic *forCopyWindow) : WorkWithWindow(fileName, forCopyWindow)
{
	fileIn >> width >> height >> needInputField;
	getline(fileIn, inputField);
	getline(fileIn, inputField);

	fileIn.close();
}
