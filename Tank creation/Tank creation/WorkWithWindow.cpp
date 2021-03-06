#include "WorkWithWindow.h"


void WorkWithWindow::forConstructor(string &fileName)
{
	windowIsOpen = true;
	needNewWindow = false;
	needWindowResult = false;

	fileIn.open(fileName);

	getline(fileIn, windowName);

	fileIn >> xCoordinate >> yCoordinate >> screanWidth >> screanHeight;

	fileIn >> timeForWork >> coefficientForTime;

	fileIn >> numberOfButton;
	if (numberOfButton != 0)
	{
		int countOfSimilarButton;
		int firstParameters[5];
		string secondParameters[3];

		for (int i = 0; i < numberOfButton;)
		{
			fileIn >> countOfSimilarButton;

			for (int j = 2; j < 5; ++j)
			{
				fileIn >> firstParameters[j];
			}
			getline(fileIn, secondParameters[0]);
			for (int j = 1; j < 3; ++j)
			{
				getline(fileIn, secondParameters[j]);
			}

			for (int j = i; j < i + countOfSimilarButton; ++j)
			{
				fileIn >> firstParameters[0] >> firstParameters[1];
				getline(fileIn, secondParameters[0]);
				if (secondParameters[0] != " ")
				{
					secondParameters[0].erase(secondParameters[0].begin());
				}

				button[secondParameters[0]] = Button(firstParameters[0], firstParameters[1], firstParameters[2], firstParameters[3], firstParameters[4], secondParameters[0], secondParameters[1], secondParameters[2]);
			}
			i += countOfSimilarButton;
		}
	}

	fileIn >> numberOfText;
	if (numberOfText != 0)
	{
		textXCoordinate = new int[numberOfText];
		textYCoordinate = new int[numberOfText];
		characterSize = new int[numberOfText];
		text = new string[numberOfText];
		fontName = new string[numberOfText];

		int countOfSimilarText;
		int firstParameters[3];
		string secondParameters[2];

		for (int i = 0; i < numberOfText;)
		{
			fileIn >> countOfSimilarText;

			for (int j = 2; j < 3; ++j)
			{
				fileIn >> firstParameters[j];
			}
			getline(fileIn, secondParameters[0]);
			for (int j = 1; j < 2; ++j)
			{
				getline(fileIn, secondParameters[j]);
			}

			for (int j = i; j < i + countOfSimilarText; ++j)
			{
				fileIn >> firstParameters[0] >> firstParameters[1];
				getline(fileIn, secondParameters[0]);
				if (secondParameters[0] != " ")
				{
					secondParameters[0].erase(secondParameters[0].begin());
				}

				textXCoordinate[j] = firstParameters[0];
				textYCoordinate[j] = firstParameters[1];
				characterSize[j] = firstParameters[2];
				text[j] = secondParameters[0];
				fontName[j] = secondParameters[1];
			}
			i += countOfSimilarText;
		}
	}
}


