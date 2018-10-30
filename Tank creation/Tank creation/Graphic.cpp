#include "Graphic.h"


void Graphic::forConstructor()
{
	textureForWindow.create(screanWidth, screanHeight);
	textureForWindow.clear(Color(50, 100, 50));

	numberOfButtonDraw = 0;
	numberOfTextDraw = 0;
	needBackground = false;
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


void Graphic::drawWindow()
{
	textureForWindow.display();
	
	Sprite spriteForWindow;
	spriteForWindow.setTexture(textureForWindow.getTexture());
	window->draw(spriteForWindow);
	window->display();
	window->clear(Color(50, 100, 50));

	textureForWindow.clear(Color(50, 100, 50));
}


void Graphic::drawPrivate()
{
	if (needBackground)
	{
		textureForWindow.draw(*backgroundSprite);
	}

	for (int i = 0; i < numberOfTextDraw; ++i)
	{
		textureForWindow.draw(textDraw[i]);
	}
}

void Graphic::drawPrivate(Button *button)
{
	for (int i = 0; i < numberOfButtonDraw; ++i)
	{
		buttonDraw[i].drawButton(textureForWindow, *button[i].getStruct());
	}
}


void Graphic::draw(Button *button)
{
	drawPrivate();
	drawPrivate(button);

	drawWindow();
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

Vector2int Graphic::getPositionOfMouse()
{
	return convert(Mouse::getPosition(*window));
}