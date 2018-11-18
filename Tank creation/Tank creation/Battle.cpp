#include "Battle.h"


Battle::Battle(string &fileName, Graphic *forCopyWindow, string tankName) : WorkWithWindow(fileName, forCopyWindow)
{
	components = dataForResources();
	graphic->setInformation(components);

	Vector2int position;

	fileIn >> position.x >> position.y;

	fileIn.close();

	tank.name = tankName;
	tank.setOffset(position);
	graphic->setInformation(tank);

	personalTank = new PersonalTank(tank.getViewableObjects());
	personalTank->download(tank.name, components);
}

Battle::~Battle()
{
	tank.~Tank();

	while (components.size() > 0)
	{
		delete components.back();
		components.pop_back();
	}

	delete personalTank;
}


void Battle::work()
{
	if (graphic->getTimeAsMilliseconds() / coefficientForTime - timer >= timeForWork)
	{
		timer += timeForWork;

		mousePosition = graphic->getPositionOfMouse();

		while (graphic->pollEvent())
		{
			if (graphic->getEvent().type == Event::Closed || (graphic->getEvent().type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Escape)))
			{
				windowIsOpen = false;
				return;
			}
		}


		for (auto i = button.begin(); i != button.end(); ++i)
		{
			i->second.work(mousePosition * (graphic->hasFocus() ? 1 : -100), Mouse::isButtonPressed(Mouse::Left) && graphic->hasFocus(), timer, timeForWork);
		}

		graphic->draw(button, tank, timer);
	}
}