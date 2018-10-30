#pragma once


#include "BaseElement.h"


struct ButtonParameter
{
	int xCoordinate;
	int yCoordinate;

	int width;
	int height;
	float scale;

	int maxTimerForPointing;
	int maxTimerForPressing;
	float epsilonForScale;
	bool checkTimerForPointing;
	bool checkTimerForPressing;
	bool checkButtonIsPressed;

	int timerPointing;
	int timerPressing;

	int characterSize;
	
	string fileName;
	string buttonType;
	string buttonName;
	string fontName;

	bool activateAnAction;
};


class Button
{
private:
	ButtonParameter button;

public:
	void setInformation(int xCoordinate, int yCoordinate, int width, int height, int characterSize, string &buttonName, string &buttonType, string &fontName);

	void work(Vector2int mousePosition, bool isPressed, long timer, int fps);

	void setXPosition(int xCoordinate);

	int getXPosition();

	void setYPosition(int yCoordinate);

	int getYPosition();

	void setMaxTimerForPointing(int newMaxTimerForPointing);

	int getMaxTimerForPointing();

	void setActivateAnAction(bool activateAnAction);

	bool getActivateAnAction();

	string getNameOfButton();

	ButtonParameter *getStruct();
};
