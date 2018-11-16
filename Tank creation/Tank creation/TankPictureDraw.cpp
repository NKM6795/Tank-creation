#include "TankPictureDraw.h"


TankPictureDraw::TankPictureDraw(ComponentParameter *component)
{
	texture.loadFromFile(component->objectName + component->typeName + "/" + component->name + string(".png"));

	sprite.setTexture(texture);
}

TankPictureDraw::~TankPictureDraw()
{

}


void TankPictureDraw::draw(RenderTexture &renderTexture, long timer, ViewableObject *object)
{
	if (object->needDraw)
	{
		sprite.setPosition(float(object->getPosition().x), float(object->getPosition().y));
		sprite.setColor(object->needChangeColor ? Color(0, 255, 0) : Color::White);
		sprite.setScale(object->getScale(), object->getScale());

		renderTexture.draw(sprite);
	}
}
