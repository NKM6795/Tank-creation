#include "Saved.h"


Saved::Saved(string &fileName, Graphic *forCopyWindow) : NotificationWindow(fileName, forCopyWindow)
{
	fileIn.close();
}


void Saved::work()
{
	if (graphic->getTimeAsMilliseconds() / coefficientForTime - timer >= timeForWork)
	{
		timer += timeForWork;

		mousePosition = graphic->getPositionOfMouse();

		while (graphic->pollEvent())
		{
			if (graphic->getEvent().type == Event::Closed || (graphic->getEvent().type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Escape)))
			{
				windowResult = "Saved/";

				windowIsOpen = false;
				return;
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
				if (button[i].getStruct()->buttonName == "Ok")
				{
					windowResult = "Saved/";

					windowIsOpen = false;
					return;
				}
			}

		}

		graphic->draw(button);
	}
}