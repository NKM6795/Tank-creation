#include "MainMenu.h"


MainMenu::MainMenu(string &fileName) : WorkWithWindow(fileName)
{
	fileIn.close();
}

MainMenu::~MainMenu()
{

}

void MainMenu::work()
{
	if (graphic->getTimeAsMilliseconds() / coefficientForTime - timer >= timeForWork)
	{
		timer += timeForWork;

		if (needWindowResult)
		{
			if (windowResult != "Cancel/")
			{
				needNewWindow = true;

				string fileName = "Data/Data for editor.dat";

				newWindow = new Editor(fileName, graphic, windowResult);

				needWindowResult = false;

				return;
			}
			needWindowResult = false;
		}

		mousePosition = graphic->getPositionOfMouse();

		while (graphic->pollEvent())
		{
			if (graphic->getEvent().type == Event::Closed || (graphic->getEvent().type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Escape)))
			{
				graphic->close();
				windowIsOpen = false;
				return;
			}
		}


		for (auto i = button.begin(); i != button.end(); ++i)
		{
			i->second.work(mousePosition * (graphic->hasFocus() ? 1 : -100), Mouse::isButtonPressed(Mouse::Left) && graphic->hasFocus(), timer, timeForWork);
		}
		if (button["Exit"].getActivateAnAction())
		{
			graphic->close();
			windowIsOpen = false;
			return;
		}
		else if (button["Create a new tank"].getActivateAnAction())
		{
			needNewWindow = true;

			string fileName = "Data/Data for editor.dat";

			newWindow = new Editor(fileName, graphic);

			button["Create a new tank"].setActivateAnAction(false);
		}
		else if (button["Modify an existing tank"].getActivateAnAction())
		{
			needNewWindow = true;
			needWindowResult = true;

			string fileName = "Data/Data for tank selection.dat";

			newWindow = new TankSelection(fileName, graphic);

			button["Modify an existing tank"].setActivateAnAction(false);
		}
		else if (button["Battle with the bot"].getActivateAnAction())
		{
			needNewWindow = true;

			string fileName = "Data/Data for not available.dat";

			graphic->drawInRenderTexture(button);

			newWindow = new NotAvailable(fileName, graphic);

			button["Battle with the bot"].setActivateAnAction(false);
		}
		else if (button["Battle with the player"].getActivateAnAction())
		{
			needNewWindow = true;

			string fileName = "Data/Data for not available.dat";

			graphic->drawInRenderTexture(button);

			newWindow = new NotAvailable(fileName, graphic);

			button["Battle with the player"].setActivateAnAction(false);
		}
		else if (button["Settings"].getActivateAnAction())
		{
			needNewWindow = true;

			string fileName = "Data/Data for not available.dat";

			graphic->drawInRenderTexture(button);

			newWindow = new NotAvailable(fileName, graphic);

			button["Settings"].setActivateAnAction(false);
		}

		graphic->draw(button);
	}
}