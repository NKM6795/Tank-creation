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


void SmallBlockDraw::draw(RenderTexture &renderTexture, long timer, Object *object)
{
	if (object->needDraw && object->getHealth() > 0 && object->getHealth() <= object->getComponentParameter()->healthPoints)
	{
		int index = 3 - (4 * object->getHealth() - 1) / object->getComponentParameter()->healthPoints;

		smallBlockSprite[index].setPosition(float(object->getPosition().x), float(object->getPosition().y));

		renderTexture.draw(smallBlockSprite[index]);
	}
}
