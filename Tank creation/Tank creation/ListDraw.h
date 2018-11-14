#pragma once


#include "ObjectDraw.h"
#include "ButtonDraw.h"
#include "GraphicForNotificationWindow.h"
#include "List.h"


class ListDraw
{
	bool needButton;
	ButtonDraw *button;

	vector<ComponentDraw *> *components;

public:
	ListDraw(List &list, vector<ComponentDraw *> &components);

	~ListDraw();

	void draw(RenderTexture &renderTexture, List &list, long timer);
};