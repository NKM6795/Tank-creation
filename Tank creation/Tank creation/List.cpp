#include "List.h"


void List::updateObject()
{
	for (int i = 0; i < int(objects.size()); ++i)
	{
		objects[i]->setPosition((fragmentHeight - objectHeight + objectWidth - int(objects[i]->getScale() * objects[i]->getComponentParameter()->width * 20)) / 2, i * fragmentHeight + (fragmentHeight - int(objects[i]->getScale() * objects[i]->getComponentParameter()->height * 20)) / 2 - position);
	}

	button->getStruct()->yCoordinate = int(conversionFactor * position) + 25;
}


List::List(vector<Object *> objects, int width, int height, int xCoordinate, int yCoordinate, int objectWidth, int objectHeight, int fragmentHeight, int separationThickness) : 
	objects(objects), width(width), height(height), xCoordinate(xCoordinate), yCoordinate(yCoordinate), objectWidth(objectWidth), objectHeight(objectHeight), fragmentHeight(fragmentHeight), separationThickness(separationThickness)
{
	open = false;

	position = 0;
	index = 0;

	needDirect = false;
	deltaPosition = -1;
	
	needInformation = false;

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
		if (objects[i]->getComponentParameter()->width > 3 || objects[i]->getComponentParameter()->height > 2)
		{
			objects[i]->setScale(min(3.f / float(objects[i]->getComponentParameter()->width), 2.f / float(objects[i]->getComponentParameter()->height)));
		}
		objects[i]->setPosition((fragmentHeight - objectHeight + objectWidth - int(objects[i]->getScale() * objects[i]->getComponentParameter()->width * 20)) / 2, i * fragmentHeight + (fragmentHeight - int(objects[i]->getScale() * objects[i]->getComponentParameter()->height * 20)) / 2);
	}

	fileName = "Data/Fonts/Strangiato.otf";
}


List::~List()
{
	if (needButton)
	{
		delete button;
	}
}


bool List::isOpen()
{
	return open;
}

void List::openList(Vector2int mousePosition)
{
	open = true;

	xCoordinate = mousePosition.x - ((mousePosition.x - width) > 0 ? width : 0);
	yCoordinate = mousePosition.y - ((mousePosition.y - height) > 0 ? height : 0);
}

void List::closeList()
{
	open = false;
}


bool List::inFocuse(Vector2int mousePosition)
{
	return mousePosition >= Vector2int(xCoordinate - 3, yCoordinate - 3) && mousePosition <= Vector2int(xCoordinate + width + 3, yCoordinate + height + 3);
}


string List::getFileName()
{
	return fileName;
}

void List::setFileName(string name)
{
	fileName = name;
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


vector<Object *> List::getSelectedObject()
{
	vector<Object *> result;

	Object *newObject = TankEditor::getCopy(objects[index]);
	newObject->setHeath(newObject->getComponentParameter()->healthPoints);

	result.push_back(newObject);

	return result;
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


int List::getObjectWidth()
{
	return objectWidth;
}

int List::getObjectHeight()
{
	return objectHeight;
}


bool List::getNeedInformation()
{
	return needInformation;
}


void List::work(Vector2int mousePosition, bool isPressed, long timer, int fps)
{
	mousePosition = mousePosition - getOffset();

	if (needButton)
	{
		button->work(mousePosition * (open ? 1 : -100), isPressed && open, timer, fps);
	}

	if (!open)
	{
		timerForInformation = timer;
	}
	else
	{
		if (button->getStruct()->checkButtonIsPressed)
		{
			timerForInformation = timer;
			oldMousePosition = mousePosition;

			if (deltaPosition == -1)
			{
				deltaPosition = mousePosition.y - int(conversionFactor * position);
			}

			int positionForButton = mousePosition.y - deltaPosition;

			position = int(float(positionForButton) / conversionFactor);

			if (position < 0)
			{
				position = 0;
			}
			else if (position + height > int(objects.size()) * fragmentHeight)
			{
				position = int(objects.size()) * fragmentHeight - height;
			}

			updateObject();
		}
		else
		{
			deltaPosition = -1;
		}

		if (needDirect)
		{
			timerForInformation = timer;
			oldMousePosition = mousePosition;

			if (mousePosition > Vector2int() && mousePosition < Vector2int(width - (needButton ? 11 : 0), height))
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
		if (mousePosition > Vector2int() && mousePosition < Vector2int(width - (needButton ? 11 : 0), height))
		{
			index = (mousePosition.y + position) / fragmentHeight;

			if (mousePosition != oldMousePosition)
			{
				timerForInformation = timer;
				oldMousePosition = mousePosition;
			}

			if (index * fragmentHeight < position)
			{
				position = index * fragmentHeight;
			}
			else if ((index + 1) * fragmentHeight > position + height)
			{
				position = (index + 1) * fragmentHeight - height;
			}

			updateObject();

			if (isPressed)
			{
				closeList();
			}
		}

		if (timer - timerForInformation >= 500)
		{
			needInformation = true;
		}
		else
		{
			needInformation = false;
		}
	}
}