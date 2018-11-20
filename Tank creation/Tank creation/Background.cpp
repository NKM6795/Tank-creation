#include "Background.h"


BackgroundComponent::BackgroundComponent(string name, string objectName, string typeName, string identifierName, int numberOfVariant) : Component(name, objectName, typeName, identifierName, numberOfVariant)
{

}


Background::Background() : ViewableObject()
{

}

Background::Background(Component *component) : ViewableObject(component)
{

}

Background::Background(Component *component, int index) : ViewableObject(component, index)
{

}


BackgroundForBattleComponent::BackgroundForBattleComponent(string name, string objectName, string typeName, string identifierName, int numberOfVariant, vector<Vector2int> dimensions, vector<Vector2int> offsets) : Component(name, objectName, typeName, identifierName, numberOfVariant)
{
	component->dimensions = dimensions;
	component->offsets = offsets;
}


BackgroundForBattle::BackgroundForBattle() : ViewableObject()
{

}

BackgroundForBattle::BackgroundForBattle(Component *component) : ViewableObject(component)
{

}

BackgroundForBattle::BackgroundForBattle(Component *component, int index) : ViewableObject(component, index)
{

}