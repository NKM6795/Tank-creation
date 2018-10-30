#include "NotificationWindow.h"


NotificationWindow::NotificationWindow(string &fileName, Graphic *forCopyWindow) : WorkWithWindow(fileName, forCopyWindow)
{
	fileIn >> width >> height >> needInputField;

	graphic->setInformation(width, height, needInputField, forCopyWindow->getRenderTexture());
}
