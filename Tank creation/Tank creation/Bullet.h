#pragma once


#include "ViewableObject.h"


class BulletComponent : public Component
{

public:
	BulletComponent(string name, string objectName, string typeName, string identifierName, int numberOfVariant, int width, int height);


};


class Bullet : public ViewableObject
{
	Vector2float bulletPosition;
	Vector2float oldBulletPosition;

	ViewableObject *father;

public:
	Bullet();
	Bullet(Component *component);
	Bullet(Component *component, int index);
	Bullet(Component *component, int index, ViewableObject *gun, float angel, float speedOfBullet, Vector2float position, long timer);

	Vector2float getBulletPosition(bool old = false);
	void setBulletPosition(Vector2float position);

	ViewableObject *getFather();
};