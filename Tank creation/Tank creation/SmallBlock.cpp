#include "SmallBlock.h"


SmallBlockComponent::SmallBlockComponent(string objectName, string typeName, string identifierName, int numberOfVariant, int healthPoints, bool canRebound) : Component(objectName, typeName, identifierName, numberOfVariant)
{
	component->healthPoints = healthPoints;

	component->canRebound = canRebound;
}


SmallBlock::SmallBlock() : Object()
{

}

SmallBlock::SmallBlock(Component *component) : Object(component)
{

}

SmallBlock::SmallBlock(Component *component, int index) : Object(component, index)
{

}