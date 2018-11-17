#include "TankEditor.h"


bool TankEditor::checkFreePlace(vector<vector<bool> > &smallTank, int widht, int height, int i, int j)
{
	if (i < 0 || j < 0 || i + widht > int(smallTank.size()) || j + height > int(smallTank.size()))
	{
		return false;
	}
	else
	{
		for (int l = i; l < i + widht; ++l)
		{
			for (int k = j; k < j + height; ++k)
			{
				if (smallTank[l][k])
				{
					return false;
				}
			}
		}
		return true;
	}
}


void TankEditor::addViewableObjectOnPosition(Component *component, int index, Vector2int position)
{
	(*objects)[position.x][position.y] = getViewableObject(component, index);
	(*objects)[position.x][position.y]->setPosition(position * 20);
	(*objects)[position.x][position.y]->setHeath(component->getStruct()->healthPoints);

	if (component->getStruct()->width > 1)
	{
		for (int i = 0; i < component->getStruct()->width; ++i)
		{
			for (int j = 0; j < component->getStruct()->height; ++j)
			{
				if (!(i == 0 && j == 0))
				{
					(*objects)[position.x + i][position.y + j] = (*objects)[position.x][position.y]->getAddition();
				}
			}
		}
	}
}


void TankEditor::dfs(vector<vector<bool> > &smallTank, int i, int j)
{
	if (i - 1 >= 0 && smallTank[i - 1][j])
	{
		smallTank[i - 1][j] = false;
		dfs(smallTank, i - 1, j);
	}

	if (j - 1 >= 0 && smallTank[i][j - 1])
	{
		smallTank[i][j - 1] = false;
		dfs(smallTank, i, j - 1);
	}
	
	if (i + 1 < int(smallTank.size()) && smallTank[i + 1][j])
	{
		smallTank[i + 1][j] = false;
		dfs(smallTank, i + 1, j);
	}
	
	if (j + 1 < int(smallTank.size()) && smallTank[i][j + 1])
	{
		smallTank[i][j + 1] = false;
		dfs(smallTank, i, j + 1);
	}
}


TankEditor::TankEditor(vector<vector<ViewableObject *> > &objects, int dataArraySize) : objects(&objects), dataArraySize(dataArraySize)
{

}

TankEditor::~TankEditor()
{

}


Vector2int TankEditor::getOffset()
{
	return Vector2int(xOffset, yOffset);
}

void TankEditor::setOffset(Vector2int offset)
{
	xOffset = offset.x;
	yOffset = offset.y;
}

void TankEditor::setOffset(int x, int y)
{
	xOffset = x;
	yOffset = y;
}


ViewableObject *TankEditor::getViewableObject(Component *component, int index)
{
	ViewableObject *newViewableObject = nullptr;

	if (typeid(*component) == typeid(BackgroundComponent))
	{
		newViewableObject = new Background(component, index);
	}
	else if (typeid(*component) == typeid(SmallBlockComponent))
	{
		newViewableObject = new SmallBlock(component, index);
	}
	else if (typeid(*component) == typeid(BigBlockComponent))
	{
		newViewableObject = new BigBlock(component, index);
	}
	else if (typeid(*component) == typeid(EngineRoomComponent))
	{
		newViewableObject = new EngineRoom(component, index);
	}
	else if (typeid(*component) == typeid(TrackComponent))
	{
		newViewableObject = new Track(component, index);
	}
	else if (typeid(*component) == typeid(GunComponent))
	{
		newViewableObject = new Gun(component, index);
	}
	else if (typeid(*component) == typeid(TankPictureComponent))
	{
		newViewableObject = new TankPicture(component, index);
	}

	return newViewableObject;
}

ViewableObject *TankEditor::getViewableObject(Vector2int mousePosition)
{
	mousePosition = mousePosition - getOffset();

	int i = mousePosition.x / 20,
		j = mousePosition.y / 20;

	if (i < 0 || j < 0 || i >= int((*objects).size()) || j >= int((*objects).size()))
	{
		return nullptr;
	}

	ViewableObject *object = (*objects)[i][j];

	if (object == nullptr)
	{
		return nullptr;
	}

	Vector2int position = (*objects)[i][j]->getPosition() / 20;

	return (*objects)[position.x][position.y];
}


