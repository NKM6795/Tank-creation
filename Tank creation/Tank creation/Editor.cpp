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

	fileIn.close();

	graphic->setInformation(tank);
	tank.setOffset(backgroundXCoordinate - backgroundWidth / 2 + 1, backgroundYCoordinate - backgroundHeight / 2 + 1);

	tankEditor = new TankEditor(tank.getViewableObjects());
	tankEditor->setOffset(backgroundXCoordinate - backgroundWidth / 2 + 1, backgroundYCoordinate - backgroundHeight / 2 + 1);

	if (tankName != "")
	{
		tankEditor->download(tankName, components);
	}

	oldViewableObject = { Vector2int(-1, -1), Vector2int(-1, -1) };

	vector<ViewableObject *> temp;

	for (int i = 5; i < 50; ++i)
	{
		ViewableObject *newViewableObject = TankEditor::getViewableObject(components[i], i);
		newViewableObject->setHeath(components[i]->getStruct()->healthPoints);
		temp.push_back(newViewableObject);
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

	delete list;
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
			else if (windowResult != "Cancel.")
			{
				tankEditor->save(windowResult);

				graphic->saveTank(windowResult, tank, timer);
			}
			needWindowResult = false;
		}


		mousePosition = graphic->getPositionOfMouse();

		while (graphic->pollEvent())
		{
			if (graphic->getEvent().type == Event::Closed || (graphic->getEvent().type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Escape) && !list->isOpen()))
			{
				needNewWindow = true;
				needWindowResult = true;

				string fileName = "Data/Data for exit from editor.dat";

				graphic->drawInRenderTexture(button, objects, tank, *list, timer);

				newWindow = new ExitFromEditor(fileName, graphic, tankEditor->completenessСheck());
			}
			else if (list->isOpen() && ((graphic->getEvent().type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Up)) || (graphic->getEvent().type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::W)) || (graphic->getEvent().type == Event::MouseWheelMoved && graphic->getEvent().mouseWheel.delta > 0)))
			{
				list->setDirect(true);
			}
			else if (list->isOpen() && ((graphic->getEvent().type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Down)) || (graphic->getEvent().type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::S)) || (graphic->getEvent().type == Event::MouseWheelMoved && graphic->getEvent().mouseWheel.delta < 0)))
			{
				list->setDirect(false);
			}
			else if (mousePosition >= Vector2int() && mousePosition <= Vector2int(screanWidth, screanHeight) && !list->isOpen() && (Mouse::isButtonPressed(Mouse::XButton2) || graphic->getEvent().type == Event::MouseWheelMoved || (graphic->getEvent().type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Q))))
			{
				list->openList(mousePosition);
			}
			else if (Mouse::isButtonPressed(Mouse::XButton1) || Mouse::isButtonPressed(Mouse::XButton2) || (graphic->getEvent().type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Q)) || (graphic->getEvent().type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Escape)))
			{
				list->closeList();
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
					needNewWindow = true;
					needWindowResult = true;

					string fileName = "Data/Data for exit from editor.dat";

					graphic->drawInRenderTexture(button, objects, tank, *list, timer);

					newWindow = new ExitFromEditor(fileName, graphic, tankEditor->completenessСheck());

					button[i].setActivateAnAction(false);
				}
				else if (button[i].getStruct()->buttonName == "Clear")
				{
					tankEditor->clear();

					button[i].setActivateAnAction(false);
				}
				else if (button[i].getStruct()->buttonName == "Save")
				{
					needNewWindow = true;

					if (tankEditor->completenessСheck())
					{
						needWindowResult = true;

						string fileName = "Data/Data for save tank.dat";

						graphic->drawInRenderTexture(button, objects, tank, *list, timer);

						newWindow = new SaveTank(fileName, graphic);

						button[i].setActivateAnAction(false);
					}
					else
					{
						string fileName = "Data/Data for not available.dat";

						graphic->drawInRenderTexture(button, objects, tank, *list, timer);

						newWindow = new NotAvailable(fileName, graphic);
						
						button[i].setActivateAnAction(false);
					}
				}
			}

		}

		//Work with tank
		if (Mouse::isButtonPressed(Mouse::Left) && graphic->hasFocus() && !list->inFocuse(mousePosition) && list->canAddElement(Mouse::isButtonPressed(Mouse::Left)))
		{
			list->closeList();

			if (oldViewableObject == pair<Vector2int, Vector2int>{ Vector2int(-1, -1), Vector2int(-1, -1) } ||
				(mousePosition.x - tankEditor->getOffset().x < oldViewableObject.first.x - oldViewableObject.second.x ||
					mousePosition.y - tankEditor->getOffset().y < oldViewableObject.first.y - oldViewableObject.second.y ||
					mousePosition.x - tankEditor->getOffset().x > oldViewableObject.first.x + oldViewableObject.second.x ||
					mousePosition.y - tankEditor->getOffset().y > oldViewableObject.first.y + oldViewableObject.second.y))
			{
				tankEditor->addViewableObject(components[list->getViewableObjects()[list->getIndex()]->getIndex()], list->getViewableObjects()[list->getIndex()]->getIndex(), mousePosition);
				oldViewableObject = objects.back() == nullptr ?
					pair<Vector2int, Vector2int>{ Vector2int(-1, -1), Vector2int(-1, -1) } :
					pair<Vector2int, Vector2int>{ mousePosition - tankEditor->getOffset(), Vector2int(objects.back()->getComponentParameter()->width, objects.back()->getComponentParameter()->height) * 20 };
			}
		}
		else if (Mouse::isButtonPressed(Mouse::Right) && graphic->hasFocus() && !list->inFocuse(mousePosition))
		{
			list->closeList();

			tankEditor->removeViewableObject(mousePosition);
		}
		else if (Mouse::isButtonPressed(Mouse::Middle) && graphic->hasFocus() && !list->inFocuse(mousePosition))
		{
			list->closeList();

			list->copyViewableObject(tankEditor->getViewableObject(mousePosition));
		}
		else
		{
			oldViewableObject = { Vector2int(-1, -1), Vector2int(-1, -1) };
		}
		
		//Work with selecting object
		if (graphic->hasFocus())
		{
			if (objects.size() == 0)
			{
				ViewableObject *temp = tankEditor->getFreePlace(components[list->getViewableObjects()[list->getIndex()]->getIndex()], list->getViewableObjects()[list->getIndex()]->getIndex(), mousePosition);

				objects.push_back(temp);
			}
			else
			{
				delete objects.back();

				objects.back() = tankEditor->getFreePlace(components[list->getViewableObjects()[list->getIndex()]->getIndex()], list->getViewableObjects()[list->getIndex()]->getIndex(), mousePosition);
			}

		}

		//Work with list
		list->work(mousePosition * (graphic->hasFocus() ? 1 : -100), Mouse::isButtonPressed(Mouse::Left) && graphic->hasFocus(), timer, timeForWork, Mouse::isButtonPressed(Mouse::Right) && graphic->hasFocus());


		graphic->draw(button, objects, tank, *list, timer);
	}
}