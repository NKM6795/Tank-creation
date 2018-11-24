#include "BulletDraw.h"


BulletDraw::BulletDraw(ComponentParameter *component)
{
	numberOfVariant = component->numberOfVariant;

	texture = new Texture[numberOfVariant];
	sprite = new Sprite[numberOfVariant];

	for (int i = 0; i < numberOfVariant; ++i)
	{
		string fileName = component->objectName + component->typeName + component->identifierName + to_string(i + 1) + string(".png");

		texture[i].loadFromFile(fileName);

		sprite[i].setTexture(texture[i]);
		sprite[i].setOrigin(float(component->width / 2), float(component->height / 2));
	}
}

BulletDraw::~BulletDraw()
{
	delete[] sprite;

	delete[] texture;
}


void BulletDraw::draw(RenderTexture &renderTexture, long timer, ViewableObject *object, int compulsoryDrawing)
{
	if (object->needDraw || compulsoryDrawing)
	{
		int index = int((timer / 100) % numberOfVariant);

		sprite[index].setPosition(float(object->getPosition().x), float(object->getPosition().y));
		sprite[index].setColor(object->needChangeColor ? Color(0, 255, 0) : Color::White);
		sprite[index].setScale(object->getScale(), object->getScale());

		renderTexture.draw(sprite[index]);
	}
}
