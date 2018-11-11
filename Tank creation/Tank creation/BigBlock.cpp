#include "BigBlock.h"


BigBlockComponent::BigBlockComponent(string objectName, string typeName, string identifierName, int numberOfVariant, int healthPoints, bool canRebound) : Component(objectName, typeName, identifierName, numberOfVariant)
{
	component->healthPoints = healthPoints;

	component->canRebound = canRebound;
}


BigBlock::BigBlock() : Object()
{
	additions = new Object*[3];

	for (int i = 0; i < 3; ++i)
	{
		additions[i] = new AdditionToBigBlock(this);
	}
}

BigBlock::BigBlock(Component *component) : Object(component)
{
	additions = new Object*[3];

	for (int i = 0; i < 3; ++i)
	{
		additions[i] = new AdditionToBigBlock(this);
	}
}

BigBlock::BigBlock(Component *component, int index) : Object(component, index)
{
	additions = new Object*[3];

	for (int i = 0; i < 3; ++i)
	{
		additions[i] = new AdditionToBigBlock(this);
	}
}


AdditionToBigBlock::AdditionToBigBlock(Object *main) : main(main)
{

}


Vector2int AdditionToBigBlock::getPosition()
{
	return main->getPosition();
}

void AdditionToBigBlock::setPosition(Vector2int position)
{
	return main->setPosition(position);
}

void AdditionToBigBlock::setPosition(int x, int y)
{
	return main->setPosition(x, y);
}


int AdditionToBigBlock::getHealth()
{
	return main->getHealth();
}

void AdditionToBigBlock::setHeath(int health)
{
	return main->setHeath(health);
}


int AdditionToBigBlock::getIndex()
{
	return main->getIndex();
}

void AdditionToBigBlock::setIndex(int i)
{
	return main->setIndex(i);
}


ComponentParameter *AdditionToBigBlock::getComponentParameter()
{
	return main->getComponentParameter();
}