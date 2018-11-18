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

	if (number > 0)
	{
		getline(fileIn, names[0]);
		for (int i = 0; i < number; ++i)
		{
			getline(fileIn, names[i]);

			Component *newComponent = new TankPictureComponent(names[i], objectName, typeName, identifierName, numberOfVariant);
			newComponent->getStruct()->healthPoints = 1;
			newComponent->getStruct()->width = 30;
			newComponent->getStruct()->height = 30;

			components.push_back(newComponent);

			ViewableObject *newViewableObject = new TankPicture(newComponent, i);
			objects.push_back(newViewableObject);
		}
	}
	fileIn.close();

	graphic->setInformation(components);

	list = new List(objects, screanWidth - 6, screanHeight - 90, 3, 87, 100, 100, 120);
	list->openList(Vector2int(3, 87));
	list->setNeedClose();

	graphic->setInformation(*list);

	fileIn.close();
}


TankSelection::~TankSelection()
{
	delete list;

	while (components.size() > 0)
	{
		delete components.back();
		components.pop_back();
	}
}


void TankSelection::deleteSelectedElement()
{
	if (remove(("Data/Tanks/" + components[list->getViewableObjects()[list->getIndexOfSelectedObject()]->getIndex()]->getStruct()->name + ".tnk").c_str()))
	{

	}
	if (remove(("Data/Tanks/" + components[list->getViewableObjects()[list->getIndexOfSelectedObject()]->getIndex()]->getStruct()->name + ".png").c_str()))
	{

	}

	string fileName = components[list->getViewableObjects()[list->getIndexOfSelectedObject()]->getIndex()]->getStruct()->name;

	delete components[list->getViewableObjects()[list->getIndexOfSelectedObject()]->getIndex()];
	components.erase(components.begin() + list->getIndexOfSelectedObject());

	int newIndex = list->getIndexOfSelectedObject() == int(components.size()) ? list->getIndexOfSelectedObject() - 1 : list->getIndexOfSelectedObject();

	delete list;
	objects.clear();

	for (int i = 0; i < int(components.size()); ++i)
	{
		ViewableObject *newViewableObject = new TankPicture(components[i], i);
		objects.push_back(newViewableObject);
	}

	graphic->setInformation(components);

	
	list = new List(objects, screanWidth - 6, screanHeight - 90, 3, 87, 100, 100, 120);
	list->openList(Vector2int(3, 87));
	list->setNeedClose();
	list->copyViewableObject(objects[newIndex]);

	graphic->setInformation(*list);

	ofstream fileOut("Data/Tanks/Number.dat");

	int number = int(components.size());

	fileOut << number << '\n';

	for (int i = 0; i < number; ++i)
	{
		fileOut << components[i]->getStruct()->name << '\n';
	}

	fileOut.close();
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
				windowResult = "Cancel/";

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
			else if ((graphic->getEvent().type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Left)) || (graphic->getEvent().type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Right)) || (graphic->getEvent().type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::A)) || (graphic->getEvent().type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::D)) || Mouse::isButtonPressed(Mouse::XButton2) || Mouse::isButtonPressed(Mouse::XButton1) || (graphic->getEvent().type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Enter)))
			{
				list->select();
			}
			else if (graphic->getEvent().type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Delete))
			{
				deleteSelectedElement();
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
					windowResult = "Cancel/";

					windowIsOpen = false;
					return;
				}
				else if (button[i].getStruct()->buttonName == "Delete")
				{
					deleteSelectedElement();

					button[i].setActivateAnAction(false);
				}
			}
		}

		//Work with list
		list->work(mousePosition * (graphic->hasFocus() ? 1 : -100), Mouse::isButtonPressed(Mouse::Left) && graphic->hasFocus(), timer, timeForWork, Mouse::isButtonPressed(Mouse::Right) && graphic->hasFocus());

		if (!list->isOpen())
		{
			windowResult = components[list->getViewableObjects()[list->getIndexOfSelectedObject()]->getIndex()]->getStruct()->name;

			windowIsOpen = false;
			return;
		}

		graphic->draw(button, *list, timer);
	}
}