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