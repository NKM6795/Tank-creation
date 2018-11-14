#include "Background.h"


BackgroundComponent::BackgroundComponent(string name, string objectName, string typeName, string identifierName, int numberOfVariant) : Component(name, objectName, typeName, identifierName, numberOfVariant)
{

}


Background::Background() : Object()
{

}

Background::Background(Component *component) : Object(component)
{

}

Background::Background(Component *component, int index) : Object(component, index)
{

}