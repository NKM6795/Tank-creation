#include "Tutorial.h"


Tutorial::Tutorial(string &fileName, Graphic *forCopyWindow) : WorkWithWindow(fileName, forCopyWindow)
{
	fileIn.close();
}

Tutorial::~Tutorial()
{

}


void Tutorial::work()
{
	if (graphic->getTimeAsMilliseconds() / coefficientForTime - timer >= timeForWork)
	{
		timer += timeForWork;
		
		mousePosition = graphic->getPositionOfMouse();

		while (graphic->pollEvent())
		{
			if (graphic->getEvent().type == Event::Closed || (graphic->getEvent().type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Escape)))
			{
				button["Exit"].setActivateAnAction(true);
			}
		}


		for (auto i = button.begin(); i != button.end(); ++i)
		{
			i->second.work(mousePosition * (graphic->hasFocus() ? 1 : -100), Mouse::isButtonPressed(Mouse::Left) && graphic->hasFocus(), timer, timeForWork);
		}
		if (button["Exit"].getActivateAnAction())
		{
			windowIsOpen = false;
			return;
		}

		graphic->draw(button);
	}
}