vector<Component *> WorkWithWindow::dataForResources(bool needCost, bool needIndexForGun)
{
	vector<Component *> components;

	string name, objectName, typeName, identifierName, typeName2, identifierName2, typeName3, identifierName3;

	int numberOfType, numberOfVariant, numberOfVariant2, numberOfVariant3;

	int cost;

	//Background
	{
		getline(fileIn, objectName);
		if (objectName == "")
		{
			getline(fileIn, objectName);
		}

		getline(fileIn, typeName);
		getline(fileIn, identifierName);

		fileIn >> numberOfType;

		for (int i = 0; i < numberOfType; ++i)
		{
			fileIn >> numberOfVariant;

			getline(fileIn, name);
			getline(fileIn, name);

			Component *newComponent = new BackgroundComponent(name, objectName, typeName + to_string(i + 1), identifierName, numberOfVariant);
			components.push_back(newComponent);
		}
	}

	//Engine room
	{
		getline(fileIn, objectName);
		if (objectName == "")
		{
			getline(fileIn, objectName);
		}

		getline(fileIn, typeName);
		getline(fileIn, identifierName);

		getline(fileIn, typeName2);
		getline(fileIn, identifierName2);

		getline(fileIn, typeName3);
		getline(fileIn, identifierName3);

		fileIn >> numberOfVariant >> numberOfVariant2 >> numberOfVariant3;

		int health;
		fileIn >> health;

		int xOffsetForRoom,
			yOffsetForRoom;
		int xOffsetForPerson,
			yOffsetForPerson;
		fileIn >> xOffsetForRoom >> yOffsetForRoom >> xOffsetForPerson >> yOffsetForPerson;

		int width,
			height;
		fileIn >> width >> height;

		getline(fileIn, name);
		getline(fileIn, name);

		Component *newComponent;
		if (needCost)
		{
			fileIn >> cost;
			newComponent = new EngineRoomComponent(name, objectName, typeName, identifierName, numberOfVariant, typeName2, identifierName2, numberOfVariant2, typeName3, identifierName3, numberOfVariant3, health, xOffsetForRoom, yOffsetForRoom, xOffsetForPerson, yOffsetForPerson, width, height, cost);
		}
		else
		{
			newComponent = new EngineRoomComponent(name, objectName, typeName, identifierName, numberOfVariant, typeName2, identifierName2, numberOfVariant2, typeName3, identifierName3, numberOfVariant3, health, xOffsetForRoom, yOffsetForRoom, xOffsetForPerson, yOffsetForPerson, width, height);
		}
		components.push_back(newComponent);
	}

	//Track
	{
		getline(fileIn, objectName);
		if (objectName == "")
		{
			getline(fileIn, objectName);
		}

		getline(fileIn, typeName);
		getline(fileIn, identifierName);

		fileIn >> numberOfType;

		for (int i = 0; i < numberOfType; ++i)
		{
			fileIn >> numberOfVariant;

			int health;
			fileIn >> health;

			int width,
				height;
			fileIn >> width >> height;

			getline(fileIn, name);
			getline(fileIn, name);

			Component *newComponent;
			if (needCost)
			{
				fileIn >> cost;
				newComponent = new TrackComponent(name, objectName, typeName + to_string(i + 1), identifierName, numberOfVariant, health, width, height, cost);
			}
			else
			{
				newComponent = new TrackComponent(name, objectName, typeName + to_string(i + 1), identifierName, numberOfVariant, health, width, height);
			}
			components.push_back(newComponent);
		}
	}

	//Small block
	{
		getline(fileIn, objectName);
		if (objectName == "")
		{
			getline(fileIn, objectName);
		}

		getline(fileIn, typeName);
		getline(fileIn, identifierName);

		fileIn >> numberOfType;

		for (int i = 0; i < numberOfType; ++i)
		{
			fileIn >> numberOfVariant;

			int health;
			bool canRebound;
			fileIn >> canRebound >> health;

			getline(fileIn, name);
			getline(fileIn, name);

			Component *newComponent;
			if (needCost)
			{
				fileIn >> cost;
				newComponent = new SmallBlockComponent(name, objectName, typeName + to_string(i + 1), identifierName, numberOfVariant, health, canRebound, cost);
			}
			else
			{
				newComponent = new SmallBlockComponent(name, objectName, typeName + to_string(i + 1), identifierName, numberOfVariant, health, canRebound);
			}
			components.push_back(newComponent);
		}
	}

	//Big block
	{
		getline(fileIn, objectName);
		if (objectName == "")
		{
			getline(fileIn, objectName);
		}

		getline(fileIn, typeName);
		getline(fileIn, identifierName);

		fileIn >> numberOfType;

		for (int i = 0; i < numberOfType; ++i)
		{
			fileIn >> numberOfVariant;

			int health;
			bool canRebound;
			fileIn >> canRebound >> health;

			getline(fileIn, name);
			getline(fileIn, name);

			Component *newComponent;
			if (needCost)
			{
				fileIn >> cost;
				newComponent = new BigBlockComponent(name, objectName, typeName + to_string(i + 1), identifierName, numberOfVariant, health, canRebound, cost);
			}
			else
			{
				newComponent = new BigBlockComponent(name, objectName, typeName + to_string(i + 1), identifierName, numberOfVariant, health, canRebound);
			}
			components.push_back(newComponent);
		}
	}
	   
	//Gun
	{
		vector<int> indexOfComponents;

		getline(fileIn, objectName);
		if (objectName == "")
		{
			getline(fileIn, objectName);
		}

		getline(fileIn, typeName);
		getline(fileIn, identifierName);

		getline(fileIn, typeName2);
		getline(fileIn, identifierName2);

		fileIn >> numberOfType;

		for (int i = 0; i < numberOfType; ++i)
		{
			fileIn >> numberOfVariant >> numberOfVariant2;

			bool horizontally;
			int damage;
			int bulletSpeed;
			int reload;
			int xOffsetForBarrel,
				yOffsetForBarrel;
			int xOriginForBarrel,
				yOriginForBarrel;
			int healthPoints;
			int backgroundIndex;
			fileIn >> horizontally >> damage >> bulletSpeed >> reload >> xOffsetForBarrel >> yOffsetForBarrel >> xOriginForBarrel >> yOriginForBarrel >> healthPoints >> backgroundIndex;

			int width,
				height;
			fileIn >> width >> height;

			if (needIndexForGun)
			{
				int numberOfComponents;
				fileIn >> numberOfComponents;

				indexOfComponents.clear();
				indexOfComponents.resize(numberOfComponents);
				for (int i = 0; i < numberOfComponents; ++i)
				{
					fileIn >> indexOfComponents[i];
				}
			}

			getline(fileIn, name);
			getline(fileIn, name);

			Component *newComponent;
			if (needIndexForGun)
			{
				if (needCost)
				{
					fileIn >> cost;
					newComponent = new GunComponent(name, objectName, to_string(i + 1) + typeName, identifierName, numberOfVariant, to_string(i + 1) + typeName2, identifierName2, numberOfVariant2, horizontally, damage, bulletSpeed, reload, xOffsetForBarrel, yOffsetForBarrel, xOriginForBarrel, yOriginForBarrel, healthPoints, backgroundIndex, width, height, indexOfComponents, cost);
				}
				else
				{
					newComponent = new GunComponent(name, objectName, to_string(i + 1) + typeName, identifierName, numberOfVariant, to_string(i + 1) + typeName2, identifierName2, numberOfVariant2, horizontally, damage, bulletSpeed, reload, xOffsetForBarrel, yOffsetForBarrel, xOriginForBarrel, yOriginForBarrel, healthPoints, backgroundIndex, width, height, indexOfComponents);
				}
			}
			else
			{
				if (needCost)
				{
					fileIn >> cost;
					newComponent = new GunComponent(name, objectName, to_string(i + 1) + typeName, identifierName, numberOfVariant, to_string(i + 1) + typeName2, identifierName2, numberOfVariant2, horizontally, damage, bulletSpeed, reload, xOffsetForBarrel, yOffsetForBarrel, xOriginForBarrel, yOriginForBarrel, healthPoints, backgroundIndex, width, height, vector<int>(), cost);
				}
				else
				{
					newComponent = new GunComponent(name, objectName, to_string(i + 1) + typeName, identifierName, numberOfVariant, to_string(i + 1) + typeName2, identifierName2, numberOfVariant2, horizontally, damage, bulletSpeed, reload, xOffsetForBarrel, yOffsetForBarrel, xOriginForBarrel, yOriginForBarrel, healthPoints, backgroundIndex, width, height);
				}
			}
			components.push_back(newComponent);
		}
	}

	return components;
}

