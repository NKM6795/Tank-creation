#include "BigBlockDraw.h"


BigBlockDraw::BigBlockDraw(ComponentParameter *component, ComponentDraw *background) : background(background)
{
	numberOfVariant = component->numberOfVariant;

	bigBlockTexture = new Texture[numberOfVariant];
	bigBlockSprite = new Sprite[numberOfVariant];

	for (int i = 0; i < numberOfVariant; ++i)
	{
		string fileName = component->objectName + component->typeName + component->identifierName + to_string(i + 1) + string(".png");

		bigBlockTexture[i].loadFromFile(fileName);

		bigBlockSprite[i].setTexture(bigBlockTexture[i]);
	}
}

BigBlockDraw::~BigBlockDraw()
{
	delete[] bigBlockSprite;

	delete[] bigBlockTexture;
}


void BigBlockDraw::draw(RenderTexture &renderTexture, long timer, ViewableObject *object, int compulsoryDrawing)
{
	if (((!compulsoryDrawing && object->needDraw) || compulsoryDrawing == 1) && object->getHealth() > 0 && object->getHealth() <= object->getComponentParameter()->healthPoints)
	{
		int index = 3 - (4 * object->getHealth() - 1) / object->getComponentParameter()->healthPoints;

		if (index != 0)
		{
			background->draw(renderTexture, timer, object);
		}
		else
		{
			object->needDraw = false;
		}

		bigBlockSprite[index].setPosition(float(object->getPosition().x), float(object->getPosition().y));
		bigBlockSprite[index].setColor(object->needChangeColor ? (object->needChangeColor == 1 ? Color::Green : Color::Red) : Color::White);

		renderTexture.draw(bigBlockSprite[index]);
	}
}
