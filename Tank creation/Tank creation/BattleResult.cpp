#include "BattleResult.h"


BattleResult::BattleResult(string &fileName, Graphic *forCopyWindow, string massage1, string massage2, string massage3) : NotificationWindow(fileName, forCopyWindow)
{
	fileIn.close();

	text[0] = massage1;
	text[1] = massage2;
	text[2] = massage3;
	text[3] = to_string(maxCost);
}


void BattleResult::work()
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
			windowResult = "Ok/";

			windowIsOpen = false;
			return;
		}

		graphic->draw(text, button);
	}
}