vector<Component *> WorkWithWindow::dataForBackgroundBattle()
{
	vector<Component *> components;

	string name, objectName, typeName, identifierName;

	int numberOfType, numberOfVariant;

	vector<Vector2int> dimensions;
	vector<Vector2int> offsets;

	//Background for battle
	{
		getline(fileIn, objectName);
		if (objectName == "")
		{
			getline(fileIn, objectName);
		}

		getline(fileIn, typeName);
		getline(fileIn, identifierName);

		fileIn >> numberOfType;

		for (int i = 0; i < numberOfType; ++i)
		{
			fileIn >> numberOfVariant;

			dimensions.clear();
			dimensions.resize(numberOfVariant);

			offsets.clear();
			offsets.resize(numberOfVariant);

			for (int j = 0; j < numberOfVariant; ++j)
			{
				fileIn >> dimensions[j].x >> dimensions[j].y >> offsets[j].x >> offsets[j].y;
			}

			getline(fileIn, name);
			getline(fileIn, name);

			Component *newComponent = new BackgroundForBattleComponent(name, objectName, typeName + to_string(i + 1), identifierName, numberOfVariant, dimensions, offsets);

			components.push_back(newComponent);
		}
	}

	return components;
}

vector<Component *> WorkWithWindow::dataForSpeedometer()
{
	vector<Component *> components;

	string name, objectName, typeName, identifierName, typeName2, typeName3;

	int numberOfVariant, numberOfOffset;

	vector<Vector2int> offsets;

	//Speedometer
	{
		getline(fileIn, objectName);
		if (objectName == "")
		{
			getline(fileIn, objectName);
		}

		getline(fileIn, typeName);
		getline(fileIn, identifierName);
		getline(fileIn, typeName2);
		getline(fileIn, typeName3);

		
		fileIn >> numberOfVariant;

		fileIn >> numberOfOffset;


		offsets.clear();
		offsets.resize(numberOfOffset);

		for (int j = 0; j < numberOfOffset; ++j)
		{
			fileIn >> offsets[j].x >> offsets[j].y;
		}

		getline(fileIn, name);
		getline(fileIn, name);

		Component *newComponent = new SpeedometerComponent(name, objectName, typeName, identifierName, numberOfVariant, typeName2, typeName3, offsets);

		components.push_back(newComponent);
	}

	return components;
}

