#include "Component.h"


Component::Component(string objectName, string typeName, string identifierName, int numberOfVariant)
{
	component = new ComponentParameter;

	component->objectName = objectName;
	component->typeName = typeName;
	component->identifierName = identifierName;
	component->numberOfVariant = numberOfVariant;
}

Component::~Component()
{
	delete component;
}


ComponentParameter *Component::getStruct()
{
	return component;
}