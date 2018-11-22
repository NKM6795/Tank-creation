#pragma once


#include "ViewableObject.h"


class BulletComponent : public Component
{

public:
	BulletComponent(string name, string objectName, string typeName, string identifierName, int numberOfVariant, int width, int height);


};


class Bullet : public ViewableObject
{


public:
	Bullet();
	Bullet(Component *component);
	Bullet(Component *component, int index);


};