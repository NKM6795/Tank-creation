#include "WorkWithWindow.h"


void WorkWithWindow::forConstructor(string &fileName)
{
	windowIsOpen = true;
	needNewWindow = false;

	fileIn.open(fileName);

	getline(fileIn, windowName);

	fileIn >> xCoordinate >> yCoordinate >> screanWidth >> screanHeight;

	fileIn >> timeForWork;

	fileIn >> numberOfButton;
	if (numberOfButton != 0)
	{
		button = new Button[numberOfButton];

		int countOfSimilarButton;
		int firstParameters[5];
		string secondParameters[3];

		for (int i = 0; i < numberOfButton;)
		{
			fileIn >> countOfSimilarButton;

			for (int j = 2; j < 5; ++j)
			{
				fileIn >> firstParameters[j];
			}
			getline(fileIn, secondParameters[0]);
			for (int j = 1; j < 3; ++j)
			{
				getline(fileIn, secondParameters[j]);
			}

			for (int j = i; j < i + countOfSimilarButton; ++j)
			{
				fileIn >> firstParameters[0] >> firstParameters[1];
				getline(fileIn, secondParameters[0]);
				if (secondParameters[0] != " ")
				{
					secondParameters[0].erase(secondParameters[0].begin());
				}
				button[j].setInformation(firstParameters[0], firstParameters[1], firstParameters[2], firstParameters[3], firstParameters[4], secondParameters[0], secondParameters[1], secondParameters[2]);
			}
			i += countOfSimilarButton;
		}
	}

	fileIn >> numberOfText;
	if (numberOfText != 0)
	{
		textXCoordinate = new int[numberOfText];
		textYCoordinate = new int[numberOfText];
		characterSize = new int[numberOfText];
		text = new string[numberOfText];
		fontName = new string[numberOfText];

		int countOfSimilarText;
		int firstParameters[3];
		string secondParameters[2];

		for (int i = 0; i < numberOfText;)
		{
			fileIn >> countOfSimilarText;

			for (int j = 2; j < 3; ++j)
			{
				fileIn >> firstParameters[j];
			}
			getline(fileIn, secondParameters[0]);
			for (int j = 1; j < 2; ++j)
			{
				getline(fileIn, secondParameters[j]);
			}

			for (int j = i; j < i + countOfSimilarText; ++j)
			{
				fileIn >> firstParameters[0] >> firstParameters[1];
				getline(fileIn, secondParameters[0]);
				if (secondParameters[0] != " ")
				{
					secondParameters[0].erase(secondParameters[0].begin());
				}

				textXCoordinate[j] = firstParameters[0];
				textYCoordinate[j] = firstParameters[1];
				characterSize[j] = firstParameters[2];
				text[j] = secondParameters[0];
				fontName[j] = secondParameters[1];
			}
			i += countOfSimilarText;
		}
	}
}

Graphic *WorkWithWindow::getGraphic()
{
	return graphic;
}

bool WorkWithWindow::isOpen()
{
	return windowIsOpen;
}

bool WorkWithWindow::getNeedNewWindow()
{
	return needNewWindow;
}

void WorkWithWindow::finishNewWindow()
{
	needNewWindow = false;
	delete newWindow;
}

WorkWithWindow *WorkWithWindow::getNewWindow()
{
	return newWindow;
}