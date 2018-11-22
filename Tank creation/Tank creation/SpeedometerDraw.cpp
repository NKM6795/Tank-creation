#include "SpeedometerDraw.h"


SpeedometerDraw::SpeedometerDraw(ComponentParameter *component)
{
	{
		panelTexture = new Texture;
		panelTexture->loadFromFile(component->objectName + component->typeName2);

		panelSprite = new Sprite;
		panelSprite->setTexture(*panelTexture);
		panelSprite->setOrigin(float(component->offsets[0].x), float(component->offsets[0].y));
	}

	{
		leverTexture = new Texture;
		leverTexture->loadFromFile(component->objectName + component->typeName3);

		leverSprite = new Sprite;
		leverSprite->setTexture(*leverTexture);
		leverSprite->setOrigin(float(component->offsets[1].x), float(component->offsets[1].y));
		offset = component->offsets[2];
	}

	numberOfVariant = component->numberOfVariant;

	speedometerTexture = new Texture[numberOfVariant];
	speedometerSprite = new Sprite[numberOfVariant];

	for (int i = 0; i < numberOfVariant; ++i)
	{
		string fileName = component->objectName + component->typeName + component->identifierName + to_string(i + 1) + string(".png");

		speedometerTexture[i].loadFromFile(fileName);

		speedometerSprite[i].setTexture(speedometerTexture[i]);
		speedometerSprite[i].setOrigin(float(component->offsets[3].x), float(component->offsets[3].y));
	}
}

SpeedometerDraw::~SpeedometerDraw()
{
	delete panelTexture;
	delete panelSprite;

	delete leverTexture;
	delete leverSprite;

	delete[] speedometerSprite;
	delete[] speedometerTexture;
}


void SpeedometerDraw::draw(RenderTexture &renderTexture, long timer, ViewableObject *object)
{
	if (object->needDraw)
	{
		panelSprite->setPosition(float(object->getPosition().x), float(object->getPosition().y));

		renderTexture.draw(*panelSprite);

		int index = object->getHealth();

		speedometerSprite[index].setPosition(float(object->getPosition().x), float(object->getPosition().y));
		speedometerSprite[index].setColor(object->needChangeColor ? (object->needChangeColor == 1 ? Color::Green : Color::Red) : Color::White);
		speedometerSprite[index].setScale(object->getScale(), object->getScale());

		renderTexture.draw(speedometerSprite[index]);

		leverSprite->setPosition(float(object->getPosition().x + offset.x), float(object->getPosition().y + offset.y));
		leverSprite->setRotation(object->tiltAngle);

		renderTexture.draw(*leverSprite);
	}
}
