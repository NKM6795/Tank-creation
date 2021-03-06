#include "Graphic.h"


void Graphic::forConstructor()
{
	textureForWindow = new RenderTexture;
	textureForWindow->create(screanWidth, screanHeight);
	textureForWindow->clear(Color(119, 107, 76));

	numberOfButtonDraw = 0;
	numberOfTextDraw = 0;
	needBackground = false;
	needNotificationWindow = false;
	notificationNeedInputField = false;
	needList = false;

	firstDraw = true;
	needSpritesForRender = false;
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

	if (needViewableObject)
	{
		int number = int(components.size());

		for (int i = 0; i < number; ++i)
		{
			delete components.back();

			components.pop_back();
		}
	}

	if (needLeftTank)
	{
		delete leftTankDraw;

		delete leftTankSprite;

		delete renderTextureForLeftTank;

		delete renderTextureForGunsForLeftTank;
	}

	if (needRightTank)
	{
		delete rightTankDraw;

		delete rightTankSprite;

		delete renderTextureForRightTank;

		delete renderTextureForGunsForRightTank;
	}

	if (needList)
	{
		delete listDraw;

		delete listSprite;

		delete renderTextureForList;
	}

	if (needSpritesForRender)
	{
		delete renderTextureForBackground;
		delete renderTextureForHighlighte;
		delete spriteForRenderBackground;
		delete spriteForRenderHighlighte;
	}
}


void Graphic::setInformation(int countOfButton, map<string, Button> &button)
{
	numberOfButtonDraw = countOfButton;
	buttonDraw = new ButtonDraw[numberOfButtonDraw];

	int i = 0;
	for (auto j = button.begin(); j != button.end(); ++j, ++i)
	{
		buttonDraw[i].setInformation(*j->second.getStruct());
	}
}

