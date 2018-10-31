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

	fileIn.close();
}


void Editor::work()
{
	if (graphic->getTimeAsMilliseconds() - timer >= timeForWork)
	{
		timer += timeForWork;

		mousePosition = graphic->getPositionOfMouse();

		while (graphic->pollEvent())
		{
			if (graphic->getEvent().type == Event::Closed || (graphic->getEvent().type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Escape)))
			{
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
				if (button[i].getStruct()->buttonName == "Back")
				{
					windowIsOpen = false;
					return;
				}
				else if (button[i].getStruct()->buttonName == "Save")
				{
					needNewWindow = true;

					string fileName = "Data/Data for exit from editor.dat";

					graphic->drawInRenderTexture(button);

					newWindow = new ExitFromEditor(fileName, graphic);

					button[i].setActivateAnAction(false);
				}
			}

		}

		graphic->draw(button);
	}
}