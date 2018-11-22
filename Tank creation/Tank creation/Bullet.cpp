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