void Graphic::setInformation(int countOfText, string *text, string *fontName, int *characterSize, int *xCoordinate, int *yCoordinate)
{
	numberOfTextDraw = countOfText;
	textDraw = new Text[numberOfTextDraw];
	font = new Font[numberOfTextDraw];

	for (int i = 0; i < numberOfTextDraw; ++i)
	{
		maxCharacterSize.push_back(characterSize[i]);

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

	renderTextureForBackground->clear(Color(119, 107, 76));

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
	if (needViewableObject)
	{
		int number = int(components.size());

		for (int i = 0; i < number; ++i)
		{
			delete components.back();

			components.pop_back();
		}
	}

	needViewableObject = true;

	int number = int(componentsForData.size());

	for (int i = 0; i < number; ++i)
	{
		ComponentDraw *newComponent;
		if (typeid(*componentsForData[i]) == typeid(BackgroundComponent))
		{
			newComponent = new BackgroundDraw(componentsForData[i]->getStruct());
		}
		else if (typeid(*componentsForData[i]) == typeid(BackgroundForBattleComponent))
		{
			newComponent = new BackgroundForBattleDraw(componentsForData[i]->getStruct());
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
		else if (typeid(*componentsForData[i]) == typeid(TankPictureComponent))
		{
			newComponent = new TankPictureDraw(componentsForData[i]->getStruct());
		}
		else if (typeid(*componentsForData[i]) == typeid(SpeedometerComponent))
		{
			newComponent = new SpeedometerDraw(componentsForData[i]->getStruct());
		}
		else if (typeid(*componentsForData[i]) == typeid(AllotmentComponent))
		{
			newComponent = new AllotmentDraw(componentsForData[i]->getStruct());
		}
		else if (typeid(*componentsForData[i]) == typeid(BulletComponent))
		{
			newComponent = new BulletDraw(componentsForData[i]->getStruct());
		}

		components.push_back(newComponent);
	}
}

void Graphic::setInformation(Tank &tank, bool left)
{
	if (left)
	{
		needLeftTank = true;

		leftTankDraw = new TankDraw();

		leftTankSprite = new Sprite;

		renderTextureForLeftTank = new RenderTexture;
		renderTextureForLeftTank->create(tank.getDimension(), tank.getDimension());
		renderTextureForLeftTank->clear(Color(0, 0, 0, 0));

		needHighlightLeftTank = false;
		renderTextureForGunsForLeftTank = new RenderTexture;
		renderTextureForGunsForLeftTank->create(tank.getDimension(), tank.getDimension());
		renderTextureForGunsForLeftTank->clear(Color(0, 0, 0, 0));
	}
	else
	{
		needRightTank = true;

		rightTankDraw = new TankDraw();

		rightTankSprite = new Sprite;
		rightTankSprite->setOrigin(float(tank.getDimension()), 0.f);
		rightTankSprite->setScale(-1.f, 1.f);

		renderTextureForRightTank = new RenderTexture;
		renderTextureForRightTank->create(tank.getDimension(), tank.getDimension());
		renderTextureForRightTank->clear(Color(0, 0, 0, 0));

		needHighlightRightTank = false;
		renderTextureForGunsForRightTank = new RenderTexture;
		renderTextureForGunsForRightTank->create(tank.getDimension(), tank.getDimension());
		renderTextureForGunsForRightTank->clear(Color(0, 0, 0, 0));
	}
}

void Graphic::setInformation(List &list)
{
	if (needList)
	{
		delete listDraw;

		listDraw = new ListDraw(list, components);
	}
	else
	{
		needList = true;

		listDraw = new ListDraw(list, components);

		listSprite = new Sprite;

		renderTextureForList = new RenderTexture;
		renderTextureForList->create(list.getWidth(), list.getHeight());
	}
}

void Graphic::setInformation(int screanWidth, int screanHeight)
{
	needSpritesForRender = true;

	renderTextureForBackground = new RenderTexture;
	renderTextureForBackground->create(screanWidth, screanHeight);
	renderTextureForBackground->clear(Color(0, 0, 0, 0));

	spriteForRenderBackground = new Sprite;

	renderTextureForHighlighte = new RenderTexture;
	renderTextureForHighlighte->create(screanWidth, screanHeight);
	renderTextureForHighlighte->clear(Color(0, 0, 0, 0));
	renderTextureForHighlighte->display();

	spriteForRenderHighlighte = new Sprite;

	spriteForRenderHighlighte->setTexture(renderTextureForHighlighte->getTexture());
}


void Graphic::drawWindow()
{
	textureForWindow->display();
	
	Sprite spriteForWindow;
	spriteForWindow.setTexture(textureForWindow->getTexture());
	window->draw(spriteForWindow);
	window->display();
	window->clear(Color(119, 107, 76));

	textureForWindow->clear(Color(119, 107, 76));
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

void Graphic::drawPrivate(string *text)
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

	if (numberOfButtonDraw > 0)
	{
		float maxWidth = 300;


		for (int i = 0; i < numberOfTextDraw; ++i)
		{
			textDraw[i].setString(text[i]);
			
			textDraw[i].setCharacterSize(maxCharacterSize[i]);
			while (textDraw[i].getLocalBounds().width >= maxWidth)
			{
				textDraw[i].setCharacterSize(textDraw[i].getCharacterSize() - 1);
			}

			textDraw[i].setOrigin(textDraw[i].getLocalBounds().width * 0.5f, textDraw[i].getLocalBounds().height * 0.5f);

			textureForWindow->draw(textDraw[i]);
		}
	}
}

void Graphic::drawPrivate(map<string, Button> &button)
{
	int i = 0;
	for (auto j = button.begin(); j != button.end(); ++j, ++i)
	{
		buttonDraw[i].drawButton(*textureForWindow, *j->second.getStruct());
	}
}

void Graphic::drawPrivate(string &inputField)
{
	notificationText->setString(inputField);
	notificationText->setOrigin(notificationText->getLocalBounds().width * 0.5f, notificationText->getOrigin().y);
	textureForWindow->draw(*notificationText);
}

void Graphic::drawPrivate(vector<ViewableObject *> &objects, long timer)
{
	objectDraw(*textureForWindow, timer, objects, components);
}

void Graphic::drawPrivate(vector<ViewableObject *> &objects, long timer, int needUpdate)
{
	if (needUpdate == 1)
	{
		renderTextureForBackground->clear(Color(0, 0, 0, 0));

		objectDraw(*renderTextureForBackground, timer, objects, components);

		renderTextureForBackground->display();


		spriteForRenderBackground->setTexture(renderTextureForBackground->getTexture());

		textureForWindow->draw(*spriteForRenderBackground);
	}
	else if (needUpdate == -1)
	{
		textureForWindow->draw(*spriteForRenderBackground);
	}
	if (needUpdate == 2)
	{
		renderTextureForHighlighte->clear(Color(0, 0, 0, 0));

		objectDraw(*renderTextureForHighlighte, timer, objects, components);

		renderTextureForHighlighte->display();


		spriteForRenderHighlighte->setTexture(renderTextureForHighlighte->getTexture());

		textureForWindow->draw(*spriteForRenderHighlighte);
	}
	else if (needUpdate == -2)
	{
		textureForWindow->draw(*spriteForRenderHighlighte);
	}
}

void Graphic::drawPrivate(Tank &tank, long timer, bool highlight, bool needUpdateRender, bool left)
{
	if (left)
	{
		if (needUpdateRender)
		{
			renderTextureForLeftTank->clear(Color(0, 0, 0, 0));

			leftTankDraw->draw(*renderTextureForLeftTank, timer, tank, components, 1);
		}
		else
		{
			leftTankDraw->draw(*renderTextureForLeftTank, timer, tank, components);
		}

		renderTextureForLeftTank->display();

		leftTankSprite->setTexture(renderTextureForLeftTank->getTexture());
		leftTankSprite->setPosition(float(tank.getOffset().x), float(tank.getOffset().y));

		textureForWindow->draw(*leftTankSprite);

		if (highlight)
		{
			renderTextureForGunsForLeftTank->clear(Color(0, 0, 0, 0));

			leftTankDraw->draw(*renderTextureForGunsForLeftTank, timer, tank, components, -1);

			renderTextureForGunsForLeftTank->display();

			leftTankSprite->setTexture(renderTextureForGunsForLeftTank->getTexture());
			leftTankSprite->setPosition(float(tank.getOffset().x), float(tank.getOffset().y));

			textureForWindow->draw(*leftTankSprite);
		}
	}
	else
	{
		if (needUpdateRender)
		{
			renderTextureForRightTank->clear(Color(0, 0, 0, 0));

			rightTankDraw->draw(*renderTextureForRightTank, timer, tank, components, 1);
		}
		else
		{
			rightTankDraw->draw(*renderTextureForRightTank, timer, tank, components);
		}

		renderTextureForRightTank->display();

		rightTankSprite->setTexture(renderTextureForRightTank->getTexture());
		rightTankSprite->setPosition(float(tank.getOffset().x), float(tank.getOffset().y));

		textureForWindow->draw(*rightTankSprite);

		if (highlight)
		{
			renderTextureForGunsForRightTank->clear(Color(0, 0, 0, 0));

			rightTankDraw->draw(*renderTextureForGunsForRightTank, timer, tank, components, -1);

			renderTextureForGunsForRightTank->display();

			rightTankSprite->setTexture(renderTextureForGunsForRightTank->getTexture());
			rightTankSprite->setPosition(float(tank.getOffset().x), float(tank.getOffset().y));

			textureForWindow->draw(*rightTankSprite);
		}
	}
}

void Graphic::drawPrivate(List &list, long timer)
{
	listDraw->draw(*renderTextureForList, list, timer);
	renderTextureForList->display();
	
	listSprite->setTexture(renderTextureForList->getTexture());
	listSprite->setPosition(float(list.getOffset().x), float(list.getOffset().y));

	drawFramework(*textureForWindow, list.getOffset().x, list.getOffset().y, list.getOffset().x + list.getWidth(), list.getOffset().y + list.getHeight());
	textureForWindow->draw(*listSprite);
}


void Graphic::draw(map<string, Button> &button)
{
	drawInRenderTexture(button);

	drawWindow();
}

void Graphic::draw(map<string, Button> &button, List &list, long timer)
{
	drawInRenderTexture(button, list, timer);

	drawWindow();
}

void Graphic::draw(map<string, Button> &button, Tank &tank, long timer)
{
	drawInRenderTexture(button, tank, timer);

	drawWindow();
}

void Graphic::draw(map<string, Button> &button, vector<ViewableObject *> &objects, long timer)
{
	drawInRenderTexture(button, objects, timer);

	drawWindow();
}

void Graphic::draw(map<string, Button> &button, vector<ViewableObject *> &objects, Tank &tank, long timer)
{
	drawInRenderTexture(button, objects, tank, timer);

	drawWindow();
}

void Graphic::draw(map<string, Button> &button, vector<ViewableObject *> &backgrounds, bool needUpdateBackground, vector<ViewableObject *> &bullets, Tank &leftTank, Tank &rightTank, bool highlight, bool needUpdateRender, vector<ViewableObject *> &highlights, bool needUpdateHighlights, long timer)
{
	drawInRenderTexture(button, backgrounds, needUpdateBackground, bullets, leftTank, rightTank, highlight, needUpdateRender, highlights, needUpdateHighlights, timer);

	drawWindow();
}

void Graphic::draw(map<string, Button> &button, vector<ViewableObject *> &objects, Tank &tank, List &list, long timer)
{
	drawInRenderTexture(button, objects, tank, list, timer);

	drawWindow();
}

void Graphic::draw(map<string, Button> &button, string &inputField)
{
	drawInRenderTexture(button, inputField);

	drawWindow();
}

void Graphic::draw(map<string, Button> &button, string &inputField, Tank &tank, long timer)
{
	drawInRenderTexture(button, inputField, tank, timer);

	drawWindow();
}

void Graphic::draw(map<string, Button> &button, string &inputField, vector<ViewableObject *> &objects, long timer)
{
	drawInRenderTexture(button, inputField, objects, timer);

	drawWindow();
}

void Graphic::draw(map<string, Button> &button, string &inputField, vector<ViewableObject *> &objects, Tank &tank, long timer)
{
	drawInRenderTexture(button, inputField, objects, tank, timer);

	drawWindow();
}

void Graphic::draw(string *text, map<string, Button> &button)
{
	drawInRenderTexture(text, button);

	drawWindow();
}

void Graphic::draw(string *text, map<string, Button> &button, List &list, long timer)
{
	drawInRenderTexture(text, button, list, timer);

	drawWindow();
}

void Graphic::draw(string *text, map<string, Button> &button, Tank &tank, long timer)
{
	drawInRenderTexture(text, button, tank, timer);

	drawWindow();
}

void Graphic::draw(string *text, map<string, Button> &button, vector<ViewableObject *> &objects, long timer)
{
	drawInRenderTexture(text, button, objects, timer);

	drawWindow();
}

void Graphic::draw(string *text, map<string, Button> &button, vector<ViewableObject *> &objects, Tank &tank, long timer)
{
	drawInRenderTexture(text, button, objects, tank, false, timer);

	drawWindow();
}

void Graphic::draw(string *text, map<string, Button> &button, vector<ViewableObject *> &objects, Tank &tank, bool needUpdateRender, List &list, long timer)
{
	drawInRenderTexture(text, button, objects, tank, needUpdateRender, list, timer);

	drawWindow();
}


void Graphic::drawInRenderTexture(map<string, Button> &button)
{
	drawPrivate();
	drawPrivate(button);
}

void Graphic::drawInRenderTexture(map<string, Button> &button, List &list, long timer)
{
	drawInRenderTexture(button);

	drawPrivate(list, timer);
}

void Graphic::drawInRenderTexture(map<string, Button> &button, Tank &tank, long timer)
{
	drawInRenderTexture(button);

	drawPrivate(tank, timer);
}

void Graphic::drawInRenderTexture(map<string, Button> &button, vector<ViewableObject *> &objects, long timer)
{
	drawInRenderTexture(button);

	drawPrivate(objects, timer);
}

void Graphic::drawInRenderTexture(map<string, Button> &button, vector<ViewableObject *> &objects, Tank &tank, long timer)
{
	drawPrivate(objects, timer);

	drawPrivate(tank, timer);

	drawPrivate(button);
}

void Graphic::drawInRenderTexture(map<string, Button> &button, vector<ViewableObject *> &backgrounds, bool needUpdateBackground, vector<ViewableObject *> &bullets, Tank &leftTank, Tank &rightTank, bool highlight, bool needUpdateRender, vector<ViewableObject *> &highlights, bool needUpdateHighlights, long timer)
{
	drawPrivate(backgrounds, timer, needUpdateBackground || firstDraw ? 1 : -1);
	if (!needUpdateBackground)
	{
		firstDraw = true;
	}
	else
	{
		firstDraw = false;
	}

	drawPrivate(bullets, timer);
	
	drawPrivate(leftTank, timer, highlight, needUpdateRender);
	drawPrivate(rightTank, timer, true, needUpdateRender, false);

	drawPrivate(highlights, timer, needUpdateHighlights ? 2 : -2);

	drawPrivate(button);
}

void Graphic::drawInRenderTexture(map<string, Button> &button, vector<ViewableObject *> &objects, Tank &tank, List &list, long timer)
{
	drawInRenderTexture(button, objects, tank, timer);

	drawPrivate(list, timer);
}

void Graphic::drawInRenderTexture(map<string, Button> &button, string &inputField)
{
	drawInRenderTexture(button);

	drawPrivate(inputField);
}

void Graphic::drawInRenderTexture(map<string, Button> &button, string &inputField, Tank &tank, long timer)
{
	drawInRenderTexture(button, inputField);

	drawPrivate(tank, timer);
}

void Graphic::drawInRenderTexture(map<string, Button> &button, string &inputField, vector<ViewableObject *> &objects, long timer)
{
	drawInRenderTexture(button, inputField);

	drawPrivate(objects, timer);
}

void Graphic::drawInRenderTexture(map<string, Button> &button, string &inputField, vector<ViewableObject *> &objects, Tank &tank, long timer)
{
	drawInRenderTexture(button, inputField, objects, timer);

	drawPrivate(tank, timer);
}

void Graphic::drawInRenderTexture(string *text, map<string, Button> &button)
{
	drawPrivate(text);
	drawPrivate(button);
}

void Graphic::drawInRenderTexture(string *text, map<string, Button> &button, List &list, long timer)
{
	drawInRenderTexture(text, button);

	drawPrivate(list, timer);
}

void Graphic::drawInRenderTexture(string *text, map<string, Button> &button, Tank &tank, long timer)
{
	drawInRenderTexture(text, button);

	drawPrivate(tank, timer);
}

void Graphic::drawInRenderTexture(string *text, map<string, Button> &button, vector<ViewableObject *> &objects, long timer)
{
	drawInRenderTexture(text, button);

	drawPrivate(objects, timer);
}

void Graphic::drawInRenderTexture(string *text, map<string, Button> &button, vector<ViewableObject *> &objects, Tank &tank, bool needUpdateRender, long timer)
{
	drawInRenderTexture(text, button);

	drawPrivate(tank, timer, false, needUpdateRender);

	drawPrivate(objects, timer);
}

void Graphic::drawInRenderTexture(string *text, map<string, Button> &button, vector<ViewableObject *> &objects, Tank &tank, bool needUpdateRender, List &list, long timer)
{
	drawInRenderTexture(text, button, objects, tank, needUpdateRender, timer);

	drawPrivate(list, timer);
}


void Graphic::saveTank(string fileName, Tank &tank, long timer)
{
	leftTankDraw->save(fileName, timer, tank, components);
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