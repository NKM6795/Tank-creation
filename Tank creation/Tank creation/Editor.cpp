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

	tank.getObjects()[0][0] = TankEditor::getObject(components[5], 5);
	tank.getObjects()[0][0]->setHeath(1);

	tank.getObjects()[5][5] = TankEditor::getObject(components[5], 5);
	tank.getObjects()[5][5]->setHeath(1);
	tank.getObjects()[5][5]->setPosition(100, 100);

	tank.getObjects()[6][5] = TankEditor::getObject(components[5], 5);
	tank.getObjects()[6][5]->setHeath(1);
	tank.getObjects()[6][5]->setPosition(120, 100);

	tank.getObjects()[7][5] = TankEditor::getObject(components[5], 5);
	tank.getObjects()[7][5]->setHeath(1);
	tank.getObjects()[7][5]->setPosition(140, 100);

	tank.getObjects()[5][6] = TankEditor::getObject(components[5], 5);
	tank.getObjects()[5][6]->setHeath(1);
	tank.getObjects()[5][6]->setPosition(100, 120);

	tank.getObjects()[6][6] = TankEditor::getObject(components[5], 5);
	tank.getObjects()[6][6]->setHeath(1);
	tank.getObjects()[6][6]->setPosition(120, 120);

	Object *newObject = tankEditor->getFreePlace(components[5], 5, Vector2int(350, 70));

	objects.push_back(newObject);
}


Editor::~Editor()
{
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
			if (graphic->getEvent().type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::F))
			{
				delete objects.back();

				objects.back() = tankEditor->getFreePlace(components[5], 5, mousePosition);
			}
		}


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

		graphic->draw(button, objects, tank, timer);
	}
}