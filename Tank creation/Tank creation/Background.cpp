#include "Background.h"


BackgroundComponent::BackgroundComponent(string objectName, string typeName, string identifierName, int numberOfVariant) : Component(objectName, typeName, identifierName, numberOfVariant)
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