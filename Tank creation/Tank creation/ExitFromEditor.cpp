#include "ExitFromEditor.h"


ExitFromEditor::ExitFromEditor(string &fileName, Graphic *forCopyWindow, string tankName, bool canSave) : NotificationWindow(fileName, forCopyWindow), canSave(canSave), tankName(tankName)
{
	fileIn.close();
}


void ExitFromEditor::work()
{
	if (graphic->getTimeAsMilliseconds() / coefficientForTime - timer >= timeForWork)
	{
		timer += timeForWork;

		if (needWindowResult)
		{
			if ((windowResult.size() > 13 && windowResult.substr(0, 13) == "Saved/Rename/") || windowResult == "Saved/")
			{
				windowResult = "Exit/" + windowResult;

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
				windowResult = "Cancel/";

				windowIsOpen = false;
				return;
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
				if (button[i].getStruct()->buttonName == "Cancel")
				{
					windowResult = "Cancel/";

					windowIsOpen = false;
					return;
				}
				if (button[i].getStruct()->buttonName == "Yes")
				{
					windowResult = "Exit/";

					windowIsOpen = false;
					return;
				}
				else
				{
					needNewWindow = true;

					if (canSave && tankName == "")
					{
						needWindowResult = true;

						string fileName = "Data/Data for save tank.dat";

						graphic->drawInRenderTexture(button);

						newWindow = new SaveTank(fileName, graphic);

						button[i].setActivateAnAction(false);
					}
					else if (canSave)
					{
						needWindowResult = true;

						string fileName = "Data/Data for saved.dat";

						graphic->drawInRenderTexture(button);

						newWindow = new Saved(fileName, graphic);

						button[i].setActivateAnAction(false);
					}
					else
					{
						string fileName = "Data/Data for not available.dat";

						graphic->drawInRenderTexture(button);

						newWindow = new NotAvailable(fileName, graphic);

						button[i].setActivateAnAction(false);
					}
				}
			}

		}

		graphic->draw(button);
	}
}