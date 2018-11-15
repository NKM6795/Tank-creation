#include "TankPicture.h"


TankPictureComponent::TankPictureComponent(string name, string objectName, string typeName, string identifierName, int numberOfVariant) : Component(name, objectName, typeName, identifierName, numberOfVariant)
{

}


TankPicture::TankPicture() : Object()
{

}

TankPicture::TankPicture(Component *component) : Object(component)
{

}

TankPicture::TankPicture(Component *component, int index) : Object(component, index)
{

}