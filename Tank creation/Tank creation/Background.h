#pragma once


#include "Object.h"


class BackgroundComponent : public Component
{

public:
	BackgroundComponent(string objectName, string typeName, string identifierName, int numberOfVariant);


};


class Background : public Object
{


public:
	Background();
	Background(Component *component);
	Background(Component *component, int index);


};