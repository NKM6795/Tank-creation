#include "GunDraw.h"


GunDraw::GunDraw(ComponentParameter *component, ComponentDraw *background) : background(background)
{
	xOffsetForBarrel = component->xOffsetForBarrel;
	yOffsetForBarrel = component->yOffsetForBarrel;
	xOriginForBarrel = component->xOriginForBarrel;
	yOriginForBarrel = component->yOriginForBarrel;

	numberOfVariantbarrel = component->numberOfVariant;

	barrelTexture = new Texture[numberOfVariantbarrel];
	barrelSprite = new Sprite[numberOfVariantbarrel];

	for (int i = 0; i < numberOfVariantbarrel; ++i)
	{
		string fileName = component->objectName + component->typeName + component->identifierName + to_string(i + 1) + string(".png");

		barrelTexture[i].loadFromFile(fileName);

		barrelSprite[i].setTexture(barrelTexture[i]);

		barrelSprite[i].setOrigin(float(xOriginForBarrel), float(yOriginForBarrel));
	}

	numberOfVarianthandhold = component->numberOfVariant2;

	handholdTexture = new Texture[numberOfVarianthandhold];
	handholdSprite = new Sprite[numberOfVarianthandhold];

	for (int i = 0; i < numberOfVarianthandhold; ++i)
	{
		string fileName = component->objectName + component->typeName2 + component->identifierName2 + to_string(i + 1) + string(".png");

		handholdTexture[i].loadFromFile(fileName);

		handholdSprite[i].setTexture(handholdTexture[i]);
	}
}

GunDraw::~GunDraw()
{
	delete[] barrelTexture;

	delete[] barrelSprite;

	delete[] handholdTexture;

	delete[] handholdSprite;
}


void GunDraw::draw(RenderTexture &renderTexture, long timer, ViewableObject *object, int compulsoryDrawing)
{
	if (((compulsoryDrawing == 1 && !object->needDrawSeparately) || (compulsoryDrawing == -1 && object->needDrawSeparately) || (!compulsoryDrawing && object->needDraw && !object->needDrawSeparately)) && object->getHealth() > 0 && object->getHealth() <= object->getComponentParameter()->healthPoints)
	{
		if (background != nullptr)
		{
			background->draw(renderTexture, timer, object);
		}
		
		if (numberOfVariantbarrel <= 1 && compulsoryDrawing == 1)
		{
			object->needDraw = false;
		}
		
		int index;
		
		if (numberOfVariantbarrel != 0)
		{
			index = int((timer / 100) % numberOfVariantbarrel);

			barrelSprite[index].setPosition(float(object->getPosition().x + xOffsetForBarrel * object->getScale()), float(object->getPosition().y + yOffsetForBarrel * object->getScale()));
			barrelSprite[index].setRotation(object->tiltAngle);
			barrelSprite[index].setColor(object->needChangeColor ? (object->needChangeColor == 1 ? Color::Green : Color::Red) : Color::White);
			barrelSprite[index].setScale(object->getScale(), object->getScale());

			renderTexture.draw(barrelSprite[index]);
		}


		index = 3 - (4 * object->getHealth() - 1) / object->getComponentParameter()->healthPoints;

		handholdSprite[index].setPosition(float(object->getPosition().x), float(object->getPosition().y));
		handholdSprite[index].setColor(object->needChangeColor ? (object->needChangeColor == 1 ? Color::Green : Color::Red) : Color::White);
		handholdSprite[index].setScale(object->getScale(), object->getScale());

		renderTexture.draw(handholdSprite[index]);
	}
}
