#include "Track.h"


TrackComponent::TrackComponent(string objectName, string typeName, string identifierName, int numberOfVariant, int healthPoints) : Component(objectName, typeName, identifierName, numberOfVariant)
{
	component->healthPoints = healthPoints;
}


Track::Track() : Object()
{
	additions = new Object*[3];

	for (int i = 0; i < 3; ++i)
	{
		additions[i] = new AdditionToTrack(this);
	}
}

Track::Track(Component *component) : Object(component)
{
	additions = new Object*[3];

	for (int i = 0; i < 3; ++i)
	{
		additions[i] = new AdditionToTrack(this);
	}
}

Track::Track(Component *component, int index) : Object(component, index)
{
	additions = new Object*[3];

	for (int i = 0; i < 3; ++i)
	{
		additions[i] = new AdditionToTrack(this);
	}
}

Track::~Track()
{
	for (int i = 0; i < 3; ++i)
	{
		delete additions[i];
	}

	delete[] additions;
}


AdditionToTrack::AdditionToTrack(Object *main) : main(main)
{

}


Vector2int AdditionToTrack::getPosition()
{
	return main->getPosition();
}

void AdditionToTrack::setPosition(Vector2int position)
{
	return main->setPosition(position);
}

void AdditionToTrack::setPosition(int x, int y)
{
	return main->setPosition(x, y);
}


int AdditionToTrack::getHealth()
{
	return main->getHealth();
}

void AdditionToTrack::setHeath(int health)
{
	return main->setHeath(health);
}


int AdditionToTrack::getIndex()
{
	return main->getIndex();
}

void AdditionToTrack::setIndex(int i)
{
	return main->setIndex(i);
}


ComponentParameter *AdditionToTrack::getComponentParameter()
{
	return main->getComponentParameter();
}