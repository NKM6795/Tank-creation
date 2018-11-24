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


void TankEditor::dfs(vector<vector<pair<TankEditor::Direct, TankEditor::Direct> > > &smallTank, int i, int j)
{
	pair<Direct, Direct> direct = smallTank[i][j];
	smallTank[i][j] = { Nowhere, Nowhere };

	if ((direct.first == Direct::All || direct.first == Direct::Left || direct.second == Direct::Left) && i - 1 >= 0 && (smallTank[i - 1][j].first == Direct::All || smallTank[i - 1][j].first == Direct::Right || smallTank[i - 1][j].second == Direct::Right))
	{
		dfs(smallTank, i - 1, j);
	}

	if ((direct.first == Direct::All || direct.first == Direct::Up || direct.second == Direct::Up) && j - 1 >= 0 && (smallTank[i][j - 1].first == Direct::All || smallTank[i][j - 1].first == Direct::Down || smallTank[i][j - 1].second == Direct::Down))
	{
		dfs(smallTank, i, j - 1);
	}
	
	if ((direct.first == Direct::All || direct.first == Direct::Right || direct.second == Direct::Right) && i + 1 < int(smallTank.size()) && (smallTank[i + 1][j].first == Direct::All || smallTank[i + 1][j].first == Direct::Left || smallTank[i + 1][j].second == Direct::Left))
	{
		dfs(smallTank, i + 1, j);
	}
	
	if ((direct.first == Direct::All || direct.first == Direct::Down || direct.second == Direct::Down) && j + 1 < int(smallTank.size()) && (smallTank[i][j + 1].first == Direct::All || smallTank[i][j + 1].first == Direct::Up || smallTank[i][j + 1].second == Direct::Up))
	{
		dfs(smallTank, i, j + 1);
	}
}

vector<vector<pair<TankEditor::Direct, TankEditor::Direct> > > TankEditor::getSmallTankForDfs()
{
	vector<vector<pair<Direct, Direct> > > smallTank((*objects).size(), vector<pair<Direct, Direct>>((*objects).size(), { Direct::Nowhere, Direct::Nowhere }));

	for (int i = 0; i < int((*objects).size()); ++i)
	{
		for (int j = 0; j < int((*objects).size()); ++j)
		{
			if ((*objects)[i][j] != nullptr)
			{
				if (typeid(*(*objects)[i][j]) == typeid(SmallBlock) || typeid(*(*objects)[i][j]) == typeid(BigBlock) || typeid(*(*objects)[i][j]) == typeid(EngineRoom) ||
					typeid(*(*objects)[i][j]) == typeid(AdditionToBigBlock) || typeid(*(*objects)[i][j]) == typeid(AdditionToEngineRoom))
				{
					smallTank[i][j] = { Direct::All, Direct::All };
				}
				else if ((typeid(*(*objects)[i][j]) == typeid(Track) || typeid(*(*objects)[i][j]) == typeid(AdditionToTrack)) && j == (*objects)[i][j]->getPosition().y / 20)
				{
					if (i == (*objects)[i][j]->getPosition().x / 20)
					{
						smallTank[i][j] = { Direct::Up, Direct::Right };
					}
					else if (i == (*objects)[i][j]->getPosition().x / 20 + (*objects)[i][j]->getComponentParameter()->width - 1)
					{
						smallTank[i][j] = { Direct::Up, Direct::Left };
					}
					else
					{
						smallTank[i][j] = { Direct::All, Direct::All };
					}
				}
				else if ((typeid(*(*objects)[i][j]) == typeid(Gun) || typeid(*(*objects)[i][j]) == typeid(AdditionToGun)) && (*objects)[i][j]->getComponentParameter()->horizontally && i == (*objects)[i][j]->getPosition().x / 20)
				{
					if ((*objects)[i][j]->getComponentParameter()->height == 1)
					{
						smallTank[i][j] = { Direct::Left, Direct::Left };
					}
					else if (j == (*objects)[i][j]->getPosition().y / 20)
					{
						smallTank[i][j] = { Direct::Down, Direct::Left };
					}
					else if (j == (*objects)[i][j]->getPosition().y / 20 + (*objects)[i][j]->getComponentParameter()->height - 1)
					{
						smallTank[i][j] = { Direct::Up, Direct::Left };
					}
					else
					{
						smallTank[i][j] = { Direct::All, Direct::All };
					}
				}
				else if ((typeid(*(*objects)[i][j]) == typeid(Gun) || typeid(*(*objects)[i][j]) == typeid(AdditionToGun)) && !(*objects)[i][j]->getComponentParameter()->horizontally && j == (*objects)[i][j]->getPosition().y / 20 + (*objects)[i][j]->getComponentParameter()->height - 1)
				{
					if (i == (*objects)[i][j]->getPosition().x / 20)
					{
						smallTank[i][j] = { Direct::Down, Direct::Right };
					}
					else if (i == (*objects)[i][j]->getPosition().x / 20 + (*objects)[i][j]->getComponentParameter()->width - 1)
					{
						smallTank[i][j] = { Direct::Down, Direct::Left };
					}
					else
					{
						smallTank[i][j] = { Direct::All, Direct::All };
					}
				}
			}
		}
	}

	return smallTank;
}


