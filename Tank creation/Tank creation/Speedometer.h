#pragma once


#include "ViewableObject.h"


class SpeedometerComponent : public Component
{


public:
	SpeedometerComponent(string name, string objectName, string typeName, string identifierName, int numberOfVariant, string typeName2, string typeName3, vector<Vector2int> offsets);


};


class Speedometer : public ViewableObject
{


public:
	Speedometer();
	Speedometer(Component *component);
	Speedometer(Component *component, int index);


};