#include "ButtonDraw.h"


void ButtonDraw::setInformation(ButtonParameter &button)
{
	buttonTexture.loadFromFile(button.fileName);

	buttonSprite.setTexture(buttonTexture);
	buttonSprite.setOrigin(button.width * 0.5f, button.height * 0.5f);
	buttonSprite.setPosition(float(button.xCoordinate), float(button.yCoordinate));
	buttonSprite.setScale(float(button.scale), float(button.scale));

	if (button.fontName != "")
	{
		font.loadFromFile(button.fontName);

		textForButton.setFont(font);
		textForButton.setString(button.buttonName);
		textForButton.setCharacterSize(button.characterSize);
		textForButton.setOrigin(textForButton.getLocalBounds().width * 0.5f, textForButton.getLocalBounds().height * 0.5f);
		textForButton.setPosition(float(button.xCoordinate), float(button.yCoordinate) - 7.f);
		textForButton.setScale(float(button.scale), float(button.scale));
	}
}

void ButtonDraw::setInformationPrivate(ButtonParameter &button)
{
	buttonSprite.setPosition(float(button.xCoordinate), float(button.yCoordinate));
	buttonSprite.setScale(float(button.scale), float(button.scale));

	textForButton.setPosition(float(button.xCoordinate), float(button.yCoordinate) - 7.f);
	textForButton.setScale(float(button.scale), float(button.scale));
}

void ButtonDraw::drawButton(RenderTexture &renderTexture, ButtonParameter &button)
{
	setInformationPrivate(button);
	renderTexture.draw(buttonSprite);
	renderTexture.draw(textForButton);
}

Sprite *ButtonDraw::getSprite()
{
	return &buttonSprite;
}