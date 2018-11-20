#include "Battle.h"


Battle::Battle(string &fileName, Graphic *forCopyWindow, string tankName) : WorkWithWindow(fileName, forCopyWindow)
{
	components = dataForResources();
	vector<Component *> tempComponents = dataForBackgroundBattle();
	components.insert(components.end(), tempComponents.begin(), tempComponents.end());
	graphic->setInformation(components);

	fileIn >> fieldWidthForBattle;

	//Layers
	{
		int i = int(components.size()) - 5;

		//First layer
		{
			ViewableObject *newObject = new BackgroundForBattle(components[i], i);
			newObject->setHeath(0);
			newObject->setPosition(0, screanHeight);
			objectsForBackground.push_back(newObject);
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
				objectsForBackground.push_back(newObject);
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
				objectsForBackground.push_back(newObject);
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
					objectsForBackground.push_back(newObject);
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
					objectsForBackground.push_back(newObject);
					positionsOfBackground.push_back(Vector2int(width, screanHeight - 20 - (rand() % 50)));

					width += components[i]->getStruct()->dimensions[index].x + 30 * (2 + rand() % 6);
				}
			}
		}
	}
	
	Vector2int position;
	fileIn >> position.x >> position.y;

	fileIn.close();

	tank.name = tankName;
	graphic->setInformation(tank);

	personalTank = new PersonalTank(tank.getViewableObjects());
	personalTank->download(tank.name, components);
	personalTank->setOffset(position);

	updatePositionOfBackground();
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


void Battle::updatePositionOfBackground()
{
	Vector2int globalPosition = personalTank->getGlobalOffset();

	for (int i = 1; i < int(objectsForBackground.size()); ++i)
	{
		int indexOffset = 4 - int(components.size()) + objectsForBackground[i]->getIndex();
		float offset = float(globalPosition.x);
		if (indexOffset == 0)
		{
			offset = float(globalPosition.x) / 2.f;
		}
		else if (indexOffset == 1)
		{
			offset = (7.f * float(globalPosition.x)) / 8.f;
		}

		objectsForBackground[i]->setPosition(positionsOfBackground[i] + Vector2int(int(offset + 0.5f), globalPosition.y));
		objectsForBackground[i]->needDraw = true;
		if (objectsForBackground[i]->getPosition().x + objectsForBackground[i]->getComponentParameter()->dimensions[objectsForBackground[i]->getHealth()].x <= 0 ||
			objectsForBackground[i]->getPosition().x >= screanWidth)
		{
			objectsForBackground[i]->needDraw = false;
		}
	}
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

		updatePositionOfBackground();
		tank.setOffset(personalTank->getOffsetForTank());

		graphic->draw(button, objectsForBackground, tank, timer);
	}
}