#include "BigBlock.h"


BigBlockComponent::BigBlockComponent(string name, string objectName, string typeName, string identifierName, int numberOfVariant, int healthPoints, bool canRebound) : Component(name, objectName, typeName, identifierName, numberOfVariant, 2, 2)
{
	component->healthPoints = healthPoints;

	component->canRebound = canRebound;
}


BigBlock::BigBlock() : ViewableObject()
{
	addition = new AdditionToBigBlock(this);
}

BigBlock::BigBlock(Component *component) : ViewableObject(component)
{
	addition = new AdditionToBigBlock(this);
}

BigBlock::BigBlock(Component *component, int index) : ViewableObject(component, index)
{
	addition = new AdditionToBigBlock(this);
}

BigBlock::~BigBlock()
{
	delete addition;
}


ViewableObject *BigBlock::getAddition()
{
	return addition;
}


AdditionToBigBlock::AdditionToBigBlock(ViewableObject *main) : main(main)
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
