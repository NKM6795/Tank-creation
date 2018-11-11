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
	}
}

TrackDraw::~TrackDraw()
{
	delete[] trackSprite;

	delete[] trackTexture;
}


void TrackDraw::draw(RenderTexture &renderTexture, long timer, Object *object)
{
	if (object->needDraw && object->getHealth() > 0 && object->getHealth() <= object->getComponentParameter()->healthPoints)
	{
		int index = object->getPosition().x % numberOfVariant;

		trackSprite[index].setPosition(float(object->getPosition().x), float(object->getPosition().y));

		renderTexture.draw(trackSprite[index]);
	}
}
