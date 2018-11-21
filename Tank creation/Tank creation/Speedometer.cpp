#include "Speedometer.h"


SpeedometerComponent::SpeedometerComponent(string name, string objectName, string typeName, string identifierName, int numberOfVariant, string typeName2, string typeName3, vector<Vector2int> offsets) : Component(name, objectName, typeName, identifierName, numberOfVariant)
{
	component->typeName2 = typeName2;
	component->typeName3 = typeName3;

	component->offsets = offsets;

	component->tiltAngle = 0;
}


Speedometer::Speedometer() : ViewableObject()
{

}

Speedometer::Speedometer(Component *component) : ViewableObject(component)
{

}

Speedometer::Speedometer(Component *component, int index) : ViewableObject(component, index)
{

}