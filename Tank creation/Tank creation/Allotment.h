#pragma once


#include "ViewableObject.h"


class AllotmentComponent : public Component
{

public:
	AllotmentComponent(string name, string objectName, string typeName, string identifierName, int numberOfVariant, vector<Vector2int> offsets);


};


class Allotment : public ViewableObject
{


public:
	Allotment();
	Allotment(Component *component);
	Allotment(Component *component, int index);


};