#include "RenameTank.h"


RenameTank::RenameTank(string &fileName, Graphic *forCopyWindow, string tankName) : NotificationWindow(fileName, forCopyWindow)
{
	fileIn.close();

	inputField = tankName;
}


void RenameTank::work()
{
	if (graphic->getTimeAsMilliseconds() / coefficientForTime - timer >= timeForWork)
	{
		timer += timeForWork;

		if (needWindowResult)
		{
			if (windowResult == "Yes/")
			{
				windowResult = "Rename/" + tankName;

				windowIsOpen = false;
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


		for (auto i = button.begin(); i != button.end(); ++i)
		{
			i->second.work(mousePosition * (graphic->hasFocus() ? 1 : -100), Mouse::isButtonPressed(Mouse::Left) && graphic->hasFocus(), timer, timeForWork);
		}
		if (button["Cancel"].getActivateAnAction())
		{
			windowResult = "Cancel/";

			windowIsOpen = false;
			return;
		}
		else if (button["Save"].getActivateAnAction())
		{
			tankName = inputField;

			if (inputField == "")
			{
				needNewWindow = true;

				string fileName = "Data/Data for not available.dat";

				graphic->drawInRenderTexture(button);

				newWindow = new NotAvailable(fileName, graphic);

				button["Save"].setActivateAnAction(false);
			}
			else
			{
				ifstream checkOnExistence("Data/Tanks/" + tankName + ".tnk");
				if (checkOnExistence)
				{
					checkOnExistence.close();

					needNewWindow = true;
					needWindowResult = true;

					string fileName = "Data/Data for checker on tank existence.dat";

					graphic->drawInRenderTexture(button);

					newWindow = new CheckerOnTankExistence(fileName, graphic);

					button["Save"].setActivateAnAction(false);

					return;
				}
				else
				{
					checkOnExistence.close();

					windowResult = "Rename/" + tankName;

					windowIsOpen = false;
					return;
				}
			}
		}

		graphic->draw(button, inputField);
	}
}