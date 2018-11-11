#include "EngineRoom.h"


EngineRoomComponent::EngineRoomComponent(string objectName, string typeName, string identifierName, int numberOfVariant, int healthPoints) : Component(objectName, typeName, identifierName, numberOfVariant)
{
	component->healthPoints = healthPoints;
}


EngineRoom::EngineRoom() : Object()
{
	additions = new Object*[5];

	for (int i = 0; i < 5; ++i)
	{
		additions[i] = new AdditionToEngineRoom(this);
	}
}

EngineRoom::EngineRoom(Component *component) : Object(component)
{
	additions = new Object*[5];

	for (int i = 0; i < 5; ++i)
	{
		additions[i] = new AdditionToEngineRoom(this);
	}
}

EngineRoom::EngineRoom(Component *component, int index) : Object(component, index)
{
	additions = new Object*[5];

	for (int i = 0; i < 5; ++i)
	{
		additions[i] = new AdditionToEngineRoom(this);
	}
}


AdditionToEngineRoom::AdditionToEngineRoom(Object *main) : main(main)
{

}


Vector2int AdditionToEngineRoom::getPosition()
{
	return main->getPosition();
}

void AdditionToEngineRoom::setPosition(Vector2int position)
{
	return main->setPosition(position);
}

void AdditionToEngineRoom::setPosition(int x, int y)
{
	return main->setPosition(x, y);
}


int AdditionToEngineRoom::getHealth()
{
	return main->getHealth();
}

void AdditionToEngineRoom::setHeath(int health)
{
	return main->setHeath(health);
}


int AdditionToEngineRoom::getIndex()
{
	return main->getIndex();
}

void AdditionToEngineRoom::setIndex(int i)
{
	return main->setIndex(i);
}


ComponentParameter *AdditionToEngineRoom::getComponentParameter()
{
	return main->getComponentParameter();
}