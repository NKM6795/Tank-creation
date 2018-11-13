#include "Gun.h"


GunComponent::GunComponent(string objectName, string typeName, string identifierName, int numberOfVariant, string typeName2, string identifierName2, int numberOfVariant2,
	bool horizontally, int damage, int bulletSpeed, int reload, int xOffsetForBarrel, int yOffsetForBarrel, int xOriginForBarrel, int yOriginForBarrel, int healthPoints, int backgroundIndex, int width, int height) :
	Component(objectName, typeName, identifierName, numberOfVariant, width, height)
{
	component->typeName2 = typeName2;
	component->identifierName2 = identifierName2;
	component->numberOfVariant2 = numberOfVariant2;

	component->horizontally = horizontally;
	component->damage = damage;
	component->bulletSpeed = bulletSpeed;
	component->reload = reload;
	component->xOffsetForBarrel = xOffsetForBarrel;
	component->yOffsetForBarrel = yOffsetForBarrel;
	component->xOriginForBarrel = xOriginForBarrel;
	component->yOriginForBarrel = yOriginForBarrel;

	component->tiltAngle = horizontally ? 90.f : 0;

	component->healthPoints = healthPoints;

	component->backgroundIndex = backgroundIndex;
}


Gun::Gun() : Object()
{
	additions = new Object*[3];

	for (int i = 0; i < 3; ++i)
	{
		additions[i] = new AdditionToGun(this);
	}
}

Gun::Gun(Component *component) : Object(component)
{
	additions = new Object*[3];

	for (int i = 0; i < 3; ++i)
	{
		additions[i] = new AdditionToGun(this);
	}
}

Gun::Gun(Component *component, int index) : Object(component, index)
{
	additions = new Object*[3];

	for (int i = 0; i < 3; ++i)
	{
		additions[i] = new AdditionToGun(this);
	}
}

Gun::~Gun()
{
	for (int i = 0; i < 3; ++i)
	{
		delete additions[i];
	}

	delete[] additions;
}


AdditionToGun::AdditionToGun(Object *main) : main(main)
{

}


Vector2int AdditionToGun::getPosition()
{
	return main->getPosition();
}

void AdditionToGun::setPosition(Vector2int position)
{
	return main->setPosition(position);
}

void AdditionToGun::setPosition(int x, int y)
{
	return main->setPosition(x, y);
}


int AdditionToGun::getHealth()
{
	return main->getHealth();
}

void AdditionToGun::setHeath(int health)
{
	return main->setHeath(health);
}


int AdditionToGun::getIndex()
{
	return main->getIndex();
}

void AdditionToGun::setIndex(int i)
{
	return main->setIndex(i);
}


ComponentParameter *AdditionToGun::getComponentParameter()
{
	return main->getComponentParameter();
}