#include "SaveTank.h"


SaveTank::SaveTank(string &fileName, Graphic *forCopyWindow) : NotificationWindow(fileName, forCopyWindow)
{
	fileIn.close();
}


void SaveTank::work()
{
	if (graphic->getTimeAsMilliseconds() / coefficientForTime - timer >= timeForWork)
	{
		timer += timeForWork;

		if (needWindowResult)
		{
			if (windowResult == "Cancel/")
			{
				windowIsOpen = false;
				return;
			}
			else if (windowResult == "Saved/")
			{
				windowResult += tankName;

				windowIsOpen = false;
				return;
			}
			else if (windowResult.size() > 7 && windowResult.substr(0, 7) == "Rename/")
			{
				tankName = windowResult;

				needNewWindow = true;
				needWindowResult = true;
					
				string fileName = "Data/Data for saved.dat";

				graphic->drawInRenderTexture(button);

				newWindow = new Saved(fileName, graphic);
					
				return;
			}
			needWindowResult = false;
		}

		mousePosition = graphic->getPositionOfMouse();

		while (graphic->pollEvent())
		{
			if (graphic->getEvent().type == Event::Closed || (graphic->getEvent().type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Escape)))
			{
				windowResult = "Cancel/";

				windowIsOpen = false;
				return;
			}
			if (graphic->getEvent().type == Event::TextEntered)
			{
				inputText(graphic->getEvent().text.unicode);
			}
		}


		for (int i = 0; i < numberOfButton; ++i)
		{
			button[i].work(mousePosition * (graphic->hasFocus() ? 1 : -100), Mouse::isButtonPressed(Mouse::Left) && graphic->hasFocus(), timer, timeForWork);
		}

		for (int i = 0; i < numberOfButton; ++i)
		{
			if (button[i].getActivateAnAction())
			{
				if (button[i].getStruct()->buttonName == "Cancel")
				{
					windowResult = "Cancel/";

					windowIsOpen = false;
					return;
				}
				else if (button[i].getStruct()->buttonName == "Enter name")
				{
					needNewWindow = true;
					needWindowResult = true;

					string fileName = "Data/Data for rename tank.dat";

					graphic->drawInRenderTexture(button);

					newWindow = new RenameTank(fileName, graphic);

					button[i].setActivateAnAction(false);
				}
			}

		}

		graphic->draw(button);
	}
}