#include "Bullet.h"


BulletComponent::BulletComponent(string name, string objectName, string typeName, string identifierName, int numberOfVariant, int width, int height) : Component(name, objectName, typeName, identifierName, numberOfVariant)
{
	component->width = width;
	component->height = height;
}


Bullet::Bullet() : ViewableObject()
{

}

Bullet::Bullet(Component *component) : ViewableObject(component)
{

}

Bullet::Bullet(Component *component, int index) : ViewableObject(component, index)
{

}

Bullet::Bullet(Component *component, int index, ViewableObject *gun, float angel, float speedOfBullet, Vector2float position, long timer) : ViewableObject(component, index)
{
	father = gun;
	component->getStruct()->healthPoints = 5;
	healthPoints = 5;

	tiltAngle = angel;
	speed = speedOfBullet;

	bulletPosition = position;
	oldBulletPosition = position;
	setPosition(position);

	timerForObject = timer;
}


Vector2float Bullet::getBulletPosition(bool old)
{
	if (old)
	{
		return oldBulletPosition;
	}
	return bulletPosition;
}

void Bullet::setBulletPosition(Vector2float position)
{
	bulletPosition = position;
}


ViewableObject *Bullet::getFather()
{
	return father;
}
