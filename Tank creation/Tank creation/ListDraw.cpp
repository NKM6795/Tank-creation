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

	font.loadFromFile(list.getFileName());

	text.setFont(font);
	text.setFillColor(Color::White);
	text.setCharacterSize(list.getViewableObjectHeight() / 2);

	Image image;
	if (list.getViewableObjectWidth() == 100)
	{
		image.create(list.getWidth() - (needButton ? 18 : 0) - list.getFragmentHeight() + list.getViewableObjectHeight() - list.getViewableObjectWidth(), list.getHeight() - (list.getFragmentHeight() - list.getViewableObjectHeight()), Color(84, 63, 37));
	}
	else
	{
		image.create(list.getWidth() - (needButton ? 18 : 0) - list.getFragmentHeight() + list.getViewableObjectHeight() - list.getViewableObjectWidth(), list.getHeight() - list.getFragmentHeight() + list.getViewableObjectHeight() - list.getViewableObjectWidth(), Color(84, 63, 37));
	}

	backgroundRorInformationTexture.loadFromImage(image);

	backgroundRorInformationSprite.setTexture(backgroundRorInformationTexture);
	backgroundRorInformationSprite.setPosition(float(list.getFragmentHeight() - list.getViewableObjectHeight() + list.getViewableObjectWidth()), float((list.getFragmentHeight() - list.getViewableObjectHeight()) / 2));

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
	renderTexture.draw(backgroundRorInformationSprite);

	drawFramework(renderTexture, int(backgroundRorInformationSprite.getPosition().x), int(backgroundRorInformationSprite.getPosition().y), int(backgroundRorInformationSprite.getPosition().x + backgroundRorInformationSprite.getLocalBounds().width), int(backgroundRorInformationSprite.getPosition().y + backgroundRorInformationSprite.getLocalBounds().height));

	vector<ViewableObject *> selectedViewableObject = list.getSelectedViewableObject();

	selectedViewableObject.back()->setPosition(list.getFragmentHeight() - list.getViewableObjectHeight() + list.getViewableObjectWidth() + 5, (list.getFragmentHeight() - list.getViewableObjectHeight()) / 2 + 5);

	objectDraw(renderTexture, timer, selectedViewableObject, (*components));

	float x = float(list.getFragmentHeight() - list.getViewableObjectHeight() + list.getViewableObjectWidth() + 5),
		y = float((list.getFragmentHeight() - list.getViewableObjectHeight()) / 2 + 5 + selectedViewableObject.back()->getComponentParameter()->height * 20 + 5);

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
}


void ListDraw::draw(RenderTexture &renderTexture, List &list, long timer)
{
	if (list.isOpen())
	{
		renderTexture.clear(Color(84, 63, 37));

		objectDraw(renderTexture, timer, list.getViewableObjects(), (*components));

		for (int i = 0; i < int(list.getViewableObjects().size()); ++i)
		{
			text.setPosition(float(list.getFragmentHeight() - list.getViewableObjectHeight() + list.getViewableObjectWidth() + (list.getViewableObjectWidth() == 100 ? 20 : 0)), float(i * list.getFragmentHeight() + list.getFragmentHeight() - list.getViewableObjectHeight() - list.getPosition()));
			text.setString(list.getViewableObjects()[i]->getComponentParameter()->name);

			renderTexture.draw(text);
		}

		if (needButton)
		{
			drawLine(renderTexture, list.getWidth() - 10, 0, list.getWidth() - 10, list.getHeight(), Color::Black);

			button->drawButton(renderTexture, *list.getButton()->getStruct());
		}

		drawRectangle(renderTexture, 1, list.getIndex() * list.getFragmentHeight() - list.getPosition(), list.getWidth() - (needButton ? 11 : 0), (list.getIndex() + 1) * list.getFragmentHeight() - 1 - list.getPosition(), Color::White);


		if (list.getNeedInformation())
		{
			drawInformation(renderTexture, list, timer);
		}
	}
}