#pragma once


#include "Object.h"


class SmallBlockComponent : public Component
{


public:
	SmallBlockComponent(string objectName, string typeName, string identifierName, int numberOfVariant, int healthPoints, bool canRebound);


};


class SmallBlock : public Object
{


public:
	SmallBlock();
	SmallBlock(Component *component);
	SmallBlock(Component *component, int index);


};