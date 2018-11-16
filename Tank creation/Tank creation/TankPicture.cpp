#include "TankPicture.h"


TankPictureComponent::TankPictureComponent(string name, string objectName, string typeName, string identifierName, int numberOfVariant) : Component(name, objectName, typeName, identifierName, numberOfVariant)
{

}


TankPicture::TankPicture() : ViewableObject()
{

}

TankPicture::TankPicture(Component *component) : ViewableObject(component)
{

}

TankPicture::TankPicture(Component *component, int index) : ViewableObject(component, index)
{

}