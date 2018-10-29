#include "Button.h"


void Button::setInformation(int xCoordinate, int yCoordinate, int width, int height, int characterSize, string &buttonName, string &buttonType, string &fontName)
{
	button.maxTimerForPointing = 50;
	button.maxTimerForPressing = 20;
	button.epsilonForScale = 0.00005f;
	button.checkTimerForPointing = true;
	button.checkTimerForPressing = true;
	button.checkButtonIsPressed = false;
	button.timerPointing = -button.maxTimerForPointing;
	button.timerPressing = -button.maxTimerForPressing;

	button.characterSize = characterSize;

	button.activateAnAction = false;

	button.xCoordinate = xCoordinate;
	button.yCoordinate = yCoordinate;
	button.width = width;
	button.height = height;
	button.scale = 1;

	button.buttonName = buttonName;
	button.buttonType = buttonType;
	button.fontName = fontName;

	button.fileName = "Data/Images/Button().png";
	button.fileName = button.fileName.insert(button.fileName.find("(") + 1, buttonType);
}

void Button::work(Vector2int mousePosition, bool isPressed)
{
	bool mouseInArea = inArea(button.width, button.height, button.xCoordinate, button.yCoordinate, mousePosition);

	if (mouseInArea || button.checkButtonIsPressed)
	{
		button.timerPointing += button.timerPointing < 0 ? 1 : button.timerPointing > 0 ? -1 : 0;
		button.checkTimerForPointing = false;
	}
	else
	{
		button.checkTimerForPointing = true;
	}

	if (mouseInArea && isPressed && !button.checkButtonIsPressed)
	{
		button.checkButtonIsPressed = true;
	}
	else if (mouseInArea && isPressed && button.checkButtonIsPressed)
	{
		button.timerPressing += button.timerPressing < 0 ? 1 : button.timerPressing > 0 ? -1 : 0;
		button.checkTimerForPressing = false;

		if (button.buttonType == "scrollbar")
		{
			button.activateAnAction = true;
		}
	}
	else if (!mouseInArea && isPressed && button.checkButtonIsPressed)
	{
		button.checkTimerForPressing = true;
	}
	else if (mouseInArea && !isPressed && button.checkButtonIsPressed)
	{
		button.activateAnAction = true;
		button.checkTimerForPressing = true;
		button.checkButtonIsPressed = false;
	}
	else if (!mouseInArea && !isPressed && button.checkButtonIsPressed)
	{
		button.checkButtonIsPressed = false;
		button.checkTimerForPressing = true;
		button.checkTimerForPointing = true;
	}

	if (button.timerPointing > -button.maxTimerForPointing && button.timerPointing < button.maxTimerForPointing && button.checkTimerForPointing)
	{
		button.timerPointing += button.timerPointing > 0 ? 1 : -1;
	}

	if (button.timerPressing > -button.maxTimerForPressing && button.timerPressing < button.maxTimerForPressing && button.checkTimerForPressing)
	{
		button.timerPressing += button.timerPressing > 0 ? 1 : -1;
	}

	button.scale = 1 - button.epsilonForScale * ((button.timerPointing * button.timerPointing) + (button.maxTimerForPressing + button.timerPressing) * (button.maxTimerForPressing + button.timerPressing));
}

void Button::setXPosition(int xCoordinate)
{
	button.xCoordinate = xCoordinate;
}

int Button::getXPosition()
{
	return button.xCoordinate;
}

void Button::setYPosition(int yCoordinate)
{
	button.yCoordinate = yCoordinate;
}

int Button::getYPosition()
{
	return button.yCoordinate;
}

void Button::setMaxTimerForPointing(int newMaxTimerForPointing)
{
	button.maxTimerForPointing = newMaxTimerForPointing;
}

int Button::getMaxTimerForPointing()
{
	return button.maxTimerForPointing;
}

void Button::setActivateAnAction(bool activateAnAction)
{
	button.activateAnAction = activateAnAction;
}

bool Button::getActivateAnAction()
{
	return button.activateAnAction;
}

string Button::getNameOfButton()
{
	return button.buttonName;
}

ButtonParameter *Button::getStruct()
{
	return &button;
}