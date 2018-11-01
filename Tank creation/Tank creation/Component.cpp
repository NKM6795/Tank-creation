#include "Component.h"


Component::Component(string objectName, string typeName, string identifierName, int numberOfVariant)
{
	component.objectName = objectName;
	component.typeName = typeName;
	component.identifierName = identifierName;
	component.numberOfVariant = numberOfVariant;
}


ComponentParameter *Component::getStruct()
{
	return &component;
}