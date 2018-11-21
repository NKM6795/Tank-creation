#include "Editor.h"


Editor::Editor(string &fileName) : WorkWithWindow(fileName)
{
	fileIn.close();
}

Editor::Editor(string &fileName, Graphic *forCopyWindow, string tankName) : WorkWithWindow(fileName, forCopyWindow)
{
	fileIn >> backgroundXCoordinate >> backgroundYCoordinate >> backgroundWidth >> backgroundHeight;

	getline(fileIn, backgroundNameOfPicture);
	getline(fileIn, backgroundNameOfPicture);
	graphic->setInformation(backgroundXCoordinate, backgroundYCoordinate, backgroundWidth, backgroundHeight, backgroundNameOfPicture);

	components = dataForResources();
	graphic->setInformation(components);

	fileIn >> listWidth >> listHeight >> listPosition.x >> listPosition.y;

	fileIn.close();

	graphic->setInformation(tank);
	tank.setOffset(backgroundXCoordinate - backgroundWidth / 2 + 1, backgroundYCoordinate - backgroundHeight / 2 + 1);
	tankIsChanged = false;

	tankEditor = new TankEditor(tank.getViewableObjects());
	tankEditor->setOffset(backgroundXCoordinate - backgroundWidth / 2 + 1, backgroundYCoordinate - backgroundHeight / 2 + 1);

	if (tankName != "")
	{
		tank.name = tankName;
		text[1] = tank.name;
		tankEditor->download(tank.name, components);
	}

	oldViewableObject = pair<Vector2int, Vector2int>(Vector2int(-1, -1), Vector2int(-1, -1));

	vector<ViewableObject *> temp;

	for (int i = 5; i < 50; ++i)
	{
		ViewableObject *newViewableObject = TankEditor::getViewableObject(components[i], i);
		newViewableObject->setHeath(components[i]->getStruct()->healthPoints);
		temp.push_back(newViewableObject);
	}

	list = new List(temp, listWidth, listHeight, listPosition.x, listPosition.y);
	list->openList(listPosition);

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

	delete list;
}


