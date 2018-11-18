#include "Button.h"


Button::Button()
{

}

Button::Button(int xCoordinate, int yCoordinate, int width, int height, int characterSize, string buttonName, string buttonType, string fontName)
{
	setInformation(xCoordinate, yCoordinate, width, height, characterSize, buttonName, buttonType, fontName);
}

void Button::setInformation(int xCoordinate, int yCoordinate, int width, int height, int characterSize, string buttonName, string buttonType, string fontName)
{
	button.maxTimerForPointing = 200;
	button.maxTimerForPressing = 50;
	button.epsilonForScale = 0.1f;
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

void Button::work(Vector2int mousePosition, bool isPressed, long timer, int fps)
{
	int deltaPointing = abs(int(button.timerPointing - timer)),
		deltaPressing = abs(int(button.timerPressing - timer));

	bool mouseInArea = inArea(button.width, button.height, button.xCoordinate, button.yCoordinate, mousePosition);

	if (mouseInArea || button.checkButtonIsPressed)
	{
		button.timerPointing = deltaPointing <= 16 ? timer : button.timerPointing + 2 * fps;
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
		button.timerPressing = deltaPressing <= 16 ? timer : button.timerPressing + 2 * fps;
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

	if (deltaPointing >= button.maxTimerForPointing && button.checkTimerForPointing)
	{
		button.timerPointing = timer - button.maxTimerForPointing;
	}

	if (deltaPressing >= button.maxTimerForPressing && button.checkTimerForPressing)
	{
		button.timerPressing = timer - button.maxTimerForPressing;
	}

	button.scale = 1 - button.epsilonForScale * ((1.f * deltaPointing * deltaPointing) / (1.f * button.maxTimerForPointing * button.maxTimerForPointing) + (1.f * (button.maxTimerForPressing - deltaPressing) * (button.maxTimerForPressing - deltaPressing)) / (2.f * (button.maxTimerForPressing /*+ button.maxTimerForPointing*/) * (button.maxTimerForPressing /*+ button.maxTimerForPointing*/)));
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