vector<Component *> WorkWithWindow::dataForAllotment()
{
	vector<Component *> components;

	string name, objectName, typeName, identifierName;

	int numberOfType;

	vector<Vector2int> offsets(1, Vector2int());

	//Allotment
	{
		getline(fileIn, objectName);
		if (objectName == "")
		{
			getline(fileIn, objectName);
		}

		getline(fileIn, typeName);
		getline(fileIn, name);


		fileIn >> numberOfType;

		offsets.clear();
		offsets.resize(1);

		fileIn >> offsets[0].x >> offsets[0].y;

		for (int i = 0; i < numberOfType; ++i)
		{
			Component *newComponent = new AllotmentComponent(name, objectName, typeName + to_string(i + 1), identifierName, 1, offsets);

			components.push_back(newComponent);
		}
	}

	return components;
}

vector<Component *> WorkWithWindow::dataForBullet()
{
	vector<Component *> components;

	string name, objectName, typeName, identifierName;

	int numberOfType, numberOfVariant;

	//Bullet
	{
		getline(fileIn, objectName);
		if (objectName == "")
		{
			getline(fileIn, objectName);
		}

		getline(fileIn, typeName);
		getline(fileIn, identifierName);
		getline(fileIn, name);

		fileIn >> numberOfType;

		for (int i = 0; i < numberOfType; ++i)
		{
			fileIn >> numberOfVariant;

			int width,
				height;
			fileIn >> width >> height;

			Component *newComponent = new BulletComponent(name, objectName, typeName + to_string(i + 1), identifierName, numberOfVariant, width, height);
			components.push_back(newComponent);
		}
	}

	return components;
}


Graphic *WorkWithWindow::getGraphic()
{
	return graphic;
}


bool WorkWithWindow::isOpen()
{
	return windowIsOpen;
}


bool WorkWithWindow::getNeedNewWindow()
{
	return needNewWindow;
}

void WorkWithWindow::finishNewWindow()
{
	needNewWindow = false;
	delete newWindow;
}

WorkWithWindow *WorkWithWindow::getNewWindow()
{
	return newWindow;
}


bool WorkWithWindow::getNeedWindowResult()
{
	return needWindowResult;
}

string WorkWithWindow::getWindowResult()
{
	return windowResult;
}

void WorkWithWindow::setWindowResult(string result)
{
	windowResult = result;
}
