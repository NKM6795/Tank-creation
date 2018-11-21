#include "Battle.h"


Battle::Battle(string &fileName, Graphic *forCopyWindow, string tankName) : WorkWithWindow(fileName, forCopyWindow)
{
	components = dataForResources();
	
	//Layers
	{
		vector<Component *> tempComponents = dataForBackgroundBattle();
		components.insert(components.end(), tempComponents.begin(), tempComponents.end());

		fileIn >> fieldWidthForBattle;

		positionForBackground = int(components.size());
		int i = positionForBackground - 5;

		//First layer
		{
			ViewableObject *newObject = new BackgroundForBattle(components[i], i);
			newObject->setHeath(0);
			newObject->setPosition(0, screanHeight);
			objects.push_back(newObject);
			positionsOfBackground.push_back(Vector2int());
		}
		++i;

		//Second layer
		{
			int width = 0, maxWidth = screanWidth + (fieldWidthForBattle - screanWidth) / 2;

			while (width < maxWidth)
			{
				ViewableObject *newObject = new BackgroundForBattle(components[i], i);

				int index = rand() % components[i]->getStruct()->numberOfVariant;
				newObject->setHeath(index);
				objects.push_back(newObject);
				positionsOfBackground.push_back(Vector2int(width, screanHeight));

				width += components[i]->getStruct()->dimensions[index].x;
			}
		}
		++i;

		//Third layer
		{
			int width = 0, maxWidth = screanWidth + (7 * (fieldWidthForBattle - screanWidth)) / 8;

			while (width < maxWidth)
			{
				ViewableObject *newObject = new BackgroundForBattle(components[i], i);

				int index = rand() % components[i]->getStruct()->numberOfVariant;
				newObject->setHeath(index);
				objects.push_back(newObject);
				positionsOfBackground.push_back(Vector2int(width, screanHeight));

				width += components[i]->getStruct()->dimensions[index].x + 50 *  (5 + rand() % 3);
			}
		}
		++i;

		//Fourth layer
		{
			//First step
			{
				int width = 0, maxWidth = fieldWidthForBattle;

				while (width < fieldWidthForBattle)
				{
					ViewableObject *newObject = new BackgroundForBattle(components[i], i);

					newObject->setHeath(0);
					objects.push_back(newObject);
					positionsOfBackground.push_back(Vector2int(width, screanHeight));

					width += components[i]->getStruct()->dimensions[0].x;
				}
			}
			++i;

			//Second step
			{
				int width = 0, maxWidth = fieldWidthForBattle;

				while (width < fieldWidthForBattle)
				{
					ViewableObject *newObject = new BackgroundForBattle(components[i], i);

					int index = rand() % components[i]->getStruct()->numberOfVariant;
					newObject->setHeath(index);
					objects.push_back(newObject);
					positionsOfBackground.push_back(Vector2int(width, screanHeight - 20 - (rand() % 50)));

					width += components[i]->getStruct()->dimensions[index].x + 30 * (2 + rand() % 6);
				}
			}
		}
	}
	
	//Speedometer
	{
		vector<Component *> tempComponents = dataForSpeedometer();
		components.insert(components.end(), tempComponents.begin(), tempComponents.end());

		ViewableObject *newObject = new Speedometer(components.back(), int(components.size()) - 1);
		newObject->setHeath(0);
		newObject->setPosition(screanWidth / 2, screanHeight);
		objects.push_back(newObject);
		positionForSpeedometer = int(objects.size()) - 1;
	}

	graphic->setInformation(components);

	Vector2int position;
	fileIn >> position.x >> position.y;

	fileIn.close();

	tank.name = tankName;
	graphic->setInformation(tank);

	personalTank = new PersonalTank(tank.getViewableObjects());
	personalTank->download(tank.name, components);
	personalTank->setOffset(position);

	updateObjects();
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


void Battle::updateObjects()
{
	Vector2int globalPosition = personalTank->getGlobalOffset();

	for (int i = 1; i < positionForSpeedometer; ++i)
	{
		int indexOffset = 4 - positionForBackground + objects[i]->getIndex();
		float offset = float(globalPosition.x);
		if (indexOffset == 0)
		{
			offset = float(globalPosition.x) / 2.f;
		}
		else if (indexOffset == 1)
		{
			offset = (7.f * float(globalPosition.x)) / 8.f;
		}

		objects[i]->setPosition(positionsOfBackground[i] + Vector2int(int(offset + 0.5f), globalPosition.y));
		objects[i]->needDraw = true;
		if (objects[i]->getPosition().x + objects[i]->getComponentParameter()->dimensions[objects[i]->getHealth()].x <= 0 ||
			objects[i]->getPosition().x >= screanWidth)
		{
			objects[i]->needDraw = false;
		}
	}

	objects[positionForSpeedometer]->setHeath(((personalTank->getSpeed() < 0 ? -7 : 7) * personalTank->getSpeed() - 1) / personalTank->getMaxSpeed());
	objects[positionForSpeedometer]->getComponentParameter()->tiltAngle = (50.f * personalTank->getSpeed()) / float(personalTank->getMaxSpeed());
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
				button["Exit"].setActivateAnAction(true);
			}
			else if (graphic->getEvent().type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Right))
			{
				personalTank->setDrive(true);
			}
			else if (graphic->getEvent().type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Left))
			{
				personalTank->setDrive(false);
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

		//Work with personal tank
		personalTank->work(mousePosition * (graphic->hasFocus() ? 1 : -100), Mouse::isButtonPressed(Mouse::Left) && graphic->hasFocus(), timer, timeForWork, Mouse::isButtonPressed(Mouse::Right) && graphic->hasFocus());

		updateObjects();
		tank.setOffset(personalTank->getOffsetForTank());

		graphic->draw(button, objects, tank, timer);
	}
}