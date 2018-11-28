#include "ListDraw.h"


ListDraw::ListDraw(List &list, vector<ComponentDraw *> &components) : components(&components)
{
	needButton = false;

	if (list.getNeedButton())
	{
		needButton = true;

		button = new ButtonDraw;

		button->setInformation(*list.getButton()->getStruct());
	}

	font.loadFromFile(list.getFileName());

	text.setFont(font);
	text.setFillColor(Color::White);
	text.setCharacterSize(list.getViewableObjectHeight() / 2);

	Image image;
	if (list.getViewableObjectWidth() == 100)
	{
		image.create(list.getWidth() - 18 - list.getFragmentHeight() + list.getViewableObjectHeight() - list.getViewableObjectWidth(), list.getHeight() - (list.getFragmentHeight() - list.getViewableObjectHeight()), Color(84, 63, 37));
	}
	else
	{
		image.create(list.getWidth() - 18 - list.getFragmentHeight() + list.getViewableObjectHeight() - list.getViewableObjectWidth(), list.getHeight() - list.getFragmentHeight() + list.getViewableObjectHeight() - list.getViewableObjectWidth(), Color(84, 63, 37));
	}

	backgroundRorInformationTexture.loadFromImage(image);

	backgroundRorInformationSprite.setTexture(backgroundRorInformationTexture);
	backgroundRorInformationSprite.setPosition(float(list.getFragmentHeight() - list.getViewableObjectHeight() + list.getViewableObjectWidth()), float((list.getFragmentHeight() - list.getViewableObjectHeight()) / 2 + ((list.getViewableObjectWidth() == 100) ? 0 : list.getSearchEngineHeight())));


	image.create(list.getWidth(), list.getSearchEngineHeight() - 3, Color(84, 63, 37));

	backgroundRorSearchEngineHeightTexture.loadFromImage(image);
	backgroundRorSearchEngineHeightSprite.setTexture(backgroundRorSearchEngineHeightTexture);
	
	information.setFont(font);
	information.setFillColor(Color::White);
	information.setCharacterSize(list.getViewableObjectHeight() / 3 + 2);
}


ListDraw::~ListDraw()
{
	if (needButton)
	{
		delete button;
	}
}


void ListDraw::drawInformation(RenderTexture &renderTexture, List &list, long timer)
{
	vector<ViewableObject *> selectedViewableObject = list.getHighlightedViewableObject();

	if (selectedViewableObject.size() == 0)
	{
		return;
	}

	renderTexture.draw(backgroundRorInformationSprite);
	drawFramework(renderTexture, int(backgroundRorInformationSprite.getPosition().x), int(backgroundRorInformationSprite.getPosition().y), int(backgroundRorInformationSprite.getPosition().x + backgroundRorInformationSprite.getLocalBounds().width), int(backgroundRorInformationSprite.getPosition().y + backgroundRorInformationSprite.getLocalBounds().height));

	selectedViewableObject.back()->setPosition(list.getFragmentHeight() - list.getViewableObjectHeight() + list.getViewableObjectWidth() + 5, (list.getFragmentHeight() - list.getViewableObjectHeight()) / 2 + 5 + ((list.getViewableObjectWidth() == 100) ? 0 : list.getSearchEngineHeight()));
	objectDraw(renderTexture, timer, selectedViewableObject, (*components));

	float x = float(list.getFragmentHeight() - list.getViewableObjectHeight() + list.getViewableObjectWidth() + 5),
		y = float((list.getFragmentHeight() - list.getViewableObjectHeight()) / 2 + 5 + selectedViewableObject.back()->getComponentParameter()->height * 20 + 5 + ((list.getViewableObjectWidth() == 100) ? 0 : list.getSearchEngineHeight()));

	string textForInformation;

	if (list.getViewableObjectWidth() == 100)
	{
		x = float(2 * (list.getFragmentHeight() - list.getViewableObjectHeight()) + list.getViewableObjectWidth() + selectedViewableObject.back()->getComponentParameter()->width * 20);
		y = float((list.getFragmentHeight() - list.getViewableObjectHeight()) / 2);

		textForInformation = "Name: ";
		information.setPosition(x, y);
		information.setString(textForInformation);
		y += list.getViewableObjectHeight() / 3 + 7;
		renderTexture.draw(information);

		textForInformation = selectedViewableObject.back()->getComponentParameter()->name;
		information.setPosition(x, y);
		information.setString(textForInformation);
		y += list.getViewableObjectHeight() / 3 + 7;
		renderTexture.draw(information);
	}
	else
	{
		textForInformation = "Name: " + selectedViewableObject.back()->getComponentParameter()->name;
		information.setPosition(x, y);
		information.setString(textForInformation);
		y += list.getViewableObjectHeight() / 3 + 7;
		renderTexture.draw(information);
	}

	if (selectedViewableObject.back()->getHealth() > 1)
	{
		textForInformation = "Healht: " + to_string(selectedViewableObject.back()->getHealth());
		information.setPosition(x, y);
		information.setString(textForInformation);
		y += list.getViewableObjectHeight() / 3 + 7;
		renderTexture.draw(information);
	}

	if (selectedViewableObject.back()->getComponentParameter()->cost > 0)
	{
		textForInformation = "Cost: " + to_string(selectedViewableObject.back()->getComponentParameter()->cost);
		information.setPosition(x, y);
		information.setString(textForInformation);
		y += list.getViewableObjectHeight() / 3 + 7;
		renderTexture.draw(information);
	}

	if (typeid(*selectedViewableObject.back()) == typeid(Gun))
	{
		textForInformation = "Damage: " + to_string(selectedViewableObject.back()->getComponentParameter()->damage);
		information.setPosition(x, y);
		information.setString(textForInformation);
		y += list.getViewableObjectHeight() / 3 + 7;
		renderTexture.draw(information);

		textForInformation = "Bullet speed: " + (selectedViewableObject.back()->getComponentParameter()->bulletSpeed == -1 ? "50 - 200" : to_string(selectedViewableObject.back()->getComponentParameter()->bulletSpeed));
		information.setPosition(x, y);
		information.setString(textForInformation);
		y += list.getViewableObjectHeight() / 3 + 7;
		renderTexture.draw(information);

		textForInformation = "Reload: " + to_string(selectedViewableObject.back()->getComponentParameter()->reload);
		information.setPosition(x, y);
		information.setString(textForInformation);
		y += list.getViewableObjectHeight() / 3 + 7;
		renderTexture.draw(information);
	}

	if (typeid(*selectedViewableObject.back()) == typeid(EngineRoom))
	{
		textForInformation = "Feature: main element";
		information.setPosition(x, y);
		information.setString(textForInformation);
		y += list.getViewableObjectHeight() / 3 + 7;
		renderTexture.draw(information);
	}

	if (typeid(*selectedViewableObject.back()) == typeid(Track))
	{
		textForInformation = "Feature: can move the tank";
		information.setPosition(x, y);
		information.setString(textForInformation);
		y += list.getViewableObjectHeight() / 3 + 7;
		renderTexture.draw(information);
	}

	if (selectedViewableObject.back()->getComponentParameter()->canRebound)
	{
		textForInformation = "Feature: can rebound bullet";
		information.setPosition(x, y);
		information.setString(textForInformation);
		y += list.getViewableObjectHeight() / 3 + 7;
		renderTexture.draw(information);
	}

	delete selectedViewableObject.back();
}


