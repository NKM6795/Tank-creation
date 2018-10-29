#include "WindowController.h"


void windowController(WorkWithWindow *window)
{
	while (window->isOpen())
	{
		window->work();

		if (window->getNeedNewWindow())
		{
			WorkWithWindow *newWindow = window->getNewWindow();

			windowController(newWindow);

			window->finishNewWindow();
		}
	}
}