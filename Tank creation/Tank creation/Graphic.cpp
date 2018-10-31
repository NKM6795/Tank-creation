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

void Graphic::setInformation(int width, int height, bool needInputField, RenderTexture *renderTextureForBackground)
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


void Graphic::draw(Button *button)
{
	drawInRenderTexture(button);

	drawWindow();
}


void Graphic::drawInRenderTexture(Button *button)
{
	drawPrivate();
	drawPrivate(button);
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

Vector2int Graphic::getPositionOfMouse()
{
	return convert(Mouse::getPosition(*window));
}