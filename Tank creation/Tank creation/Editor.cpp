#include "Editor.h"


Editor::Editor(string &fileName) : WorkWithWindow(fileName)
{
	fileIn.close();
}

Editor::Editor(string &fileName, Graphic *forCopyWindow) : WorkWithWindow(fileName, forCopyWindow)
{
	fileIn >> backgroundXCoordinate >> backgroundYCoordinate >> backgroundWidth >> backgroundHeight;

	getline(fileIn, backgroundNameOfPicture);
	getline(fileIn, backgroundNameOfPicture);
	graphic->setInformation(backgroundXCoordinate, backgroundYCoordinate, backgroundWidth, backgroundHeight, backgroundNameOfPicture);

	components = dataForResources();
	graphic->setInformation(components);

	fileIn.close();

	graphic->setInformation(tank);
	tank.setOffset(backgroundXCoordinate - backgroundWidth / 2 + 1, backgroundYCoordinate - backgroundHeight / 2 + 1);

	tankEditor = new TankEditor(tank.getObjects());
	tankEditor->setOffset(backgroundXCoordinate - backgroundWidth / 2 + 1, backgroundYCoordinate - backgroundHeight / 2 + 1);

	oldObject = nullptr;


	vector<Object *> temp;

	for (int i = 5; i < 50; ++i)
	{
		Object *newObject = TankEditor::getObject(components[i], i);
		newObject->setHeath(components[i]->getStruct()->healthPoints);
		temp.push_back(newObject);
	}

	list = new List(temp, 300, 290, 50, 50);

	graphic->setInformation(*list);
}


Editor::~Editor()
{
	tank.~Tank();

	while (components.size() > 0)
	{
		delete components.back();
		components.pop_back();
	}

	while (objects.size() > 0)
	{
		delete objects.back();
		objects.pop_back();
	}

	delete tankEditor;
}


void Editor::work()
{
	if (graphic->getTimeAsMilliseconds() / coefficientForTime - timer >= timeForWork)
	{
		timer += timeForWork;

		if (needWindowResult)
		{
			if (windowResult == "Exit.")
			{
				windowIsOpen = false;
				return;
			}
			needWindowResult = false;
		}


		mousePosition = graphic->getPositionOfMouse();

		while (graphic->pollEvent())
		{
			if (graphic->getEvent().type == Event::Closed || (graphic->getEvent().type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Escape)))
			{
				needNewWindow = true;
				needWindowResult = true;

				string fileName = "Data/Data for exit from editor.dat";

				graphic->drawInRenderTexture(button);

				newWindow = new ExitFromEditor(fileName, graphic);
			}
			if ((graphic->getEvent().type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Up)) || (graphic->getEvent().type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::W)) || (graphic->getEvent().type == Event::MouseWheelMoved && graphic->getEvent().mouseWheel.delta > 0))
			{
				list->setDirect(true);
			}
			if ((graphic->getEvent().type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Down)) || (graphic->getEvent().type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::S)) || (graphic->getEvent().type == Event::MouseWheelMoved && graphic->getEvent().mouseWheel.delta < 0))
			{
				list->setDirect(false);
			}
		}

		//Work with buttons
		for (int i = 0; i < numberOfButton; ++i)
		{
			button[i].work(mousePosition * (graphic->hasFocus() ? 1 : -100), Mouse::isButtonPressed(Mouse::Left) && graphic->hasFocus(), timer, timeForWork);
		}

		for (int i = 0; i < numberOfButton; ++i)
		{
			if (button[i].getActivateAnAction())
			{
				if (button[i].getStruct()->buttonName == "Back")
				{
					needNewWindow = true;
					needWindowResult = true;

					string fileName = "Data/Data for exit from editor.dat";

					graphic->drawInRenderTexture(button, tank, timer);

					newWindow = new ExitFromEditor(fileName, graphic);

					button[i].setActivateAnAction(false);
				}
				else
				{
					needNewWindow = true;

					string fileName = "Data/Data for not available.dat";

					graphic->drawInRenderTexture(button, tank, timer);

					newWindow = new NotAvailable(fileName, graphic);

					button[i].setActivateAnAction(false);
				}
			}

		}

		//Work with tank
		if (Mouse::isButtonPressed(Mouse::Left) && graphic->hasFocus())
		{
			if (oldObject == nullptr || oldObject != tank.getObject(mousePosition))
			{
				tankEditor->addObject(components[37], 37, mousePosition);
				oldObject = tank.getObject(mousePosition);
			}
		}
		else if (Mouse::isButtonPressed(Mouse::Right) && graphic->hasFocus())
		{
			tankEditor->removeObject(mousePosition);
		}
		else
		{
			oldObject = nullptr;
		}
		
		if (graphic->hasFocus())
		{
			if (objects.size() == 0)
			{
				Object *temp = tankEditor->getFreePlace(components[37], 37, mousePosition);

				objects.push_back(temp);
			}
			else
			{
				delete objects.back();

				objects.back() = tankEditor->getFreePlace(components[37], 37, mousePosition);
			}

		}

		//Work with list
		list->work(mousePosition * (graphic->hasFocus() ? 1 : -100), Mouse::isButtonPressed(Mouse::Left) && graphic->hasFocus(), timer, timeForWork);


		graphic->draw(button, objects, tank, *list, timer);
	}
}