#include "Battle.h"


Battle::Battle(string &fileName, Graphic *forCopyWindow, string tankName) : WorkWithWindow(fileName, forCopyWindow)
{
	components = dataForResources(true);
	
	firstUpdateOfBackgrounds = true;
	//Layers
	{
		vector<Component *> tempComponents = dataForBackgroundBattle();
		components.insert(components.end(), tempComponents.begin(), tempComponents.end());

		fileIn >> fieldWidthForBattle;

		int i = int(components.size()) - 5;

		//First layer
		{
			ViewableObject *newObject = new BackgroundForBattle(components[i], i);
			newObject->setHeath(0);
			newObject->setPosition(0, screanHeight);
			backgroundObjects.push_back(newObject);
			positionsOfBackground.push_back(Vector2int());

			backgroundAndSpeedometerObjects.push_back(newObject);
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
				backgroundObjects.push_back(newObject);
				positionsOfBackground.push_back(Vector2int(width, screanHeight));

				backgroundAndSpeedometerObjects.push_back(newObject);

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
				backgroundObjects.push_back(newObject);
				positionsOfBackground.push_back(Vector2int(width, screanHeight));

				backgroundAndSpeedometerObjects.push_back(newObject);

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
					backgroundObjects.push_back(newObject);
					positionsOfBackground.push_back(Vector2int(width, screanHeight));

					backgroundAndSpeedometerObjects.push_back(newObject);

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
					backgroundObjects.push_back(newObject);
					positionsOfBackground.push_back(Vector2int(width, screanHeight - 20 - (rand() % 50)));

					backgroundAndSpeedometerObjects.push_back(newObject);

					width += components[i]->getStruct()->dimensions[index].x + 30 * (2 + rand() % 6);
				}
			}
		}
	}
	
	//Speedometer
	{
		vector<Component *> tempComponents = dataForSpeedometer();
		components.insert(components.end(), tempComponents.begin(), tempComponents.end());

		speedometerObjects = new Speedometer(components.back(), int(components.size()) - 1);
		speedometerObjects->setHeath(0);
		speedometerObjects->setPosition(screanWidth / 2, screanHeight);

		backgroundAndSpeedometerObjects.push_back(speedometerObjects);
	}

	//Allotment
	{
		vector<Component *> tempComponents = dataForAllotment();
		allotmentPositionInComponents = int(components.size());
		components.insert(components.end(), tempComponents.begin(), tempComponents.end());
	}

	//Bullet
	{
		vector<Component *> tempComponents = dataForBullet();
		bulletPositionInComponents = int(components.size());
		components.insert(components.end(), tempComponents.begin(), tempComponents.end());
	}

	graphic->setInformation(screanWidth, screanHeight);

	graphic->setInformation(components);

	Vector2int position;
	fileIn >> position.x >> position.y;


	leftTank.name = tankName;
	graphic->setInformation(leftTank);

	personalTank = new PersonalTank(leftTank.getViewableObjects(), fieldWidthForBattle, screanWidth);
	personalTank->download(leftTank.name, components);
	personalTank->setOffset(position);

	fileIn >> position.x >> position.y;
	fileIn.close();

	rightTank.name = tankName;
	graphic->setInformation(rightTank, false);

	botTank = new BotTank(rightTank.getViewableObjects(), fieldWidthForBattle, screanWidth);
	botTank->download(rightTank.name, components);
	botTank->setOffset(position);
	botTank->setGlobalOffset(Vector2int(-fieldWidthForBattle + screanWidth, 0));

	lengthBetweenTanks = getLengthBetweenTanks(leftTank, rightTank) * 20;

	updateObjects();
}

Battle::~Battle()
{
	leftTank.~Tank();
	rightTank.~Tank();

	while (components.size() > 0)
	{
		delete components.back();
		components.pop_back();
	}

	while (backgroundAndSpeedometerObjects.size() > 0)
	{
		delete backgroundAndSpeedometerObjects.back();
		backgroundAndSpeedometerObjects.pop_back();
	}

	while (bullets.size() > 0)
	{
		delete bullets.back();
		bullets.pop_back();
	}

	while (allotmentObjects.size() > 0)
	{
		delete allotmentObjects.back();
		allotmentObjects.pop_back();
	}

	delete personalTank;
	delete botTank;
}


