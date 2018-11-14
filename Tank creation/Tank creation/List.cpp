#include "List.h"


List::List(vector<Object *> objects, int width, int height, int xCoordinate, int yCoordinate, int objectWidth, int objectHeight, int fragmentHeight, int separationThickness) : 
	objects(objects), width(width), height(height), xCoordinate(xCoordinate), yCoordinate(yCoordinate), objectWidth(objectWidth), objectHeight(objectHeight), fragmentHeight(fragmentHeight), separationThickness(separationThickness)
{
	position = 0;
	index = 0;

	activateAnAction = false;
	
	needButton = false;
	conversionFactor = 1.f;
	button = nullptr;
	if (int(objects.size()) * fragmentHeight > height)
	{
		needButton = true;

		conversionFactor = float(int(objects.size()) * fragmentHeight) / float(height);

		button = new Button;

		button->setInformation(width - 11, position, 11, 9, 0, "", "scrollbar", "");
	}

	for (int i = 0; i < int(objects.size()); ++i)
	{
		objects[i]->setPosition((fragmentHeight - objectHeight + objectWidth) / 2, i * fragmentHeight + (fragmentHeight - objectHeight) / 2);
	}
}


List::~List()
{
	if (needButton)
	{
		delete button;
	}
}


int List::getIndex()
{
	return index;
}


Button *List::getButton()
{
	return button;
}


vector<Object *> &List::getObjects()
{
	return objects;
}


Vector2int List::getOffset()
{
	return Vector2int(xCoordinate, yCoordinate);
}

void List::setOffset(Vector2int offset)
{
	xCoordinate = offset.x;
	yCoordinate = offset.y;
}

void List::setOffset(int x, int y)
{
	xCoordinate = x;
	yCoordinate = y;
}


int List::getFragmentHeight()
{
	return fragmentHeight;
}


int List::getWidth()
{
	return width;
}

int List::getHeight()
{
	return height;
}


void List::work(Vector2int mousePosition, bool isPressed, long timer, int fps)
{
	mousePosition = mousePosition - getOffset();

	if (needButton)
	{
		button->work(mousePosition, isPressed, timer, fps);
	}

	

}


bool List::getActivateAnAction()
{
	return activateAnAction;
}