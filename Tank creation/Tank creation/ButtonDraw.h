#pragma once


#include "BasicElementDraw.h"
#include "Button.h"


class ButtonDraw
{
	Texture buttonTexture;
	Sprite buttonSprite;
	Text textForButton;
	Font font;
	void setInformationPrivate(ButtonParameter &button);

public:
	void setInformation(ButtonParameter &button);

	void drawButton(RenderTexture &renderTexture, ButtonParameter &button);

	Sprite *getSprite();
};
