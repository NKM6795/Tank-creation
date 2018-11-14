#include "ListDraw.h"


ListDraw::ListDraw(List &list, vector<ComponentDraw *> components) : components(&components)
{
	needButton = false;

	if (list.getButton() != nullptr)
	{
		needButton = true;

		button = new ButtonDraw;

		button->setInformation(*list.getButton()->getStruct());
	}
}


void ListDraw::draw(RenderTexture &renderTexture, List &list, long timer)
{
	renderTexture.clear(Color(84, 63, 37));

	objectDraw(renderTexture, timer, list.getObjects(), (*components));

	button->drawButton(renderTexture, *list.getButton()->getStruct());
}