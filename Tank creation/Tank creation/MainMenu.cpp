#include "MainMenu.h"


MainMenu::MainMenu(string &fileName) : WorkWithWindow(fileName)
{
	string objectName, typeName, identifierName;
	
	int numberOfType, numberInType, numberOfVariant;


	getline(fileIn, objectName);

	fileIn >> numberOfType;
	for (int i = 0; i < numberOfType; ++i)
	{
		fileIn >> numberInType;

		getline(fileIn, typeName);
		getline(fileIn, typeName);

		for (int j = 0; j < numberInType; ++j)
		{
			fileIn >> numberOfVariant;

			getline(fileIn, identifierName);
			getline(fileIn, identifierName);

			Component *newComponent;

			if (typeName == "/background")
			{
				newComponent = new BackgroundComponent(objectName, typeName + to_string(j + 1), identifierName, numberOfVariant);
			}

			components.push_back(newComponent);
		}
	}


	getline(fileIn, objectName);

	fileIn >> numberOfType;
	for (int i = 0; i < numberOfType; ++i)
	{
		fileIn >> numberInType;

		getline(fileIn, typeName);
		getline(fileIn, typeName);

		for (int j = 0; j < numberInType; ++j)
		{
			fileIn >> numberOfVariant;

			getline(fileIn, identifierName);
			getline(fileIn, identifierName);

			int health;
			bool canRebound;
			fileIn >> canRebound >> health;

			Component *newComponent;

			if (typeName == "/block")
			{
				newComponent = new SmallBlockComponent(objectName, typeName + to_string(j + 1), identifierName, numberOfVariant, health, canRebound);
			}

			components.push_back(newComponent);
		}
	}


	getline(fileIn, objectName);
	getline(fileIn, objectName);

	fileIn >> numberOfType;
	for (int i = 0; i < numberOfType; ++i)
	{
		fileIn >> numberInType;

		getline(fileIn, typeName);
		getline(fileIn, typeName);

		for (int j = 0; j < numberInType; ++j)
		{
			fileIn >> numberOfVariant;

			getline(fileIn, identifierName);
			getline(fileIn, identifierName);

			int health;
			bool canRebound;
			fileIn >> canRebound >> health;

			Component *newComponent;

			if (typeName == "/block")
			{
				newComponent = new BigBlockComponent(objectName, typeName + to_string(j + 1), identifierName, numberOfVariant, health, canRebound);
			}

			components.push_back(newComponent);
		}
	}

	graphic->setInformation(components);
	fileIn.close();


	for (int i = 0; i < 5; ++i)
	{
		Object *newObject = new Background(components[i], i);
		newObject->setPosition((1 + i) * 100, 10);
		objects.push_back(newObject);
	}

	for (int i = 5; i < 18; ++i)
	{
		Object *newObject = new SmallBlock(components[i], i);
		newObject->setPosition((1 + i) * 50, 100);
		newObject->setHeath(1);
		objects.push_back(newObject);
	}
	for (int i = 5; i < 18; ++i)
	{
		Object *newObject = new SmallBlock(components[i], i);
		newObject->setPosition((1 + i) * 50, 130);
		newObject->setHeath((components[i]->getStruct()->healthPoints) / 2);
		objects.push_back(newObject);
	}
	for (int i = 5; i < 18; ++i)
	{
		Object *newObject = new SmallBlock(components[i], i);
		newObject->setPosition((1 + i) * 50, 160);
		newObject->setHeath((components[i]->getStruct()->healthPoints * 3) / 4);
		objects.push_back(newObject);
	}
	for (int i = 5; i < 18; ++i)
	{
		Object *newObject = new SmallBlock(components[i], i);
		newObject->setPosition((1 + i) * 50, 190);
		newObject->setHeath(components[i]->getStruct()->healthPoints);
		objects.push_back(newObject);
	}

	for (int i = 18; i < 35; ++i)
	{
		Object *newObject = new BigBlock(components[i], i);
		newObject->setPosition((-17 + i) * 50, 230);
		newObject->setHeath(1);
		objects.push_back(newObject);
	}
	for (int i = 18; i < 35; ++i)
	{
		Object *newObject = new BigBlock(components[i], i);
		newObject->setPosition((-17 + i) * 50, 280);
		newObject->setHeath((components[i]->getStruct()->healthPoints) / 2);
		objects.push_back(newObject);
	}
	for (int i = 18; i < 35; ++i)
	{
		Object *newObject = new BigBlock(components[i], i);
		newObject->setPosition((-17 + i) * 50, 330);
		newObject->setHeath((components[i]->getStruct()->healthPoints * 3) / 4);
		objects.push_back(newObject);
	}
	for (int i = 18; i < 35; ++i)
	{
		Object *newObject = new BigBlock(components[i], i);
		newObject->setPosition((-17 + i) * 50, 380);
		newObject->setHeath(components[i]->getStruct()->healthPoints);
		objects.push_back(newObject);
	}
}

void MainMenu::work()
{
	if (graphic->getTimeAsMilliseconds() / coefficientForTime - timer >= timeForWork)
	{
		timer += timeForWork;

		mousePosition = graphic->getPositionOfMouse();

		while (graphic->pollEvent())
		{
			if (graphic->getEvent().type == Event::Closed || (graphic->getEvent().type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Escape)))
			{
				graphic->close();
				windowIsOpen = false;
				return;
			}
		}


		for (int i = 0; i < numberOfButton; ++i)
		{
			button[i].work(mousePosition, Mouse::isButtonPressed(Mouse::Left), timer, timeForWork);
		}

		for (int i = 0; i < numberOfButton; ++i)
		{
			if (button[i].getActivateAnAction())
			{
				if (button[i].getStruct()->buttonName == "Exit")
				{
					graphic->close();
					windowIsOpen = false;
					return;
				}
				else if (button[i].getStruct()->buttonName == "Create a new tank")
				{
					needNewWindow = true;

					string fileName = "Data/Data for editor.dat";

					newWindow = new Editor(fileName, graphic);

					button[i].setActivateAnAction(false);
				}
				else
				{
					needNewWindow = true;

					string fileName = "Data/Data for not available.dat";

					graphic->drawInRenderTexture(button);

					newWindow = new NotAvailable(fileName, graphic);

					button[i].setActivateAnAction(false);
				}
			}

		}

		graphic->draw(button, timer, objects);
	}
}