void ListDraw::draw(RenderTexture &renderTexture, List &list, long timer)
{
	if (list.isOpen())
	{
		renderTexture.clear(Color(84, 63, 37));

		objectDraw(renderTexture, timer, list.getViewableObjects(), (*components));

		for (int i = 0; i < int(list.getViewableObjects().size()); ++i)
		{
			if (list.getViewableObjects()[i]->needDraw)
			{
				text.setPosition(float(list.getFragmentHeight() - list.getViewableObjectHeight() + list.getViewableObjectWidth() + (list.getViewableObjectWidth() == 100 ? 20 : 0)), float(i * list.getFragmentHeight() + list.getFragmentHeight() - list.getViewableObjectHeight() - list.getPosition() + list.getSearchEngineHeight()));
				text.setString(list.getViewableObjects()[i]->getComponentParameter()->name);

				renderTexture.draw(text);
			}
		}

		if (list.getNeedButton())
		{
			drawLine(renderTexture, list.getWidth() - 10, list.getSearchEngineHeight(), list.getWidth() - 10, list.getHeight(), Color::Black);

			button->drawButton(renderTexture, *list.getButton()->getStruct());
		}

		if (list.getIndex() != -1)
		{
			drawRectangle(renderTexture, 2, list.getIndex() * list.getFragmentHeight() - list.getPosition() + 1 + list.getSearchEngineHeight(), list.getWidth() - (needButton ? 11 : 0) - 1, (list.getIndex() + 1) * list.getFragmentHeight() - 1 - list.getPosition() - 1 + list.getSearchEngineHeight(), Color::White);
		}
		if (list.getIndexOfSelectedObject() != -1)
		{
			drawRectangle(renderTexture, 1, list.getIndexOfSelectedObject() * list.getFragmentHeight() - list.getPosition() + list.getSearchEngineHeight(), list.getWidth() - (needButton ? 11 : 0), (list.getIndexOfSelectedObject() + 1) * list.getFragmentHeight() - 1 - list.getPosition() + list.getSearchEngineHeight(), Color::Blue);
		}

		renderTexture.draw(backgroundRorSearchEngineHeightSprite);

		information.setPosition(float(list.getFragmentHeight() - list.getViewableObjectHeight()) / 2, 0.f);
		information.setString(list.getInputField());
		renderTexture.draw(information);

		drawFramework(renderTexture, 0, 0, list.getWidth(), list.getSearchEngineHeight() - 3);
		
		if (list.getNeedInformation())
		{
			drawInformation(renderTexture, list, timer);
		}
	}
}