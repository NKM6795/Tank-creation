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
				button["Cancel"].setActivateAnAction(true);
			}
			else if (graphic->getEvent().type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Enter))
			{
				button["Save and exit"].setActivateAnAction(true);
			}
		}


		for (auto i = button.begin(); i != button.end(); ++i)
		{
			i->second.work(mousePosition * (graphic->hasFocus() ? 1 : -100), Mouse::isButtonPressed(Mouse::Left) && graphic->hasFocus(), timer, timeForWork);
		}
		if (button["Cancel"].getActivateAnAction())
		{
			windowResult = "Cancel/";

			windowIsOpen = false;
			return;
		}
		else if (button["Yes"].getActivateAnAction())
		{
			windowResult = "Exit/";

			windowIsOpen = false;
			return;
		}
		else if (button["Save and exit"].getActivateAnAction())
		{
			needNewWindow = true;

			if (canSave && tankName == "")
			{
				needWindowResult = true;

				string fileName = "Data/Data for save tank.dat";

				graphic->drawInRenderTexture(button);

				newWindow = new SaveTank(fileName, graphic);
			}
			else if (canSave)
			{
				needWindowResult = true;

				string fileName = "Data/Data for saved.dat";

				graphic->drawInRenderTexture(button);

				newWindow = new Saved(fileName, graphic);
			}
			else
			{
				string fileName = "Data/Data for not available.dat";

				graphic->drawInRenderTexture(button);

				newWindow = new NotAvailable(fileName, graphic, "Tank is not correct");
			}

			button["Save and exit"].setActivateAnAction(false);
		}

		graphic->draw(button);
	}
}