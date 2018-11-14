#include "List.h"


void List::updateObject()
{
	for (int i = 0; i < int(objects.size()); ++i)
	{
		objects[i]->setPosition((fragmentHeight - objectHeight + objectWidth - objects[i]->getComponentParameter()->width * 20) / 2, i * fragmentHeight + (fragmentHeight - objects[i]->getComponentParameter()->height * 20) / 2 - position);
	}

	button->getStruct()->yCoordinate = int(conversionFactor * position) + 25;
}

List::List(vector<Object *> objects, int width, int height, int xCoordinate, int yCoordinate, int objectWidth, int objectHeight, int fragmentHeight, int separationThickness) : 
	objects(objects), width(width), height(height), xCoordinate(xCoordinate), yCoordinate(yCoordinate), objectWidth(objectWidth), objectHeight(objectHeight), fragmentHeight(fragmentHeight), separationThickness(separationThickness)
{
	position = 0;
	index = 0;

	needDirect = false;
	activateAnAction = false;
	
	needButton = false;
	conversionFactor = 1.f;
	button = nullptr;
	if (int(objects.size()) * fragmentHeight > height)
	{
		needButton = true;

		conversionFactor = float(height) / float(int(objects.size()) * fragmentHeight);

		button = new Button;

		button->setInformation(width - 5, 25, 10, 51, 0, "", "scrollbar", "");
	}

	for (int i = 0; i < int(objects.size()); ++i)
	{
		objects[i]->setPosition((fragmentHeight - objectHeight + objectWidth - objects[i]->getComponentParameter()->width * 20) / 2, i * fragmentHeight + (fragmentHeight - objects[i]->getComponentParameter()->height * 20) / 2);
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


int List::getPosition()
{
	return position;
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


void List::setDirect(bool direct)
{
	needDirect = true;

	up = direct;
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

	if (needDirect)
	{
		if (mousePosition > Vector2int() && mousePosition < Vector2int(width, height))
		{
			if (!up && position + height + fragmentHeight <= int(objects.size()) * fragmentHeight)
			{
				position += fragmentHeight;

				updateObject();
			}
			else if (up && position - fragmentHeight >= 0)
			{
				position -= fragmentHeight;

				updateObject();
			}
		}
		else
		{
			index += up ? -1 : 1;
			index = index < 0 ? 0 : index >= int(objects.size()) ? int(objects.size()) - 1 : index;

			if (index * fragmentHeight < position)
			{
				position = index * fragmentHeight;
			}
			else if ((index + 1) * fragmentHeight > position + height)
			{
				position = (index + 1) * fragmentHeight - height;
			}

			updateObject();
		}
		needDirect = false;
	}
	if (mousePosition > Vector2int() && mousePosition < Vector2int(width, height))
	{
		index = (mousePosition.y + position) / fragmentHeight;

		if (index * fragmentHeight < position)
		{
			position = index * fragmentHeight;
		}
		else if ((index + 1) * fragmentHeight > position + height)
		{
			position = (index + 1) * fragmentHeight - height;
		}

		updateObject();
	}

}


bool List::getActivateAnAction()
{
	return activateAnAction;
}