TankEditor::TankEditor(vector<vector<ViewableObject *> > &objects, int dataArraySize) : objects(&objects), dataArraySize(dataArraySize)
{
	needUpdateTank = true;
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
				else if (j + height == int(smallTank.size()))
				{
					continue;
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
		newViewableObject->needChangeColor = 1;

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

	needUpdateTank = true;
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


int TankEditor::completenessСheck()
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

	if (!checkMain)
	{
		return -1;
	}

	if (!checkTrack)
	{
		return -2;
	}

	vector<vector<pair<Direct, Direct> > > smallTank = getSmallTankForDfs();

	for (int i = 0; i < int(smallTank.size()); ++i)
	{
		for (int j = 0; j < int(smallTank.size()); ++j)
		{
			if (smallTank[i][j].first != Direct::Nowhere && !checkCompleteness)
			{
				dfs(smallTank, i, j);
				checkCompleteness = true;
			}
			else if (smallTank[i][j].first != Direct::Nowhere && checkCompleteness)
			{
				return 0;
			}
		}
	}

	return 1;
}

vector<ViewableObject *> TankEditor::getWrongObjects()
{
	Vector2int mainPosition(-1, -1);

	for (int i = 0; i < int((*objects).size()) && mainPosition.x == -1; ++i)
	{
		for (int j = 0; j < int((*objects).size()) && mainPosition.x == -1; ++j)
		{
			if ((*objects)[i][j] != nullptr && typeid(*(*objects)[i][j]) == typeid(EngineRoom))
			{
				mainPosition = Vector2int(i, j);
			}
		}
	}

	vector<vector<pair<Direct, Direct> > > smallTank = getSmallTankForDfs();
	dfs(smallTank, mainPosition.x, mainPosition.y);

	vector<ViewableObject *> result;
	for (int i = 0; i < int(smallTank.size()); ++i)
	{
		for (int j = 0; j < int(smallTank.size()); ++j)
		{
			if (smallTank[i][j].first != Direct::Nowhere && !(typeid(*(*objects)[i][j]) == typeid(AdditionToBigBlock) || typeid(*(*objects)[i][j]) == typeid(AdditionToEngineRoom) || typeid(*(*objects)[i][j]) == typeid(AdditionToGun) || typeid(*(*objects)[i][j]) == typeid(AdditionToTrack)))
			{
				ViewableObject *newViewableObject = getViewableObject((*objects)[i][j]->getComponent(), (*objects)[i][j]->getIndex());
				newViewableObject->setPosition(Vector2int(i, j) * 20 + getOffset());
				newViewableObject->setHeath((*objects)[i][j]->getComponentParameter()->healthPoints);
				newViewableObject->needChangeColor = -1;

				result.push_back(newViewableObject);
			}
			//Vertical guns
			else if (smallTank[i][j].first != Direct::Nowhere && typeid(*(*objects)[i][j]) == typeid(AdditionToGun) && smallTank[i][j].first == Direct::Down && smallTank[i][j].second == Direct::Right)
			{
				Vector2int position = (*objects)[i][j]->getPosition() / 20;
				ViewableObject *gun = (*objects)[position.x][position.y];

				ViewableObject *newViewableObject = getViewableObject(gun->getComponent(), gun->getIndex());
				newViewableObject->setPosition(position * 20 + getOffset());
				newViewableObject->setHeath(gun->getComponentParameter()->healthPoints);
				newViewableObject->needChangeColor = -1;

				result.push_back(newViewableObject);
			}
		}
	}
	return result;
}


bool TankEditor::getNeedUpdateTank()
{
	if (needUpdateTank)
	{
		needUpdateTank = false;
		return true;
	}
	return false;
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