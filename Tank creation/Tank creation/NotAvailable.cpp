#include "NotAvailable.h"


NotAvailable::NotAvailable(string &fileName, Graphic *forCopyWindow, string massage) : NotificationWindow(fileName, forCopyWindow)
{
	fileIn.close();

	text[1] = massage;
}


void NotAvailable::work()
{
	if (graphic->getTimeAsMilliseconds() / coefficientForTime - timer >= timeForWork)
	{
		timer += timeForWork;

		mousePosition = graphic->getPositionOfMouse();

		while (graphic->pollEvent())
		{
			if (graphic->getEvent().type == Event::Closed || (graphic->getEvent().type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Escape)) || (graphic->getEvent().type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Enter)))
			{
				button["Ok"].setActivateAnAction(true);
			}
		}


		for (auto i = button.begin(); i != button.end(); ++i)
		{
			i->second.work(mousePosition * (graphic->hasFocus() ? 1 : -100), Mouse::isButtonPressed(Mouse::Left) && graphic->hasFocus(), timer, timeForWork);
		}
		if (button["Ok"].getActivateAnAction())
		{
			windowIsOpen = false;
			return;
		}

		graphic->draw(text, button);
	}
}