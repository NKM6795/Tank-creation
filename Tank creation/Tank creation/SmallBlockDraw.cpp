#include "SmallBlockDraw.h"


SmallBlockDraw::SmallBlockDraw(ComponentParameter *component)
{
	numberOfVariant = component->numberOfVariant;

	smallBlockTexture = new Texture[numberOfVariant];
	smallBlockSprite = new Sprite[numberOfVariant];

	for (int i = 0; i < numberOfVariant; ++i)
	{
		string fileName = component->objectName + component->typeName + component->identifierName + to_string(i + 1) + string(".png");

		smallBlockTexture[i].loadFromFile(fileName);

		smallBlockSprite[i].setTexture(smallBlockTexture[i]);
	}
}

SmallBlockDraw::~SmallBlockDraw()
{
	delete[] smallBlockSprite;

	delete[] smallBlockTexture;
}


void SmallBlockDraw::draw(RenderTexture &renderTexture, long timer, ViewableObject *object, int compulsoryDrawing)
{
	if (((!compulsoryDrawing && object->needDraw) || compulsoryDrawing == 1) && object->getHealth() > 0 && object->getHealth() <= object->getComponentParameter()->healthPoints)
	{
		if (compulsoryDrawing == 1)
		{
			object->needDraw = false;
		}

		int index = 3 - (4 * object->getHealth() - 1) / object->getComponentParameter()->healthPoints;

		smallBlockSprite[index].setPosition(float(object->getPosition().x), float(object->getPosition().y));
		smallBlockSprite[index].setColor(object->needChangeColor ? (object->needChangeColor == 1 ? Color::Green : Color::Red) : Color::White);

		renderTexture.draw(smallBlockSprite[index]);
	}
}
