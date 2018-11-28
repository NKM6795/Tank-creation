#pragma once


#include "ViewableObject.h"


class SmallBlockComponent : public Component
{


public:
	SmallBlockComponent(string name, string objectName, string typeName, string identifierName, int numberOfVariant, int healthPoints, bool canRebound, int cost = 0);


};


class SmallBlock : public ViewableObject
{


public:
	SmallBlock();
	SmallBlock(Component *component);
	SmallBlock(Component *component, int index);


};