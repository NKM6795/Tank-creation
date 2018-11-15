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
	text.setCharacterSize(list.getObjectHeight() / 2);

	Image image;
	image.create(list.getWidth() - (needButton ? 18 : 0) - list.getFragmentHeight() + list.getObjectHeight() - list.getObjectWidth(), list.getHeight() - list.getFragmentHeight() + list.getObjectHeight() - list.getObjectWidth(), Color(84, 63, 37));
	
	backgroundRorInformationTexture.loadFromImage(image);

	backgroundRorInformationSprite.setTexture(backgroundRorInformationTexture);
	backgroundRorInformationSprite.setPosition(float(list.getFragmentHeight() - list.getObjectHeight() + list.getObjectWidth()), float((list.getFragmentHeight() - list.getObjectHeight()) / 2));

	information.setFont(font);
	information.setFillColor(Color::White);
	information.setCharacterSize(list.getObjectHeight() / 3 + 2);
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

	vector<Object *> selectedObject = list.getSelectedObject();

	selectedObject.back()->setPosition(list.getFragmentHeight() - list.getObjectHeight() + list.getObjectWidth() + 5, (list.getFragmentHeight() - list.getObjectHeight()) / 2 + 5);

	objectDraw(renderTexture, timer, selectedObject, (*components));

	float x = float(list.getFragmentHeight() - list.getObjectHeight() + list.getObjectWidth() + 5),
		y = float((list.getFragmentHeight() - list.getObjectHeight()) / 2 + 5 + selectedObject.back()->getComponentParameter()->height * 20 + 5);

	string textForInformation;

	textForInformation = "Name: " + selectedObject.back()->getComponentParameter()->name;
	information.setPosition(x, y);
	information.setString(textForInformation);
	y += list.getObjectHeight() / 3 + 7;
	renderTexture.draw(information);

	textForInformation = "Healht: " + to_string(selectedObject.back()->getHealth());
	information.setPosition(x, y);
	information.setString(textForInformation);
	y += list.getObjectHeight() / 3 + 7;
	renderTexture.draw(information);

	if (typeid(*selectedObject.back()) == typeid(Gun))
	{
		textForInformation = "Damage: " + to_string(selectedObject.back()->getComponentParameter()->damage);
		information.setPosition(x, y);
		information.setString(textForInformation);
		y += list.getObjectHeight() / 3 + 7;
		renderTexture.draw(information);

		textForInformation = "Bullet speed: " + (selectedObject.back()->getComponentParameter()->bulletSpeed == -1 ? "50 - 200" : to_string(selectedObject.back()->getComponentParameter()->bulletSpeed));
		information.setPosition(x, y);
		information.setString(textForInformation);
		y += list.getObjectHeight() / 3 + 7;
		renderTexture.draw(information);

		textForInformation = "Reload: " + to_string(selectedObject.back()->getComponentParameter()->reload);
		information.setPosition(x, y);
		information.setString(textForInformation);
		y += list.getObjectHeight() / 3 + 7;
		renderTexture.draw(information);
	}

	if (typeid(*selectedObject.back()) == typeid(EngineRoom))
	{
		textForInformation = "Feature: main element";
		information.setPosition(x, y);
		information.setString(textForInformation);
		y += list.getObjectHeight() / 3 + 7;
		renderTexture.draw(information);
	}

	if (typeid(*selectedObject.back()) == typeid(Track))
	{
		textForInformation = "Feature: can move the tank";
		information.setPosition(x, y);
		information.setString(textForInformation);
		y += list.getObjectHeight() / 3 + 7;
		renderTexture.draw(information);
	}

	if (selectedObject.back()->getComponentParameter()->canRebound)
	{
		textForInformation = "Feature: can rebound bullet";
		information.setPosition(x, y);
		information.setString(textForInformation);
		y += list.getObjectHeight() / 3 + 7;
		renderTexture.draw(information);
	}
}


void ListDraw::draw(RenderTexture &renderTexture, List &list, long timer)
{
	if (list.isOpen())
	{
		renderTexture.clear(Color(84, 63, 37));

		objectDraw(renderTexture, timer, list.getObjects(), (*components));

		for (int i = 0; i < int(list.getObjects().size()); ++i)
		{
			text.setPosition(float(list.getFragmentHeight() - list.getObjectHeight() + list.getObjectWidth()), float(i * list.getFragmentHeight() + list.getFragmentHeight() - list.getObjectHeight() - list.getPosition()));
			text.setString(list.getObjects()[i]->getComponentParameter()->name);

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