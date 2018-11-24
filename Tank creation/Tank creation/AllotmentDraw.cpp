#include "AllotmentDraw.h"


AllotmentDraw::AllotmentDraw(ComponentParameter *component)
{
	string fileName = component->objectName + component->typeName + string(".png");

	texture.loadFromFile(fileName);

	sprite.setTexture(texture);
	sprite.setOrigin(float(component->offsets[0].x), float(component->offsets[0].y));
}

AllotmentDraw::~AllotmentDraw()
{

}


void AllotmentDraw::draw(RenderTexture &renderTexture, long timer, ViewableObject *object, int compulsoryDrawing)
{
	if (object->needDraw || compulsoryDrawing)
	{
		sprite.setPosition(float(object->getPosition().x), float(object->getPosition().y));
		sprite.setRotation(object->tiltAngle);

		renderTexture.draw(sprite);
	}
}