#include "List.h"


void List::updateViewableObject()
{
	for (int i = 0; i < int(objects.size()); ++i)
	{
		objects[i]->setPosition((fragmentHeight - objectHeight + objectWidth - int(objects[i]->getScale() * objects[i]->getComponentParameter()->width * 20)) / 2, i * fragmentHeight + (fragmentHeight - int(objects[i]->getScale() * objects[i]->getComponentParameter()->height * 20)) / 2 - position);
	}

	if (needButton)
	{
		button->getStruct()->yCoordinate = int(conversionFactor * position) + 25;
	}
}


List::List(vector<ViewableObject *> objects, int width, int height, int xCoordinate, int yCoordinate, int objectWidth, int objectHeight, int fragmentHeight, int separationThickness) : 
	objects(objects), width(width), height(height), xCoordinate(xCoordinate), yCoordinate(yCoordinate), objectWidth(objectWidth), objectHeight(objectHeight), fragmentHeight(fragmentHeight), separationThickness(separationThickness)
{
	open = false;

	needClose = false;
	needSelect = false;

	timerForDoubleClick = 0;
	firstClick = false;

	position = 0;
	index = 0;
	indexOfSelectedObject = 0;

	if (objects.size() == 0)
	{
		index = -1;
		indexOfSelectedObject = -1;
	}

	needDirect = false;
	deltaPosition = -1;
	
	needInformation = false;

	mouseButtonIsPressed = false;

	needButton = false;
	conversionFactor = 1.f;
	button = nullptr;
	if (int(objects.size()) * fragmentHeight > height)
	{
		needButton = true;

		conversionFactor = float(height - 51) / float(int(objects.size()) * fragmentHeight - height);

		button = new Button;

		button->setInformation(width - 5, 25, 10, 51, 0, "", "scrollbar", "");
	}

	for (int i = 0; i < int(objects.size()); ++i)
	{
		if (objects[i]->getComponentParameter()->width == 30)
		{
			objects[i]->setScale(0.166666666667f);
		}
		else if (objects[i]->getComponentParameter()->width > 3 || objects[i]->getComponentParameter()->height > 2)
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

	while (objects.size() > 0)
	{
		delete objects.back();
		objects.pop_back();
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


void List::setNeedClose()
{
	needClose = true;
}


bool List::inFocuse(Vector2int mousePosition)
{
	return open && ((mousePosition >= Vector2int(xCoordinate - 3, yCoordinate - 3) && mousePosition <= Vector2int(xCoordinate + width + 3, yCoordinate + height + 3)) || (needButton && button->getStruct()->checkButtonIsPressed));
}


bool List::canAddElement(bool isPressed)
{
	if (isPressed && mouseButtonIsPressed)
	{
		return false;
	}
	else
	{
		mouseButtonIsPressed = false;
		return true;
	}
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

int List::getIndexOfSelectedObject()
{
	return indexOfSelectedObject;
}


int List::getPosition()
{
	return position;
}


Button *List::getButton()
{
	return button;
}


vector<ViewableObject *> &List::getViewableObjects()
{
	return objects;
}


vector<ViewableObject *> List::getHighlightedViewableObject()
{
	vector<ViewableObject *> result;

	if (index == -1)
	{
		return result;
	}

	ViewableObject *newViewableObject = TankEditor::getCopy(objects[index]);
	newViewableObject->setHeath(newViewableObject->getComponentParameter()->healthPoints);

	result.push_back(newViewableObject);

	return result;
}

vector<ViewableObject *> List::getSelectedViewableObject()
{
	vector<ViewableObject *> result;

	if (indexOfSelectedObject == -1)
	{
		return result;
	}

	ViewableObject *newViewableObject = TankEditor::getCopy(objects[indexOfSelectedObject]);
	newViewableObject->setHeath(newViewableObject->getComponentParameter()->healthPoints);

	result.push_back(newViewableObject);

	return result;
}


void List::copyViewableObject(ViewableObject *object)
{
	if (object == nullptr)
	{
		return;
	}

	for (int i = 0; i < int(objects.size()); ++i)
	{
		if (objects[i]->getIndex() == object->getIndex())
		{
			indexOfSelectedObject = i;
			index = i;
			return;
		}
	}
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

void List::select()
{
	needSelect = true;
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


int List::getViewableObjectWidth()
{
	return objectWidth;
}

int List::getViewableObjectHeight()
{
	return objectHeight;
}


bool List::getNeedInformation()
{
	return needInformation;
}


void List::work(Vector2int mousePosition, bool isPressed, long timer, int fps, bool rightIsPressed)
{
	if (!isPressed && mouseButtonIsPressed)
	{
		mouseButtonIsPressed = false;
		if (!firstClick)
		{
			firstClick = true;
			timerForDoubleClick = timer;
		}
		else if (timer - timerForDoubleClick < 300)
		{
			if (needClose)
			{
				closeList();
			}

			indexOfSelectedObject = index;

			firstClick = false;
		}
		else
		{
			firstClick = false;
		}
	}

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
		if (needSelect)
		{
			needSelect = false;

			indexOfSelectedObject = index;
		}


		if (needButton && button->getStruct()->checkButtonIsPressed)
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

			updateViewableObject();
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

					updateViewableObject();
				}
				else if (up && position - fragmentHeight >= 0)
				{
					position -= fragmentHeight;

					updateViewableObject();
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

				updateViewableObject();
			}
			needDirect = false;
		}
		if (index != -1 && mousePosition > Vector2int() && mousePosition < Vector2int(width - (needButton ? 11 : 0), height))
		{
			index = (mousePosition.y + position) / fragmentHeight;
			index = index < 0 ? 0 : index >= int(objects.size()) ? int(objects.size()) - 1 : index;


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

			updateViewableObject();

			if (isPressed && (!needButton || (needButton && !button->getStruct()->checkButtonIsPressed)))
			{
				indexOfSelectedObject = index;

				mouseButtonIsPressed = true;
			}
		}

		if (index != -1 && (timer - timerForInformation >= 500 || rightIsPressed))
		{
			timerForInformation = timer - 500;
			needInformation = true;
		}
		else
		{
			needInformation = false;
		}
	}
}