#include "TrackDraw.h"


TrackDraw::TrackDraw(ComponentParameter *component)
{
	numberOfVariant = component->numberOfVariant;

	trackTexture = new Texture[numberOfVariant];
	trackSprite = new Sprite[numberOfVariant];

	for (int i = 0; i < numberOfVariant; ++i)
	{
		string fileName = component->objectName + component->typeName + component->identifierName + to_string(i + 1) + string(".png");

		trackTexture[i].loadFromFile(fileName);

		trackSprite[i].setTexture(trackTexture[i]);

		if (component->width == 6)
		{
			trackSprite[i].setOrigin(1.f, 1.f);
		}
	}
}

TrackDraw::~TrackDraw()
{
	delete[] trackSprite;

	delete[] trackTexture;
}


void TrackDraw::draw(RenderTexture &renderTexture, long timer, ViewableObject *object, int compulsoryDrawing)
{
	if (((!compulsoryDrawing && object->needDraw) || compulsoryDrawing == 1) && object->getHealth() > 0 && object->getHealth() <= object->getComponentParameter()->healthPoints)
	{
		if (compulsoryDrawing == 1)
		{
			object->needDraw = false;
		}

		int index = object->getComponentParameter()->backgroundIndex;

		trackSprite[index].setPosition(float(object->getPosition().x), float(object->getPosition().y));
		trackSprite[index].setColor(object->needChangeColor ? (object->needChangeColor == 1 ? Color::Green : Color::Red) : Color::White);
		trackSprite[index].setScale(object->getScale(), object->getScale());

		renderTexture.draw(trackSprite[index]);
	}
}
