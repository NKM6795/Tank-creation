#include "NotificationWindow.h"


void NotificationWindow::inputText(int unicode)
{
	if (int(inputField.size()) < maxSizeOfText)
	{
		if (unicode == 8 || (unicode >= 48 && unicode <= 57) || (unicode >= 65 && unicode <= 90) || (unicode >= 97 && unicode <= 122))
		{
			if (unicode == 8 && inputField.size() > 0)
			{
				inputField.pop_back();
			}
			else
			{
				inputField.push_back(char(unicode));
			}
		}
	}
}


NotificationWindow::NotificationWindow(string &fileName, Graphic *forCopyWindow) : WorkWithWindow(fileName, forCopyWindow)
{
	fileIn >> width >> height >> needInputField >> notificationXCoordinate >> notificationYCoordinate >> notificationCharacterSize >> maxSizeOfText;

	getline(fileIn, fontNameForNotification);
	getline(fileIn, fontNameForNotification);

	graphic->setInformation(width, height, needInputField, notificationXCoordinate, notificationYCoordinate, notificationCharacterSize, fontNameForNotification, forCopyWindow->getRenderTexture());
}