ViewableObject *TankEditor::getCopy(ViewableObject *object)
{
	return getViewableObject(object->getComponent(), object->getIndex());
}


Vector2int TankEditor::getFreePlace(Component *component, Vector2int mousePosition)
{
	vector<vector<bool> > smallTank = Tank::getSmallTank(*objects);

	mousePosition = mousePosition - getOffset();

	int widht = component->getStruct()->width,
		height = component->getStruct()->height;
	
	float x = float(mousePosition.x) / 20,
		y = float(mousePosition.y) / 20;

	if (x < 0 || y < 0 || x >= float((*objects).size()) || y >= float((*objects).size()))
	{
		return Vector2int(-1, -1);
	}

	float maxR = sqrt(2.f) * 30.f;

	int tempI = (widht % 2 == 1) ? int(x - widht / 2) : int(x + 0.5f - widht / 2),
		tempJ = (height % 2 == 1) ? int(y - height / 2) : int(y + 0.5f - height / 2);

	float r = 0;

	if (typeid(*component) == typeid(TrackComponent) && component->getStruct()->height + int(y) < int(smallTank.size()))
	{
		r = float(smallTank.size()) - component->getStruct()->height - y - 1;
	}

	for (; r < maxR; r += 0.5f)
	{
		int oldI = -1,
			oldJ = -1;
		for (float phi = 0; phi < 2.f * PI; phi += PI / 50.f)
		{
			int i = (widht % 2 == 1) ? int(x + r * sin(phi) - widht / 2) : int(x + r * sin(phi) + 0.5f - widht / 2),
				j = (height % 2 == 1) ? int(y + r * cos(phi) - height / 2) : int(y + r * cos(phi) + 0.5f - height / 2);

			if (checkFreePlace(smallTank, widht, height, i, j))
			{
				if (typeid(*component) == typeid(TrackComponent))
				{
					if (component->getStruct()->height + j < int(smallTank.size()))
					{
						continue;
					}
				}

				if (oldI == -1)
				{
					oldI = i;
					oldJ = j;
				}

				if (((i - tempI) * (i - tempI) + (j - tempJ) * (j - tempJ)) < ((oldI - tempI) * (oldI - tempI) + (oldJ - tempJ) * (oldJ - tempJ)))
				{
					oldI = i;
					oldJ = j;
				}
			}
		}

		if (oldI != -1)
		{
			return Vector2int(oldI, oldJ);
		}
	}

	return Vector2int(-1, -1);
}

ViewableObject *TankEditor::getFreePlace(Component *component, int index, Vector2int mousePosition)
{
	Vector2int position = getFreePlace(component, mousePosition);

	if (position.x == -1)
	{
		return nullptr;
	}
	else
	{
		ViewableObject *newViewableObject = getViewableObject(component, index);
		newViewableObject->setPosition(position * 20 + getOffset());
		newViewableObject->setHeath(component->getStruct()->healthPoints);
		newViewableObject->needChangeColor = true;

		return newViewableObject;
	}
}


bool TankEditor::addViewableObject(Component *component, int index, Vector2int mousePosition)
{
	Vector2int position = getFreePlace(component, mousePosition);

	if (position.x == -1)
	{
		return false;
	}
	else
	{
		addViewableObjectOnPosition(component, index, position);
		return true;
	}
}


bool TankEditor::removeViewableObject(Vector2int mousePosition)
{
	ViewableObject *object = getViewableObject(mousePosition);

	if (object == nullptr)
	{
		return false;
	}

	Vector2int position = object->getPosition() / 20;

	int widht = object->getComponentParameter()->width,
		height = object->getComponentParameter()->height;

	delete object;
	
	for (int l = 0; l < widht; ++l)
	{
		for (int k = 0; k < height; ++k)
		{
			(*objects)[position.x + l][position.y + k] = nullptr;
		}
	}

	return true;
}

