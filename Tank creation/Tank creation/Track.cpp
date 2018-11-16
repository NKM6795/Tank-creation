#include "Track.h"


TrackComponent::TrackComponent(string name, string objectName, string typeName, string identifierName, int numberOfVariant, int healthPoints, int width, int height) : Component(name, objectName, typeName, identifierName, numberOfVariant, width, height)
{
	component->healthPoints = healthPoints;
}


Track::Track() : ViewableObject()
{
	addition = new AdditionToTrack(this);
}

Track::Track(Component *component) : ViewableObject(component)
{
	addition = new AdditionToTrack(this);
}

Track::Track(Component *component, int index) : ViewableObject(component, index)
{
	addition = new AdditionToTrack(this);
}

Track::~Track()
{
	delete addition;
}


ViewableObject *Track::getAddition()
{
	return addition;
}


AdditionToTrack::AdditionToTrack(ViewableObject *main) : main(main)
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