void Editor::work()
{
	if (graphic->getTimeAsMilliseconds() / coefficientForTime - timer >= timeForWork)
	{
		timer += timeForWork;

		if (needWindowResult)
		{
			if (windowResult == "Exit/")
			{
				windowIsOpen = false;
				return;
			}
			else if (windowResult.size() > 18 && windowResult.substr(0, 18) == "Exit/Saved/Rename/")
			{
				tank.name = windowResult.substr(18);
				text[1] = tank.name;

				tankEditor->save(tank.name);

				graphic->saveTank(tank.name, tank, timer);

				windowIsOpen = false;
				return;
			}
			else if (windowResult == "Exit/Saved/")
			{
				tankEditor->save(tank.name);

				graphic->saveTank(tank.name, tank, timer);

				windowIsOpen = false;
				return;
			}
			else if (windowResult.size() > 7 && windowResult.substr(0, 7) == "Rename/")
			{
				tankIsChanged = true;

				tank.name = windowResult.substr(7);
				text[1] = tank.name;
			}
			else if (windowResult.size() > 13 && windowResult.substr(0, 13) == "Saved/Rename/")
			{
				tank.name = windowResult.substr(13);
				text[1] = tank.name;
				tankIsChanged = false;

				tankEditor->save(tank.name);

				graphic->saveTank(tank.name, tank, timer);
			}
			else if (windowResult == "Saved/")
			{
				tankIsChanged = false;

				tankEditor->save(tank.name);

				graphic->saveTank(tank.name, tank, timer);
			}
			needWindowResult = false;
		}

		mousePosition = graphic->getPositionOfMouse();

		while (graphic->pollEvent())
		{
			if (graphic->getEvent().type == Event::Closed || (graphic->getEvent().type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Escape)))
			{
				button["Back"].setActivateAnAction(true);
			}
			else if (graphic->getEvent().type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::S) && Keyboard::isKeyPressed(Keyboard::LControl))
			{
				needNewWindow = true;

				button["Save"].setActivateAnAction(true);
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
			if (!tankIsChanged || tankEditor->isEmpty())
			{
				windowIsOpen = false;
				return;
			}
			else
			{
				needNewWindow = true;
				needWindowResult = true;

				string fileName = "Data/Data for exit from editor.dat";

				graphic->drawInRenderTexture(text, button, objects, tank, *list, timer);

				newWindow = new ExitFromEditor(fileName, graphic, tank.name, tankEditor);

				button["Back"].setActivateAnAction(false);
			}

		}
		else if (button["Clear"].getActivateAnAction())
		{
			tankEditor->clear();

			button["Clear"].setActivateAnAction(false);
		}
		else if (button["Save"].getActivateAnAction())
		{
			needNewWindow = true;

			if (tankEditor->completenessСheck() == 1 && tank.name == "")
			{
				needWindowResult = true;

				string fileName = "Data/Data for save tank.dat";

				graphic->drawInRenderTexture(text, button, objects, tank, *list, timer);

				newWindow = new SaveTank(fileName, graphic);
			}
			else if (tankEditor->completenessСheck() == 1)
			{
				needNewWindow = true;
				needWindowResult = true;

				string fileName = "Data/Data for saved.dat";

				graphic->drawInRenderTexture(text, button, objects, tank, *list, timer);

				newWindow = new Saved(fileName, graphic);
			}
			else if (tankEditor->completenessСheck() == -1)
			{
				string fileName = "Data/Data for not available.dat";

				graphic->drawInRenderTexture(text, button, objects, tank, *list, timer);

				newWindow = new NotAvailable(fileName, graphic, "Missing main unit");
			}
			else if (tankEditor->completenessСheck() == -2)
			{
				string fileName = "Data/Data for not available.dat";

				graphic->drawInRenderTexture(text, button, objects, tank, *list, timer);

				newWindow = new NotAvailable(fileName, graphic, "No tracks");
			}
			else
			{
				string fileName = "Data/Data for not available.dat";

				graphic->drawInRenderTexture(text, button, objects, tank, *list, timer);

				newWindow = new NotAvailable(fileName, graphic, "Tank is not correct");
			}

			button["Save"].setActivateAnAction(false);
		}
		else if (button["Change name"].getActivateAnAction())
		{
			needNewWindow = true;
			needWindowResult = true;

			string fileName = "Data/Data for rename tank.dat";

			graphic->drawInRenderTexture(text, button, objects, tank, *list, timer);

			newWindow = new RenameTank(fileName, graphic, tank.name);

			button["Change name"].setActivateAnAction(false);
		}

		//Work with tank
		if (Mouse::isButtonPressed(Mouse::Left) && graphic->hasFocus() && !list->inFocuse(mousePosition) && list->canAddElement(Mouse::isButtonPressed(Mouse::Left)))
		{
			if (oldViewableObject == pair<Vector2int, Vector2int>(Vector2int(-1, -1), Vector2int(-1, -1)) ||
				(mousePosition.x - tankEditor->getOffset().x < oldViewableObject.first.x - oldViewableObject.second.x ||
					mousePosition.y - tankEditor->getOffset().y < oldViewableObject.first.y - oldViewableObject.second.y ||
					mousePosition.x - tankEditor->getOffset().x > oldViewableObject.first.x + oldViewableObject.second.x ||
					mousePosition.y - tankEditor->getOffset().y > oldViewableObject.first.y + oldViewableObject.second.y))
			{
				tankIsChanged = tankEditor->addViewableObject(components[list->getViewableMainObjects()[list->getMainIndexOfSelectedObject()]->getIndex()], list->getViewableMainObjects()[list->getMainIndexOfSelectedObject()]->getIndex(), mousePosition) || tankIsChanged;
				oldViewableObject = objects.back() == nullptr ?
					pair<Vector2int, Vector2int>(Vector2int(-1, -1), Vector2int(-1, -1)) :
					pair<Vector2int, Vector2int>(mousePosition - tankEditor->getOffset(), Vector2int(objects.back()->getComponentParameter()->width, objects.back()->getComponentParameter()->height) * 20);
			}
		}
		else if (Mouse::isButtonPressed(Mouse::Right) && graphic->hasFocus() && !list->inFocuse(mousePosition))
		{
			tankIsChanged = tankEditor->removeViewableObject(mousePosition) || tankIsChanged;
		}
		else if (Mouse::isButtonPressed(Mouse::Middle) && graphic->hasFocus() && !list->inFocuse(mousePosition))
		{
			list->copyViewableObject(tankEditor->getViewableObject(mousePosition));
		}
		else
		{
			oldViewableObject = pair<Vector2int, Vector2int>(Vector2int(-1, -1), Vector2int(-1, -1));
		}
		
		//Work with selecting object
		while (objects.size() > 0)
		{
			delete objects.back();
			objects.pop_back();
		}
		if (!tankEditor->completenessСheck())
		{
			objects = tankEditor->getWrongObjects();
		}
		if (graphic->hasFocus())
		{
			objects.push_back(tankEditor->getFreePlace(components[list->getViewableMainObjects()[list->getMainIndexOfSelectedObject()]->getIndex()], list->getViewableMainObjects()[list->getMainIndexOfSelectedObject()]->getIndex(), mousePosition));
		}

		//Work with list
		list->work(mousePosition * (graphic->hasFocus() ? 1 : -100), Mouse::isButtonPressed(Mouse::Left) && graphic->hasFocus(), timer, timeForWork, Mouse::isButtonPressed(Mouse::Right) && graphic->hasFocus());


		graphic->draw(text, button, objects, tank, *list, timer);
	}
}