#include "EngineRoomDraw.h"


EngineRoomDraw::EngineRoomDraw(ComponentParameter *component)
{
	numberOfVariantBackground = component->numberOfVariant;

	backgroundTexture = new Texture[component->numberOfVariant];
	backgroundSprite = new Sprite[component->numberOfVariant];

	for (int i = 0; i < numberOfVariantBackground; ++i)
	{
		string fileName = component->objectName + component->typeName + component->identifierName + to_string(i + 1) + string(".png");

		backgroundTexture[i].loadFromFile(fileName);

		backgroundSprite[i].setTexture(backgroundTexture[i]);
	}

	numberOfVariantRoom = component->numberOfVariant2;

	roomTexture = new Texture[component->numberOfVariant2];
	roomSprite = new Sprite[component->numberOfVariant2];

	for (int i = 0; i < numberOfVariantRoom; ++i)
	{
		string fileName = component->objectName + component->typeName2 + component->identifierName2 + to_string(i + 1) + string(".png");

		roomTexture[i].loadFromFile(fileName);

		roomSprite[i].setTexture(roomTexture[i]);
	}

	numberOfVariantPerson = component->numberOfVariant3;

	personWorksTexture = new Texture[component->numberOfVariant3];
	personWorksSprite = new Sprite[component->numberOfVariant3];

	for (int i = 0; i < numberOfVariantPerson; ++i)
	{
		string fileName = component->objectName + component->typeName3 + component->identifierName3 + to_string(i + 1) + string(".png");

		personWorksTexture[i].loadFromFile(fileName);

		personWorksSprite[i].setTexture(personWorksTexture[i]);
	}

	xOffsetForRoom = component->xOffsetForRoom;
	yOffsetForRoom = component->yOffsetForRoom;

	xOffsetForPerson = component->xOffsetForPerson;
	yOffsetForPerson = component->yOffsetForPerson;
}

EngineRoomDraw::~EngineRoomDraw()
{
	delete[] backgroundTexture;

	delete[] backgroundSprite;

	delete[] roomTexture;

	delete[] roomSprite;

	delete[] personWorksTexture;

	delete[] personWorksSprite;
}


void EngineRoomDraw::draw(RenderTexture &renderTexture, long timer, Object *object)
{
	if (object->needDraw && object->getHealth() > 0 && object->getHealth() <= object->getComponentParameter()->healthPoints)
	{
		int index = 3 - (4 * object->getHealth() - 1) / object->getComponentParameter()->healthPoints;
		
		backgroundSprite[index].setPosition(float(object->getPosition().x), float(object->getPosition().y));
		
		renderTexture.draw(backgroundSprite[index]);


		index = int((timer / 100) % numberOfVariantRoom);

		roomSprite[index].setPosition(float(object->getPosition().x + xOffsetForRoom), float(object->getPosition().y + yOffsetForRoom));

		renderTexture.draw(roomSprite[index]);


		index = int((timer / 100) % numberOfVariantPerson);

		personWorksSprite[index].setPosition(float(object->getPosition().x + xOffsetForPerson), float(object->getPosition().y + yOffsetForPerson));

		renderTexture.draw(personWorksSprite[index]);
	}
}
