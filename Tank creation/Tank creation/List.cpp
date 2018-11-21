#include "List.h"


void List::updateViewableObject()
{
	for (int i = 0; i < int(objects.size()); ++i)
	{
		objects[i]->setPosition((fragmentHeight - objectHeight + objectWidth - int(objects[i]->getScale() * objects[i]->getComponentParameter()->width * 20)) / 2, i * fragmentHeight + (fragmentHeight - int(objects[i]->getScale() * objects[i]->getComponentParameter()->height * 20)) / 2 - position + searchEngineHeight);

		if (objects[i]->getPosition().y + objects[i]->getComponentParameter()->height * 20 < searchEngineHeight || objects[i]->getPosition().y > getHeight())
		{
			objects[i]->needDraw = false;
		}
		else
		{
			objects[i]->needDraw = true;
		}
	}

	if (needButton)
	{
		button->getStruct()->yCoordinate = int(conversionFactor * position) + 25 + searchEngineHeight;
	}
}


List::List(vector<ViewableObject *> objects, int width, int height, int xCoordinate, int yCoordinate, int objectWidth, int objectHeight, int fragmentHeight, int separationThickness) : 
	mainObjects(objects), objects(objects), width(width), height(height), xCoordinate(xCoordinate), yCoordinate(yCoordinate), objectWidth(objectWidth), objectHeight(objectHeight), fragmentHeight(fragmentHeight), separationThickness(separationThickness)
{
	//Open and close list
	open = false;
	needClose = false;

	//Indexes and position
	position = 0;
	searchEngineHeight = fragmentHeight / 2;
	this->height -= searchEngineHeight;
	index = 0;
	indexOfSelectedObject = 0;
	mainIndex = 0;
	mainIndexOfSelectedObject = 0;
	if (objects.size() == 0)
	{
		index = -1;
		indexOfSelectedObject = -1;
		mainIndex = -1;
		mainIndexOfSelectedObject = -1;
	}
	needDirect = false;
	deltaPosition = -1;
	needSelect = false;
	
	//Information
	needInformation = false;

	//Mouse
	mouseButtonIsPressed = false;
	timerForDoubleClick = 0;
	firstClick = false;

	//Scrollbar
	needButton = false;
	conversionFactor = 1.f;
	button = nullptr;
	if (int(objects.size()) * fragmentHeight > this->height)
	{
		needButton = true;

		conversionFactor = float(this->height - 51) / float(int(objects.size()) * fragmentHeight - this->height);

		button = new Button;

		button->setInformation(width - 5, 25 + searchEngineHeight, 10, 51, 0, "", "scrollbar", "");
	}

	//Objects
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
	}
	updateViewableObject();
	fileName = "Data/Fonts/Strangiato.otf";

	//Filter
	maxSizeOfText = 17;
}


