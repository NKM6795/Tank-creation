#include "MainMenu.h"


MainMenu::MainMenu(string &fileName) : WorkWithWindow(fileName)
{
	string objectName, typeName, identifierName;
	
	int numberOfType, numberInType, numberOfVariant, numberInVariant;

	getline(fileIn, objectName);

	fileIn >> numberOfType;
	for (int i = 0; i < numberOfType; ++i)
	{
		fileIn >> numberInType;
		for (int j = 0; j < numberInType; ++j)
		{
			getline(fileIn, typeName);
			getline(fileIn, typeName);

			fileIn >> numberOfVariant;
			for (int l = 0; l < numberOfVariant; ++l)
			{
				fileIn >> numberInVariant;

				getline(fileIn, identifierName);
				getline(fileIn, identifierName);

				Component *newComponent;

				if (typeName == "/background")
				{
					newComponent = new BackgroundComponent(objectName, typeName + to_string(j + 1), identifierName, numberInVariant);
				}

				components.push_back(newComponent);
			}
		}
	}

	graphic->setInformation(components);

	fileIn.close();

	Object *object = new Background(components[0], 0);

	object->setPosition(500, 500);

	objects.push_back(object);
}

void MainMenu::work()
{
	if (graphic->getTimeAsMilliseconds() - timer >= timeForWork)
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