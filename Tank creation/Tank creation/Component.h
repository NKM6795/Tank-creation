#pragma once


#include "BaseElement.h"


struct ComponentParameter
{
	string objectName;
	string typeName;
	string identifierName;
	int numberOfVariant;
};


class Component
{
	ComponentParameter *component;

public:
	Component(string objectName, string typeName, string identifierName, int numberOfVariant);

	virtual ~Component();

	ComponentParameter *getStruct();
};