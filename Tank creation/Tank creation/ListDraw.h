#pragma once


#include "ViewableObjectDraw.h"
#include "ButtonDraw.h"
#include "GraphicForNotificationWindow.h"
#include "List.h"


class ListDraw
{
	bool needButton;
	ButtonDraw *button;

	vector<ComponentDraw *> *components;

	Font font;
	Text text;

	bool needInformation;

	Texture backgroundRorInformationTexture;
	Sprite backgroundRorInformationSprite;

	Text information;

	void drawInformation(RenderTexture &renderTexture, List &list, long timer);

public:
	ListDraw(List &list, vector<ComponentDraw *> &components);

	~ListDraw();

	void draw(RenderTexture &renderTexture, List &list, long timer);
};