List::~List()
{
	if (needButton)
	{
		delete button;
	}

	while (mainObjects.size() > 0)
	{
		delete mainObjects.back();
		mainObjects.pop_back();
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
	return open && ((mousePosition >= Vector2int(xCoordinate, yCoordinate) && mousePosition <= Vector2int(xCoordinate + width, yCoordinate + searchEngineHeight + min(height, int(objects.size()) * fragmentHeight))) || (needButton && button->getStruct()->checkButtonIsPressed));
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

int List::getMainIndex()
{
	return mainIndex;
}

int List::getMainIndexOfSelectedObject()
{
	return mainIndexOfSelectedObject;
}



int List::getPosition()
{
	return position;
}


bool List::getNeedButton()
{
	return needButton;
}


Button *List::getButton()
{
	return button;
}


vector<ViewableObject *> &List::getViewableObjects()
{
	return objects;
}

vector<ViewableObject *> &List::getViewableMainObjects()
{
	return mainObjects;
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
			break;
		}
	}

	for (int i = 0; i < int(mainObjects.size()); ++i)
	{
		if (mainObjects[i]->getIndex() == object->getIndex())
		{
			mainIndexOfSelectedObject = i;
			mainIndex = i;
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
	return height + searchEngineHeight;
}


int List::getViewableObjectWidth()
{
	return objectWidth;
}

int List::getViewableObjectHeight()
{
	return objectHeight;
}


int List::getSearchEngineHeight()
{
	return searchEngineHeight;
}


string List::getInputField()
{
	return inputField;
}


void List::showInformation()
{
	if (index != -1)
	{
		needInformation = true;
	}
}

bool List::getNeedInformation()
{
	return needInformation;
}


void List::work(Vector2int mousePosition, bool isPressed, long timer, int fps, bool rightIsPressed)
{
	if (!isPressed && mouseButtonIsPressed && inFocuse(mousePosition))
	{
		cout << 0 << '\n';
		mouseButtonIsPressed = false;
		if (!firstClick)
		{
			firstClick = true;
			timerForDoubleClick = timer;
		}
		else if (timer - timerForDoubleClick < 1000)
		{
			if (needClose)
			{
				closeList();
			}
			indexOfSelectedObject = index;
			mainIndexOfSelectedObject = mainIndex;

			firstClick = false;
		}
		else
		{
			firstClick = false;
		}
	}

	mousePosition = mousePosition - getOffset();
	mousePosition.y -= searchEngineHeight;

	if (needButton)
	{
		button->work((mousePosition + Vector2int(0, searchEngineHeight)) * (open ? 1 : -100), isPressed && open, timer, fps);
	}

	if (!open)
	{
		needInformation = false;
	}
	else
	{
		if (needSelect)
		{
			needSelect = false;

			if (index != -1)
			{
				indexOfSelectedObject = index;
				mainIndexOfSelectedObject = mainIndex;

				if (needClose)
				{
					closeList();
				}
			}
			else if (objects.size() > 0)
			{
				index = 0;

				for (int i = 0; i < int(mainObjects.size()); ++i)
				{
					if (mainObjects[i] == objects[index])
					{
						mainIndex = i;
						break;
					}
				}

				indexOfSelectedObject = index;
				mainIndexOfSelectedObject = mainIndex;
			}
		}

		if (needButton && button->getStruct()->checkButtonIsPressed)
		{
			needInformation = false;
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
			needInformation = false;
			oldMousePosition = mousePosition;

			if (mousePosition > Vector2int() && mousePosition < Vector2int(width - (needButton ? 11 : 0), min(height, int(objects.size()) * fragmentHeight)))
			{
				if (!up && position + height + fragmentHeight <= int(objects.size()) * fragmentHeight)
				{
					position += fragmentHeight;

					updateViewableObject();
				}
				else if (!up)
				{
					position = max(0, int(objects.size()) * fragmentHeight - height);

					updateViewableObject();
				}
				else if (up && position - fragmentHeight >= 0)
				{
					position -= fragmentHeight;

				}
				else if (up)
				{
					position = 0;

					updateViewableObject();
				}
			}
			else
			{
				index += up ? -1 : 1;
				index = index < 0 ? 0 : index >= int(objects.size()) ? int(objects.size()) - 1 : index;

				for (int i = 0; i < int(mainObjects.size()); ++i)
				{
					if (mainObjects[i] == objects[index])
					{
						mainIndex = i;
						break;
					}
				}

				if (index * fragmentHeight <= position)
				{
					position = index * fragmentHeight;
				}
				else if ((index + 1) * fragmentHeight >= position + height)
				{
					position = (index + 1) * fragmentHeight - height;
				}

				updateViewableObject();
			}
			needDirect = false;
		}
		if (index != -1 && mousePosition > Vector2int() && mousePosition < Vector2int(width - (needButton ? 11 : 0), min(height, int(objects.size()) * fragmentHeight)))
		{
			index = (mousePosition.y + position) / fragmentHeight;
			index = index < 0 ? 0 : index >= int(objects.size()) ? int(objects.size()) - 1 : index;

			for (int i = 0; i < int(mainObjects.size()); ++i)
			{
				if (mainObjects[i] == objects[index])
				{
					mainIndex = i;
					break;
				}
			}

			if (index * fragmentHeight <= position)
			{
				position = index * fragmentHeight;
			}
			else if ((index + 1) * fragmentHeight >= position + height)
			{
				position = (index + 1) * fragmentHeight - height;
			}

			updateViewableObject();

			if (isPressed && (!needButton || (needButton && !button->getStruct()->checkButtonIsPressed)))
			{
				indexOfSelectedObject = index;
				mainIndexOfSelectedObject = mainIndex;

				mouseButtonIsPressed = true;
			}
		}

		if (mousePosition != oldMousePosition && mousePosition >= Vector2int() && mousePosition < Vector2int(width - 11, height))
		{
			needInformation = false;
			oldMousePosition = mousePosition;
		}

		if (index != -1 && rightIsPressed && inFocuse(mousePosition))
		{
			needInformation = true;
		}
	}
}

void List::workWithText(int unicode)
{
	bool changed = false;

	if (int(inputField.size()) < maxSizeOfText || unicode == 8)
	{
		if (unicode == 8 || unicode == 32 || (unicode >= 48 && unicode <= 57) || (unicode >= 65 && unicode <= 90) || (unicode >= 97 && unicode <= 122))
		{
			if (unicode == 8 && inputField.size() > 0)
			{
				inputField.pop_back();
				changed = true;
			}
			else if (unicode != 8)
			{
				inputField.push_back(char(unicode));
				changed = true;
			}
		}
	}

	if (changed)
	{
		objects.clear();

		for (int i = 0; i < int(mainObjects.size()); ++i)
		{
			if (mainObjects[i]->getComponentParameter()->name.size() >= inputField.size())
			{
				string firstName = mainObjects[i]->getComponentParameter()->name,
					secondName = inputField;

				for (int j = 0; j < int(firstName.size()); ++j)
				{
					if (firstName[j] >= 'A' && firstName[j] <= 'Z')
					{
						firstName[j] = char(int(firstName[j]) + 32);
					}
				}

				for (int j = 0; j < int(secondName.size()); ++j)
				{
					if (secondName[j] > 'A' && secondName[j] < 'Z')
					{
						secondName[j] = char(int(secondName[j]) + 40);
					}
				}

				if (firstName.find(secondName) != string::npos)
				{
					objects.push_back(mainObjects[i]);
				}
			}
		}


		if (int(objects.size()) * fragmentHeight > height)
		{
			needButton = true;

			conversionFactor = float(height - 51) / float(int(objects.size()) * fragmentHeight - height);
		}
		else
		{
			needButton = false;
		}

		index = -1;
		indexOfSelectedObject = -1;
		for (int i = 0; i < int(objects.size()); ++i)
		{
			if (objects[i] == mainObjects[mainIndex])
			{
				index = i;
			}
			if (objects[i] == mainObjects[mainIndexOfSelectedObject])
			{
				indexOfSelectedObject = i;
			}
		}

		position = 0;

		updateViewableObject();
	}
}