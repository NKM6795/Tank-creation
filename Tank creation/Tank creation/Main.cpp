#include "WindowController.h"

int main()
{
	string fileName = "Data/Date for main menu.dat";

	WorkWithWindow *window = new MainMenu(fileName);

	windowController(window);

	delete window;

	return 0;
}