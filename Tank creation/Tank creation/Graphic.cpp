#include "Graphic.h"


void Graphic::forConstructor()
{
	textureForWindow = new RenderTexture;
	textureForWindow->create(screanWidth, screanHeight);
	textureForWindow->clear(Color(50, 100, 50));

	numberOfButtonDraw = 0;
	numberOfTextDraw = 0;
	needBackground = false;
	needNotificationWindow = false;
	notificationNeedInputField = false;
}


Graphic::Graphic(RenderWindow *windowForCopy)
{
	window = windowForCopy;
	screanWidth = window->getSize().x;
	screanHeight = window->getSize().y;

	forConstructor();
}

Graphic::~Graphic()
{
	delete textureForWindow;

	if (numberOfButtonDraw != 0)
	{
		delete[] buttonDraw;
	}

	if (numberOfTextDraw != 0)
	{
		delete[] textDraw;

		delete[] font;
	}

	if (needBackground)
	{
		delete backgroundSprite;

		delete backgroundTexture;
	}

	if (needNotificationWindow)
	{
		delete windowBackgroundTexture;

		delete windowBackgroundSprite;
		
		delete formTexture;
		
		delete formSprite;
	}

	if (notificationNeedInputField)
	{
		delete notificationText;

		delete notificationFont;
	}

	if (needObject)
	{
		int number = int(components.size());

		for (int i = 0; i < number; ++i)
		{
			delete components.back();

			components.pop_back();
		}
	}

	if (needTank)
	{
		delete tankDraw;

		delete tankTexture;

		delete tankSprite;
	}
}


void Graphic::setInformation(int countOfButton, Button *button)
{
	numberOfButtonDraw = countOfButton;
	buttonDraw = new ButtonDraw[numberOfButtonDraw];

	for (int i = 0; i < numberOfButtonDraw; ++i)
	{
		buttonDraw[i].setInformation(*button[i].getStruct());
	}
}

void Graphic::setInformation(int countOfText, string *text, string *fontName, int *characterSize, int *xCoordinate, int *yCoordinate)
{
	numberOfTextDraw = countOfText;
	textDraw = new Text[numberOfTextDraw];
	font = new Font[numberOfTextDraw];

	for (int i = 0; i < numberOfTextDraw; ++i)
	{
		font[i].loadFromFile(fontName[i]);

		textDraw[i].setFont(font[i]);
		textDraw[i].setString(text[i]);
		textDraw[i].setCharacterSize(characterSize[i]);
		textDraw[i].setFillColor(Color::White);
		textDraw[i].setOrigin(textDraw[i].getLocalBounds().width * 0.5f, textDraw[i].getLocalBounds().height * 0.5f);
		textDraw[i].setPosition(float(xCoordinate[i]), float(yCoordinate[i]));
	}
}

void Graphic::setInformation(int xCoordinate, int yCoordinate, int width, int height, string fileName)
{
	needBackground = true;

	backgroundTexture = new Texture;
	backgroundTexture->loadFromFile(fileName);

	backgroundSprite = new Sprite;
	backgroundSprite->setTexture(*backgroundTexture);

	backgroundSprite->setOrigin(width * 0.5f, height * 0.5f);
	backgroundSprite->setPosition(float(xCoordinate), float(yCoordinate));
}

void Graphic::setInformation(int width, int height, bool needInputField, int xCoordinate, int yCoordinate, int characterSize, string fontName, RenderTexture *renderTextureForBackground)
{
	needNotificationWindow = true;

	renderTextureForBackground->display();

	windowBackgroundTexture = new Texture(renderTextureForBackground->getTexture());

	windowBackgroundSprite = new Sprite;
	windowBackgroundSprite->setTexture(*windowBackgroundTexture);
	windowBackgroundSprite->setColor(Color(100, 100, 100));

	renderTextureForBackground->clear(Color(50, 100, 50));

	Image *imageForForm;
	imageForForm = getForm(width, height);

	formTexture = new Texture;
	formTexture->loadFromImage(*imageForForm);

	formSprite = new Sprite;
	formSprite->setTexture(*formTexture);
	formSprite->setOrigin(width * 0.5f, height * 0.5f);
	formSprite->setPosition(screanWidth * 0.5f, screanHeight * 0.5f);

	delete imageForForm;

	notificationNeedInputField = needInputField;

	if (notificationNeedInputField)
	{
		notificationFont = new Font;
		notificationFont->loadFromFile(fontName);
		
		notificationText = new Text;
		notificationText->setFont(*notificationFont);
		notificationText->setFillColor(Color::White);
		notificationText->setCharacterSize(characterSize);
		notificationText->setPosition(float(xCoordinate), float(yCoordinate));
		notificationText->setOrigin(0.f, characterSize * 0.5f);
	}
}

void Graphic::setInformation(vector<Component *> &componentsForData)
{
	needObject = true;

	int number = int(componentsForData.size());

	for (int i = 0; i < number; ++i)
	{
		ComponentDraw *newComponent;
		if (typeid(*componentsForData[i]) == typeid(BackgroundComponent))
		{
			newComponent = new BackgroundDraw(componentsForData[i]->getStruct());
		}
		else if (typeid(*componentsForData[i]) == typeid(SmallBlockComponent))
		{
			newComponent = new SmallBlockDraw(componentsForData[i]->getStruct());
		}
		else if (typeid(*componentsForData[i]) == typeid(BigBlockComponent))
		{
			newComponent = new BigBlockDraw(componentsForData[i]->getStruct(), components[0]);
		}
		else if (typeid(*componentsForData[i]) == typeid(EngineRoomComponent))
		{
			newComponent = new EngineRoomDraw(componentsForData[i]->getStruct());
		}
		else if (typeid(*componentsForData[i]) == typeid(TrackComponent))
		{
			newComponent = new TrackDraw(componentsForData[i]->getStruct());
		}
		else if (typeid(*componentsForData[i]) == typeid(GunComponent))
		{
			if (componentsForData[i]->getStruct()->backgroundIndex != -1)
			{
				newComponent = new GunDraw(componentsForData[i]->getStruct(), components[componentsForData[i]->getStruct()->backgroundIndex]);
			}
			else
			{
				newComponent = new GunDraw(componentsForData[i]->getStruct());
			}
		}

		components.push_back(newComponent);
	}
}

