#include "SmallBlock.h"


SmallBlockComponent::SmallBlockComponent(string name, string objectName, string typeName, string identifierName, int numberOfVariant, int healthPoints, bool canRebound) : Component(name, objectName, typeName, identifierName, numberOfVariant)
{
	component->healthPoints = healthPoints;

	component->canRebound = canRebound;
}


SmallBlock::SmallBlock() : ViewableObject()
{

}

SmallBlock::SmallBlock(Component *component) : ViewableObject(component)
{

}

SmallBlock::SmallBlock(Component *component, int index) : ViewableObject(component, index)
{

}