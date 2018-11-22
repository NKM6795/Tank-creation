#include "Speedometer.h"


SpeedometerComponent::SpeedometerComponent(string name, string objectName, string typeName, string identifierName, int numberOfVariant, string typeName2, string typeName3, vector<Vector2int> offsets) : Component(name, objectName, typeName, identifierName, numberOfVariant)
{
	component->typeName2 = typeName2;
	component->typeName3 = typeName3;

	component->offsets = offsets;
}


Speedometer::Speedometer() : ViewableObject()
{
	tiltAngle = 0;
}

Speedometer::Speedometer(Component *component) : ViewableObject(component)
{
	tiltAngle = 0;
}

Speedometer::Speedometer(Component *component, int index) : ViewableObject(component, index)
{
	tiltAngle = 0;
}