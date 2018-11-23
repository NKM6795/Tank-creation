#include "BackgroundDraw.h"


BackgroundDraw::BackgroundDraw(ComponentParameter *component)
{
	numberOfVariant = component->numberOfVariant;

	backgroundTexture = new Texture[numberOfVariant];
	backgroundSprite = new Sprite[numberOfVariant];

	for (int i = 0; i < numberOfVariant; ++i)
	{
		string fileName = component->objectName + component->typeName + component->identifierName + to_string(i + 1) + string(".png");

		backgroundTexture[i].loadFromFile(fileName);
		
		backgroundSprite[i].setTexture(backgroundTexture[i]);
	}
}

BackgroundDraw::~BackgroundDraw()
{
	delete[] backgroundSprite;
	
	delete[] backgroundTexture;
}


void BackgroundDraw::draw(RenderTexture &renderTexture, long timer, ViewableObject *object)
{
	if (object->needDraw)
	{
		int index = int((timer / 100) % numberOfVariant);

		backgroundSprite[index].setPosition(float(object->getPosition().x), float(object->getPosition().y));
		backgroundSprite[index].setColor(object->needChangeColor ? (object->needChangeColor == 1 ? Color::Green : Color::Red) : Color::White);
		backgroundSprite[index].setScale(object->getScale(), object->getScale());

		renderTexture.draw(backgroundSprite[index]);
	}
}


BackgroundForBattleDraw::BackgroundForBattleDraw(ComponentParameter *component)
{
	numberOfVariant = component->numberOfVariant;

	backgroundTexture = new Texture[numberOfVariant];
	backgroundSprite = new Sprite[numberOfVariant];

	for (int i = 0; i < numberOfVariant; ++i)
	{
		string fileName = component->objectName + component->typeName + component->identifierName + to_string(i + 1) + string(".png");

		backgroundTexture[i].loadFromFile(fileName);

		backgroundSprite[i].setTexture(backgroundTexture[i]);
		backgroundSprite[i].setOrigin(float(component->offsets[i].x), float(component->offsets[i].y));
	}
}

BackgroundForBattleDraw::~BackgroundForBattleDraw()
{
	delete[] backgroundSprite;

	delete[] backgroundTexture;
}


void BackgroundForBattleDraw::draw(RenderTexture &renderTexture, long timer, ViewableObject *object)
{
	if (object->needDraw)
	{
		int index = object->getHealth();

		backgroundSprite[index].setPosition(float(object->getPosition().x), float(object->getPosition().y));
		backgroundSprite[index].setColor(object->needChangeColor ? (object->needChangeColor == 1 ? Color::Green : Color::Red) : Color::White);
		backgroundSprite[index].setScale(object->getScale(), object->getScale());

		renderTexture.draw(backgroundSprite[index]);
	}
}