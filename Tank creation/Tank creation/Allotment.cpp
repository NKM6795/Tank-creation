#include "Allotment.h"


AllotmentComponent::AllotmentComponent(string name, string objectName, string typeName, string identifierName, int numberOfVariant, vector<Vector2int> offsets) : Component(name, objectName, typeName, identifierName, numberOfVariant)
{
	component->offsets = offsets;
}


Allotment::Allotment() : ViewableObject()
{

}

Allotment::Allotment(Component *component) : ViewableObject(component)
{

}

Allotment::Allotment(Component *component, int index) : ViewableObject(component, index)
{

}