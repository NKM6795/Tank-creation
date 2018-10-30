#include "WindowController.h"

int main()
{
	string fileName = "Data/Data for main menu.dat";

	WorkWithWindow *window = new MainMenu(fileName);

	windowController(window);

	delete window;

	return 0;
}