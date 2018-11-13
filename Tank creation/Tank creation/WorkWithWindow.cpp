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
		button = new Button[numberOfButton];

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
				button[j].setInformation(firstParameters[0], firstParameters[1], firstParameters[2], firstParameters[3], firstParameters[4], secondParameters[0], secondParameters[1], secondParameters[2]);
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

vector<Component *> WorkWithWindow::dataForResources()
{
	vector<Component *> components;

	string objectName, typeName, identifierName, typeName2, identifierName2, typeName3, identifierName3;

	int numberOfType, numberOfVariant, numberOfVariant2, numberOfVariant3;

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

			Component *newComponent = new BackgroundComponent(objectName, typeName + to_string(i + 1), identifierName, numberOfVariant);
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

			Component *newComponent = new SmallBlockComponent(objectName, typeName + to_string(i + 1), identifierName, numberOfVariant, health, canRebound);
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

			Component *newComponent = new BigBlockComponent(objectName, typeName + to_string(i + 1), identifierName, numberOfVariant, health, canRebound);
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

		Component *newComponent = new EngineRoomComponent(objectName, typeName, identifierName, numberOfVariant, typeName2, identifierName2, numberOfVariant2, typeName3, identifierName3, numberOfVariant3, health, xOffsetForRoom, yOffsetForRoom, xOffsetForPerson, yOffsetForPerson, width, height);
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

			Component *newComponent = new TrackComponent(objectName, typeName + to_string(i + 1), identifierName, numberOfVariant, health, width, height);
			components.push_back(newComponent);
		}
	}

	//Gun
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

			Component *newComponent = new GunComponent(objectName, to_string(i + 1) + typeName, identifierName, numberOfVariant, to_string(i + 1) + typeName2, identifierName2, numberOfVariant2, horizontally, damage, bulletSpeed, reload, xOffsetForBarrel, yOffsetForBarrel, xOriginForBarrel, yOriginForBarrel, healthPoints, backgroundIndex, width, height);
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

WorkWithWindow *WorkWithWindow::getNewWindow()
{
	return newWindow;
}