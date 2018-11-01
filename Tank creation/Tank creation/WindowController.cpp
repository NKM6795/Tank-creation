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

			if (window->getNeedWindowResult())
			{
				window->setWindowResult(newWindow->getWindowResult());
			}

			window->finishNewWindow();
		}
	}
}