void Battle::updateObjects()
{
	Vector2int globalPosition = personalTank->getGlobalOffset();

	int offsetIndex = 0, objectIndex = backgroundObjects[1]->getIndex();

	for (int i = 1; i < int(backgroundObjects.size()); ++i)
	{
		if (objectIndex != backgroundObjects[i]->getIndex())
		{
			++offsetIndex;
		}

		float offset = float(globalPosition.x);
		if (offsetIndex == 0)
		{
			offset = float(globalPosition.x) / 2.f;
		}
		else if (offsetIndex == 1)
		{
			offset = (7.f * float(globalPosition.x)) / 8.f;
		}

		backgroundObjects[i]->setPosition(positionsOfBackground[i] + Vector2int(int(offset + 0.5f), globalPosition.y));
		backgroundObjects[i]->needDraw = true;
		if (backgroundObjects[i]->getPosition().x + backgroundObjects[i]->getComponentParameter()->dimensions[backgroundObjects[i]->getHealth()].x <= 0 ||
			backgroundObjects[i]->getPosition().x >= screanWidth)
		{
			backgroundObjects[i]->needDraw = false;
		}
	}

	speedometerObjects->setHeath(((personalTank->getSpeed() < 0 ? -7 : 7) * personalTank->getSpeed() - 1) / personalTank->getMaxSpeed());
	speedometerObjects->tiltAngle = (50.f * personalTank->getSpeed()) / float(personalTank->getMaxSpeed());
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
			else if (graphic->getEvent().type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::D))
			{
				botTank->setDrive(true);
			}
			else if (graphic->getEvent().type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::A))
			{
				botTank->setDrive(false);
			}

			if (graphic->getEvent().type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::LControl))
			{
				personalTank->setControlIsPressed(true);
			}

			if (graphic->getEvent().type == Event::KeyPressed && (Keyboard::isKeyPressed(Keyboard::Num0) || Keyboard::isKeyPressed(Keyboard::Num1) ||
				Keyboard::isKeyPressed(Keyboard::Num2) || Keyboard::isKeyPressed(Keyboard::Num3) || Keyboard::isKeyPressed(Keyboard::Num4) ||
				Keyboard::isKeyPressed(Keyboard::Num5) || Keyboard::isKeyPressed(Keyboard::Num6) || Keyboard::isKeyPressed(Keyboard::Num7) ||
				Keyboard::isKeyPressed(Keyboard::Num8) || Keyboard::isKeyPressed(Keyboard::Num9)))
			{
				personalTank->setNumberIsPressed(graphic->getEvent().text.unicode);
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
		personalTank->work(mousePosition * (graphic->hasFocus() ? 1 : -100), Mouse::isButtonPressed(Mouse::Left) && graphic->hasFocus(), timer, timeForWork, lengthBetweenTanks - botTank->getBorder().x, botTank->getOffsetForTank().x, components, bulletPositionInComponents, bullets, Mouse::isButtonPressed(Mouse::Right) && graphic->hasFocus());

		//Work with bot tank
		botTank->work(timer, timeForWork, lengthBetweenTanks + 2 * personalTank->getBorder().y - 2 * leftTank.getDimension(), mousePosition - personalTank->getGlobalOffset(), components, bulletPositionInComponents, bullets);

		if (personalTank->getNeedUpdateLengthBetweenTanks() || botTank->getNeedUpdateLengthBetweenTanks())
		{
			lengthBetweenTanks = getLengthBetweenTanks(leftTank, rightTank) * 20;
		}

		if (firstUpdateOfBackgrounds || personalTank->getSpeed() != 0 || botTank->getSpeed() != 0)
		{
			firstUpdateOfBackgrounds = false;

			updateObjects();
			leftTank.setOffset(personalTank->getOffsetForTank());

			//botTank->setGlobalOffset(personalTank->getGlobalOffset());

			rightTank.setOffset(botTank->getOffsetForTank() + personalTank->getGlobalOffset());
		}
		if (!firstUpdateOfBackgrounds && personalTank->getSpeed() != 0)
		{
			firstUpdateOfBackgrounds = true;
		}

		if (personalTank->getHighlightingUpdated(true))
		{
			while (allotmentObjects.size() > 0)
			{
				delete allotmentObjects.back();
				allotmentObjects.pop_back();
			}
			allotmentObjects = personalTank->getHighlightedGuns(components, allotmentPositionInComponents);
		}

		//Work with bullet
		if (personalTank->getNeedAddBullet())
		{
			vector<ViewableObject *> tempObjects = personalTank->getBullets();
			bullets.insert(bullets.end(), tempObjects.begin(), tempObjects.end());
		}
		if (botTank->getNeedAddBullet())
		{
			vector<ViewableObject *> tempObjects = botTank->getBullets();
			bullets.insert(bullets.end(), tempObjects.begin(), tempObjects.end());
		}

		workWithBullet(components, bulletPositionInComponents, bullets, personalTank->getGlobalOffset(), screanWidth, timer, timeForWork, screanHeight - 70);

		graphic->draw(button, backgroundAndSpeedometerObjects, personalTank->getSpeed() != 0, bullets, leftTank, rightTank, personalTank->needHighlighte(), max(max(personalTank->getNeedUpdateTank(), botTank->getNeedUpdateTank()), personalTank->getHighlightingUpdated(true)), allotmentObjects, personalTank->getHighlightingUpdated(), timer);
	}
}