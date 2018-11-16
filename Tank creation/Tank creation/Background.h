#pragma once


#include "ViewableObject.h"


class BackgroundComponent : public Component
{

public:
	BackgroundComponent(string name, string objectName, string typeName, string identifierName, int numberOfVariant);


};


class Background : public ViewableObject
{


public:
	Background();
	Background(Component *component);
	Background(Component *component, int index);


};