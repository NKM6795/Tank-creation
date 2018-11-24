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

	if (needTank)
	{
		delete tankDraw;

		delete tankSprite;

		delete renderTextureForTank;

		delete renderTextureForGunsForTank;
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

	if (numberOfTextDraw > 0)
	{
		maxCharacterSize = characterSize[0];
	}

	for (int i = 0; i < numberOfTextDraw; ++i)
	{
		font[i].loadFromFile(fontName[i]);

		textDraw[i].setFont(font[i]);
		textDraw[i].setString(text[i]);
		textDraw[i].setCharacterSize(characterSize[i]);
		textDraw[i].setFillColor(Color::White);
		textDraw[i].setOrigin(textDraw[i].getLocalBounds().width * 0.5f, textDraw[i].getLocalBounds().height * 0.5f);
		textDraw[i].setPosition(float(xCoordinate[i]), float(yCoordinate[i]));
		
		if (numberOfTextDraw > 0)
		{
			maxCharacterSize = max(maxCharacterSize, characterSize[i]);
		}
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

void Graphic::setInformation(Tank &tank)
{
	needTank = true;

	tankDraw = new TankDraw();

	tankSprite = new Sprite;

	renderTextureForTank = new RenderTexture;
	renderTextureForTank->create(tank.getDimension(), tank.getDimension());
	renderTextureForTank->clear(Color(0, 0, 0, 0));

	needHighlight = false;
	renderTextureForGunsForTank = new RenderTexture;
	renderTextureForGunsForTank->create(tank.getDimension(), tank.getDimension());
	renderTextureForGunsForTank->clear(Color(0, 0, 0, 0));
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

		for (int i = 1; i < numberOfButtonDraw; ++i)
		{
			maxWidth = max(maxWidth, buttonDraw[i].getSprite()->getLocalBounds().width);
		}

		for (int i = 0; i < numberOfTextDraw; ++i)
		{
			textDraw[i].setString(text[i]);
			
			textDraw[i].setCharacterSize(maxCharacterSize);
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

void Graphic::drawPrivate(Tank &tank, long timer, bool highlight, bool needUpdateRender)
{
	if (needUpdateRender)
	{
		renderTextureForTank->clear(Color(0, 0, 0, 0));

		tankDraw->draw(*renderTextureForTank, timer, tank, components, 1);
	}
	else
	{
		tankDraw->draw(*renderTextureForTank, timer, tank, components);
	}

	renderTextureForTank->display();

	tankSprite->setTexture(renderTextureForTank->getTexture());
	tankSprite->setPosition(float(tank.getOffset().x), float(tank.getOffset().y));

	textureForWindow->draw(*tankSprite);

	if (highlight)
	{
		renderTextureForGunsForTank->clear(Color(0, 0, 0, 0));

		tankDraw->draw(*renderTextureForGunsForTank, timer, tank, components, -1);

		renderTextureForGunsForTank->display();

		tankSprite->setTexture(renderTextureForGunsForTank->getTexture());
		tankSprite->setPosition(float(tank.getOffset().x), float(tank.getOffset().y));

		textureForWindow->draw(*tankSprite);
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

void Graphic::draw(map<string, Button> &button, vector<ViewableObject *> &backgrounds, bool needUpdateBackground, vector<ViewableObject *> &bullets, Tank &tank, bool highlight, bool needUpdateRender, vector<ViewableObject *> &highlights, bool needUpdateHighlights, long timer)
{
	drawInRenderTexture(button, backgrounds, needUpdateBackground, bullets, tank, highlight, needUpdateRender, highlights, needUpdateHighlights, timer);

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

void Graphic::drawInRenderTexture(map<string, Button> &button, vector<ViewableObject *> &backgrounds, bool needUpdateBackground, vector<ViewableObject *> &bullets, Tank &tank, bool highlight, bool needUpdateRender, vector<ViewableObject *> &highlights, bool needUpdateHighlights, long timer)
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
	
	drawPrivate(tank, timer, highlight, needUpdateRender);

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
	tankDraw->save(fileName, timer, tank, components);
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