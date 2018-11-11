#pragma once


#include "Graphic.h"


class WorkWithWindow
{
private:
	void forConstructor(string &fileName);

protected:
	int xCoordinate;
	int yCoordinate;

	int screanWidth;
	int screanHeight;
	string windowName;

	int numberOfButton;
	Button *button;

	int numberOfText;
	int *textXCoordinate;
	int *textYCoordinate;
	int *characterSize;
	string *text;
	string *fontName;

	long timeForWork;
	long timer;
	long coefficientForTime;

	bool windowIsOpen;

	bool needNewWindow;
	WorkWithWindow *newWindow;

	bool needWindowResult;
	string windowResult;

	Graphic *graphic;

	Vector2int mousePosition;

	ifstream fileIn;		//for constructor

public:
	WorkWithWindow(string &fileName)
	{
		forConstructor(fileName);

		graphic = new Graphic(screanWidth, screanHeight);

		if (numberOfButton != 0)
		{
			graphic->setInformation(numberOfButton, button);
		}

		if (numberOfText != 0)
		{
			graphic->setInformation(numberOfText, text, fontName, characterSize, textXCoordinate, textYCoordinate);
		}
	}

	WorkWithWindow(string &fileName, Graphic *forCopyWindow)
	{
		forConstructor(fileName);

		graphic = new Graphic(forCopyWindow->getWindow());

		if (numberOfButton != 0)
		{
			graphic->setInformation(numberOfButton, button);
		}

		if (numberOfText != 0)
		{
			graphic->setInformation(numberOfText, text, fontName, characterSize, textXCoordinate, textYCoordinate);
		}
	}
	
	virtual ~WorkWithWindow()
	{
		if (numberOfButton != 0)
		{
			delete[] button;
		}

		if (numberOfText != 0)
		{
			delete[] textXCoordinate;

			delete[] textYCoordinate;

			delete[] characterSize;

			delete[] text;

			delete[] fontName;
		}

		delete graphic;
	}

	Graphic *getGraphic();

	bool isOpen();

	bool getNeedNewWindow();

	void finishNewWindow();

	WorkWithWindow *getNewWindow();

	bool getNeedWindowResult();

	string getWindowResult();

	void setWindowResult(string result);

	virtual void work() = 0;
};