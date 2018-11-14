#include "EngineRoom.h"


EngineRoomComponent::EngineRoomComponent(string name, string objectName, string typeName, string identifierName, int numberOfVariant, string typeName2, string identifierName2, int numberOfVariant2,
	string typeName3, string identifierName3, int numberOfVariant3, int healthPoints, int xOffsetForRoom, int yOffsetForRoom, int xOffsetForPerson, int yOffsetForPerson, int width, int height) :
	Component(name, objectName, typeName, identifierName, numberOfVariant, width, height)
{
	component->typeName2 = typeName2;
	component->identifierName2 = identifierName2;
	component->numberOfVariant2 = numberOfVariant2;

	component->typeName3 = typeName3;
	component->identifierName3 = identifierName3;
	component->numberOfVariant3 = numberOfVariant3;

	component->healthPoints = healthPoints;

	component->xOffsetForRoom = xOffsetForRoom;
	component->yOffsetForRoom = yOffsetForRoom;

	component->xOffsetForPerson = xOffsetForPerson;
	component->yOffsetForPerson = yOffsetForPerson;
}


EngineRoom::EngineRoom() : Object()
{
	addition = new AdditionToEngineRoom(this);
}

EngineRoom::EngineRoom(Component *component) : Object(component)
{
	addition= new AdditionToEngineRoom(this);
}

EngineRoom::EngineRoom(Component *component, int index) : Object(component, index)
{
	addition= new AdditionToEngineRoom(this);
}

EngineRoom::~EngineRoom()
{
	delete addition;
}


Object *EngineRoom::getAddition()
{
	return addition;
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