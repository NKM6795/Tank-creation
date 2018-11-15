#pragma once


#include "Object.h"


class TankPictureComponent : public Component
{

public:
	TankPictureComponent(string name, string objectName, string typeName, string identifierName, int numberOfVariant);


};


class TankPicture : public Object
{


public:
	TankPicture();
	TankPicture(Component *component);
	TankPicture(Component *component, int index);


};