void Graphic::setInformation(Tank &tank)
{
	needTank = true;

	tankDraw = new TankDraw();

	tankTexture = new Texture;

	tankSprite = new Sprite;
}


void Graphic::drawWindow()
{
	textureForWindow->display();
	
	Sprite spriteForWindow;
	spriteForWindow.setTexture(textureForWindow->getTexture());
	window->draw(spriteForWindow);
	window->display();
	window->clear(Color(50, 100, 50));

	textureForWindow->clear(Color(50, 100, 50));
}


void Graphic::drawPrivate()
{
	if (needNotificationWindow)
	{
		textureForWindow->draw(*windowBackgroundSprite);
		textureForWindow->draw(*formSprite);
	}

	if (needBackground)
	{
		textureForWindow->draw(*backgroundSprite);
	}

	for (int i = 0; i < numberOfTextDraw; ++i)
	{
		textureForWindow->draw(textDraw[i]);
	}
}

void Graphic::drawPrivate(Button *button)
{
	for (int i = 0; i < numberOfButtonDraw; ++i)
	{
		buttonDraw[i].drawButton(*textureForWindow, *button[i].getStruct());
	}
}

void Graphic::drawPrivate(string &inputField)
{
	notificationText->setString(inputField);
	notificationText->setOrigin(notificationText->getLocalBounds().width * 0.5f, notificationText->getOrigin().y);
	textureForWindow->draw(*notificationText);
}

void Graphic::drawPrivate(vector<Object *> &objects, long timer)
{
	objectDraw(*textureForWindow, timer, objects, components);
}

void Graphic::drawPrivate(Tank &tank, long timer)
{
	RenderTexture *renderTextureForTank = new RenderTexture;
	renderTextureForTank->create(tank.getDimension(), tank.getDimension());
	renderTextureForTank->clear(Color(0, 0, 0, 0));

	tankDraw->draw(*renderTextureForTank, timer, tank, components);

	renderTextureForTank->display();

	delete tankTexture;
	tankTexture = new Texture(renderTextureForTank->getTexture());

	delete renderTextureForTank;

	tankSprite->setTexture(*tankTexture);
	tankSprite->setPosition(float(tank.getOffset().x), float(tank.getOffset().y));

	textureForWindow->draw(*tankSprite);
}


void Graphic::draw(Button *button)
{
	drawInRenderTexture(button);

	drawWindow();
}

void Graphic::draw(Button *button, Tank &tank, long timer)
{
	drawInRenderTexture(button, tank, timer);

	drawWindow();
}

void Graphic::draw(Button *button, vector<Object *> &objects, long timer)
{
	drawInRenderTexture(button, objects, timer);

	drawWindow();
}

void Graphic::draw(Button *button, string &inputField)
{
	drawInRenderTexture(button, inputField);

	drawWindow();
}

void Graphic::draw(Button *button, string &inputField, Tank &tank, long timer)
{
	drawInRenderTexture(button, inputField, tank, timer);

	drawWindow();
}

void Graphic::draw(Button *button, string &inputField, vector<Object *> &objects, long timer)
{
	drawInRenderTexture(button, inputField, objects, timer);

	drawWindow();
}


void Graphic::drawInRenderTexture(Button *button)
{
	drawPrivate();
	drawPrivate(button);
}

void Graphic::drawInRenderTexture(Button *button, Tank &tank, long timer)
{
	drawInRenderTexture(button);

	drawPrivate(tank, timer);
}

void Graphic::drawInRenderTexture(Button *button, vector<Object *> &objects, long timer)
{
	drawInRenderTexture(button);

	drawPrivate(objects, timer);
}

void Graphic::drawInRenderTexture(Button *button, string &inputField)
{
	drawInRenderTexture(button);

	drawPrivate(inputField);
}

void Graphic::drawInRenderTexture(Button *button, string &inputField, Tank &tank, long timer)
{
	drawInRenderTexture(button, inputField);

	drawPrivate(tank, timer);
}

void Graphic::drawInRenderTexture(Button *button, string &inputField, vector<Object *> &objects, long timer)
{
	drawInRenderTexture(button, inputField);

	drawPrivate(objects, timer);
}


long Graphic::getTimeAsMilliseconds()
{
	return globalTimer.getElapsedTime().asMilliseconds();
}

long long Graphic::getTimeAsMicroseconds()
{
	return globalTimer.getElapsedTime().asMicroseconds();
}

RenderWindow *Graphic::getWindow()
{
	return window;
}

RenderTexture *Graphic::getRenderTexture()
{
	return textureForWindow;
}

bool Graphic::isOpen()
{
	if (window == nullptr)
	{
		return false;
	}
	return true;
}

void Graphic::close()
{
	window->close();
	delete window;
	window = nullptr;
}

bool Graphic::pollEvent()
{
	return window->pollEvent(event);
}

Event Graphic::getEvent()
{
	return event;
}

bool Graphic::hasFocus()
{
	return window->hasFocus();
}

Vector2int Graphic::getPositionOfMouse()
{
	return convert(Mouse::getPosition(*window));
}