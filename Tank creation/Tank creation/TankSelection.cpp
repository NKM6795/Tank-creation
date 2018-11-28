#include "TankSelection.h"


TankSelection::TankSelection(string &fileName) : WorkWithWindow(fileName)
{
	fileIn.close();
}

TankSelection::TankSelection(string &fileName, Graphic *forCopyWindow, bool needToLimit) : WorkWithWindow(fileName, forCopyWindow)
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

	fileIn >> listWidth >> listHeight >> listPosition.x >> listPosition.y >> listObjectWidth >> listObjectHeight >> listFragmentHeight;


	fileIn.close();


	fileIn.open("Data/Tanks/Number.dat");

	int number;
	fileIn >> number;

	vector<pair<string, int> > names(number, { "", 0 });

	if (number > 0)
	{
		for (int i = 0; i < number; ++i)
		{
			getline(fileIn, names[i].first);
			getline(fileIn, names[i].first);
			fileIn >> names[i].second;

			if (needToLimit && names[i].second > maxCost)
			{
				continue;
			}

			Component *newComponent = new TankPictureComponent(names[i].first, objectName, typeName, identifierName, numberOfVariant);
			newComponent->getStruct()->healthPoints = 1;
			newComponent->getStruct()->width = 30;
			newComponent->getStruct()->height = 30;
			newComponent->getStruct()->cost = names[i].second;

			components.push_back(newComponent);

			ViewableObject *newViewableObject = new TankPicture(newComponent, int(components.size()) - 1);
			objects.push_back(newViewableObject);
		}
	}
	fileIn.close();

	graphic->setInformation(components);

	list = new List(objects, listWidth, listHeight, listPosition.x, listPosition.y, listObjectWidth, listObjectHeight, listFragmentHeight);
	list->openList(listPosition);
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
	if (list->getViewableMainObjects().size() == 0)
	{
		return;
	}

	if (remove(("Data/Tanks/" + components[list->getViewableMainObjects()[list->getMainIndexOfSelectedObject()]->getIndex()]->getStruct()->name + ".tnk").c_str()))
	{

	}
	if (remove(("Data/Tanks/" + components[list->getViewableMainObjects()[list->getMainIndexOfSelectedObject()]->getIndex()]->getStruct()->name + ".png").c_str()))
	{

	}

	string fileName = components[list->getViewableMainObjects()[list->getMainIndexOfSelectedObject()]->getIndex()]->getStruct()->name;

	delete components[list->getViewableMainObjects()[list->getMainIndexOfSelectedObject()]->getIndex()];
	components.erase(components.begin() + list->getMainIndexOfSelectedObject());

	int newIndex = list->getMainIndexOfSelectedObject() == int(components.size()) ? list->getMainIndexOfSelectedObject() - 1 : list->getMainIndexOfSelectedObject();

	delete list;
	objects.clear();

	for (int i = 0; i < int(components.size()); ++i)
	{
		ViewableObject *newViewableObject = new TankPicture(components[i], i);
		objects.push_back(newViewableObject);
	}

	graphic->setInformation(components);

	
	list = new List(objects, listWidth, listHeight, listPosition.x, listPosition.y, listObjectWidth, listObjectHeight, listFragmentHeight);
	list->openList(listPosition);
	list->setNeedClose();
	list->copyViewableObject(objects[newIndex]);

	graphic->setInformation(*list);

	ofstream fileOut("Data/Tanks/Number.dat");

	int number = int(components.size());

	fileOut << number << '\n';

	for (int i = 0; i < number; ++i)
	{
		fileOut << components[i]->getStruct()->name << '\n' << components[i]->getStruct()->cost << '\n';
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
			else if (list->isOpen() && ((graphic->getEvent().type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Up)) || (graphic->getEvent().type == Event::MouseWheelMoved && graphic->getEvent().mouseWheel.delta > 0)))
			{
				list->setDirect(true);
			}
			else if (list->isOpen() && ((graphic->getEvent().type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Down)) || (graphic->getEvent().type == Event::MouseWheelMoved && graphic->getEvent().mouseWheel.delta < 0)))
			{
				list->setDirect(false);
			}
			else if ((graphic->getEvent().type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Right)) || Mouse::isButtonPressed(Mouse::XButton2) || (graphic->getEvent().type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Enter)))
			{
				list->select();
			}
			else if ((graphic->getEvent().type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Left)) || Mouse::isButtonPressed(Mouse::XButton1))
			{
				list->showInformation();
			}
			else if (graphic->getEvent().type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Delete))
			{
				deleteSelectedElement();
			}

			if (graphic->getEvent().type == Event::TextEntered)
			{
				list->workWithText(graphic->getEvent().text.unicode);
			}
		}

		//Work with buttons
		for (auto i = button.begin(); i != button.end(); ++i)
		{
			i->second.work(mousePosition * ((graphic->hasFocus() && !list->inFocuse(mousePosition) && list->canAddElement(Mouse::isButtonPressed(Mouse::Left))) ? 1 : -100), Mouse::isButtonPressed(Mouse::Left) && (graphic->hasFocus() && !list->inFocuse(mousePosition) && list->canAddElement(Mouse::isButtonPressed(Mouse::Left))), timer, timeForWork);
		}
		if (button["Back"].getActivateAnAction())
		{
			windowResult = "Cancel/";

			windowIsOpen = false;
			return;
		}
		else if (button["Delete"].getActivateAnAction())
		{
			deleteSelectedElement();

			button["Delete"].setActivateAnAction(false);
		}
		else if (button["Choose"].getActivateAnAction())
		{
			list->closeList();

			button["Choose"].setActivateAnAction(false);
		}

		//Work with list
		list->work(mousePosition * (graphic->hasFocus() ? 1 : -100), Mouse::isButtonPressed(Mouse::Left) && graphic->hasFocus(), timer, timeForWork, Mouse::isButtonPressed(Mouse::Right) && graphic->hasFocus());

		if (!list->isOpen())
		{
			if (list->getViewableMainObjects().size() != 0)
			{
				windowResult = components[list->getViewableMainObjects()[list->getMainIndexOfSelectedObject()]->getIndex()]->getStruct()->name;
			}
			else
			{
				windowResult = "Cancel/";
			}

			windowIsOpen = false;
			return;
		}

		graphic->draw(button, *list, timer);
	}
}