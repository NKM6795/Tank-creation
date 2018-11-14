#include "ListDraw.h"


ListDraw::ListDraw(List &list, vector<ComponentDraw *> &components) : components(&components)
{
	needButton = false;

	if (list.getButton() != nullptr)
	{
		needButton = true;

		button = new ButtonDraw;

		button->setInformation(*list.getButton()->getStruct());
	}
}


ListDraw::~ListDraw()
{
	if (needButton)
	{
		delete button;
	}
}


void ListDraw::draw(RenderTexture &renderTexture, List &list, long timer)
{
	renderTexture.clear(Color(84, 63, 37));

	objectDraw(renderTexture, timer, list.getObjects(), (*components));

	if (needButton)
	{
		drawLine(renderTexture, list.getWidth() - 10, 0, list.getWidth() - 10, list.getHeight(), Color::Black);

		button->drawButton(renderTexture, *list.getButton()->getStruct());
	}

	drawRectangle(renderTexture, 1, list.getIndex() * list.getFragmentHeight(), list.getWidth() - (needButton ? 11 : 0), (list.getIndex() + 1) * list.getFragmentHeight() - 1, Color::White);
}