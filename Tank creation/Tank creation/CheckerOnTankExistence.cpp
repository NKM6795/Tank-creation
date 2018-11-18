#include "CheckerOnTankExistence.h"


CheckerOnTankExistence::CheckerOnTankExistence(string &fileName, Graphic *forCopyWindow) : NotificationWindow(fileName, forCopyWindow)
{
	fileIn.close();
}


void CheckerOnTankExistence::work()
{
	if (graphic->getTimeAsMilliseconds() / coefficientForTime - timer >= timeForWork)
	{
		timer += timeForWork;

		mousePosition = graphic->getPositionOfMouse();

		while (graphic->pollEvent())
		{
			if (graphic->getEvent().type == Event::Closed || (graphic->getEvent().type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Escape)))
			{
				windowResult = "Cancel/";

				windowIsOpen = false;
				return;
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
		else if (button["Yes"].getActivateAnAction())
		{
			windowResult = "Yes/";

			windowIsOpen = false;
			return;
		}

		graphic->draw(button);
	}
}