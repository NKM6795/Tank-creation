#include "TankSelection.h"


TankSelection::TankSelection(string &fileName) : WorkWithWindow(fileName)
{
	fileIn.close();
}

TankSelection::TankSelection(string &fileName, Graphic *forCopyWindow) : WorkWithWindow(fileName, forCopyWindow)
{
	string objectName, typeName, identifierName;

	int numberOfVariant;

	getline(fileIn, objectName);
	if (objectName == "")
	{
		getline(fileIn, objectName);
	}

	getline(fileIn, typeName);
	getline(fileIn, identifierName);
	fileIn >> numberOfVariant;

	fileIn.close();


	fileIn.open("Data/Tanks/Number.dat");

	int number;
	fileIn >> number;

	vector<string> names(number, "");

	getline(fileIn, names[0]);
	for (int i = 0; i < number; ++i)
	{
		getline(fileIn, names[i]);

		Component *newComponent = new TankPictureComponent(names[i], objectName, typeName, identifierName, numberOfVariant);
		newComponent->getStruct()->healthPoints = 1;
		newComponent->getStruct()->width = 30;
		newComponent->getStruct()->height = 30;

		components.push_back(newComponent);

		Object *newObject = new TankPicture(newComponent, i);
		objects.push_back(newObject);
	}
	fileIn.close();

	graphic->setInformation(components);

	list = new List(objects, screanWidth - 6, screanHeight - 90, 3, 87, 100, 100, 120);

	list->openList(Vector2int(3, 87));

	graphic->setInformation(*list);

	fileIn.close();
}


TankSelection::~TankSelection()
{
	while (objects.size() > 0)
	{
		delete objects.back();
		objects.pop_back();
	}

	delete list;
}


void TankSelection::work()
{
	if (graphic->getTimeAsMilliseconds() / coefficientForTime - timer >= timeForWork)
	{
		timer += timeForWork;

		mousePosition = graphic->getPositionOfMouse();

		while (graphic->pollEvent())
		{
			if (graphic->getEvent().type == Event::Closed || (graphic->getEvent().type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Escape)))
			{
				windowResult = "Cancel.";

				windowIsOpen = false;
				return;
			}
			else if (list->isOpen() && ((graphic->getEvent().type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Up)) || (graphic->getEvent().type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::W)) || (graphic->getEvent().type == Event::MouseWheelMoved && graphic->getEvent().mouseWheel.delta > 0)))
			{
				list->setDirect(true);
			}
			else if (list->isOpen() && ((graphic->getEvent().type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Down)) || (graphic->getEvent().type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::S)) || (graphic->getEvent().type == Event::MouseWheelMoved && graphic->getEvent().mouseWheel.delta < 0)))
			{
				list->setDirect(false);
			}
		}

		//Work with buttons
		for (int i = 0; i < numberOfButton; ++i)
		{
			button[i].work(mousePosition * ((graphic->hasFocus() && !list->inFocuse(mousePosition) && list->canAddElement(Mouse::isButtonPressed(Mouse::Left))) ? 1 : -100), Mouse::isButtonPressed(Mouse::Left) && (graphic->hasFocus() && !list->inFocuse(mousePosition) && list->canAddElement(Mouse::isButtonPressed(Mouse::Left))), timer, timeForWork);
		}
		for (int i = 0; i < numberOfButton; ++i)
		{
			if (button[i].getActivateAnAction())
			{
				if (button[i].getStruct()->buttonName == "Back")
				{
					windowResult = "Cancel.";

					windowIsOpen = false;
					return;
				}
			}
		}

		//Work with list
		list->work(mousePosition * (graphic->hasFocus() ? 1 : -100), Mouse::isButtonPressed(Mouse::Left) && graphic->hasFocus(), timer, timeForWork);

		if (!list->isOpen())
		{
			windowResult = components[list->getObjects()[list->getIndex()]->getIndex()]->getStruct()->name;

			windowIsOpen = false;
			return;
		}

		graphic->draw(button, *list, timer);
	}
}