void TankEditor::clear()
{
	for (int i = 0; i < int((*objects).size()); ++i)
	{
		for (int j = 0; j < int((*objects).size()); ++j)
		{
			removeViewableObject(Vector2int(i, j) * 20 + getOffset());
		}
	}
}


bool TankEditor::isEmpty()
{
	for (int i = 0; i < int((*objects).size()); ++i)
	{
		for (int j = 0; j < int((*objects).size()); ++j)
		{
			if ((*objects)[i][j] != nullptr)
			{
				return false;
			}
		}
	}

	return true;
}


bool TankEditor::completenessСheck()
{
	bool checkMain = false,
		checkTrack = false,
		checkCompleteness = false;

	for (int i = 0; i < int((*objects).size()); ++i)
	{
		for (int j = 0; j < int((*objects).size()); ++j)
		{
			if (!checkMain && (*objects)[i][j] != nullptr && typeid(*(*objects)[i][j]) == typeid(EngineRoom))
			{
				checkMain = true;
			}
			if (!checkTrack && (*objects)[i][j] != nullptr && typeid(*(*objects)[i][j]) == typeid(Track))
			{
				checkTrack = true;
			}
		}
	}

	if (!checkMain || !checkTrack)
	{
		return false;
	}

	vector<vector<bool> > smallTank = Tank::getSmallTank(*objects);

	for (int i = 0; i < int(smallTank.size()); ++i)
	{
		for (int j = 0; j < int(smallTank.size()); ++j)
		{
			if (smallTank[i][j] && !checkCompleteness)
			{
				dfs(smallTank, i, j);
				checkCompleteness = true;
			}
			else if (smallTank[i][j] && checkCompleteness)
			{
				return false;
			}
		}
	}

	return true;
}


void TankEditor::save(string fileName)
{
	fileName = "Data/Tanks/" + fileName + ".tnk";

	ofstream fileOut(fileName);

	for (int i = 0; i < int((*objects).size()); ++i)
	{
		for (int j = 0; j < int((*objects).size()); ++j)
		{
			fileOut << i << ' ' << j << ' ';

			if ((*objects)[i][j] == nullptr || typeid(*(*objects)[i][j]) == typeid(AdditionToBigBlock) || typeid(*(*objects)[i][j]) == typeid(AdditionToEngineRoom) || typeid(*(*objects)[i][j]) == typeid(AdditionToGun) || typeid(*(*objects)[i][j]) == typeid(AdditionToTrack))
			{
				fileOut << -1 << ' ';
			}
			else
			{
				fileOut << (*objects)[i][j]->getIndex() << ' ';
			}
		}
	}

	fileOut.close();

	ifstream fileIn("Data/Tanks/Number.dat");

	int number;
	fileIn >> number;

	bool needNewViewableObject = true;

	vector<string> names(number, "");
	
	if (number > 0)
	{
		getline(fileIn, names[0]);
		for (int i = 0; i < number; ++i)
		{
			getline(fileIn, names[i]);
			if (names[i] == fileName.substr(fileName.find("Tanks/") + 6, fileName.find(".tnk") - fileName.find("Tanks/") - 6))
			{
				needNewViewableObject = false;
			}
		}
	}
	fileIn.close();

	fileOut.open("Data/Tanks/Number.dat");

	number += needNewViewableObject;

	fileOut << number << '\n';

	for (int i = 0; i < number - needNewViewableObject; ++i)
	{
		fileOut << names[i] << '\n';
	}

	if (needNewViewableObject)
	{
		fileOut << fileName.substr(fileName.find("Tanks/") + 6, fileName.find(".tnk") - fileName.find("Tanks/") - 6) << '\n';
	}

	fileOut.close();
}

void TankEditor::download(string fileName, vector<Component *> &components)
{
	fileName = "Data/Tanks/" + fileName + ".tnk";

	ifstream fileIn(fileName);

	if (fileIn)
	{
		clear();

		for (int i = 0; i < int((*objects).size()); ++i)
		{
			for (int j = 0; j < int((*objects).size()); ++j)
			{
				Vector2int position;
				int index;
				fileIn >> position.x >> position.y >> index;

				if (index != -1)
				{
					addViewableObjectOnPosition(components[index], index, position);
				}
			}
		}
	}
}