#pragma once


#include "ButtonDraw.h"
#include "GraphicForNotificationWindow.h"


class Graphic
{
	Clock globalTimer;
	Event event;

	int screanWidth;
	int screanHeight;
	RenderWindow *window;
	RenderTexture *textureForWindow;

	int numberOfButtonDraw;
	ButtonDraw *buttonDraw;
	
	int numberOfTextDraw;
	Text *textDraw;
	Font *font;

	bool needBackground;
	Texture *backgroundTexture;
	Sprite *backgroundSprite;


	bool needNotificationWindow;
	Texture *windowBackgroundTexture;
	Sprite *windowBackgroundSprite;
	Texture *formTexture;
	Sprite *formSprite;
	bool notificationNeedInputField;
	Text *notificationText;
	Font *notificationFont;

	
	int sizeOfDateArrayDraw;
	
	void forConstructor();


	void drawWindow();


	void drawPrivate();

	void drawPrivate(Button *button);

	void drawPrivate(string &inputField);

public:
	Graphic(int screanWidth, int screanHeight) : screanWidth(screanWidth), screanHeight(screanHeight)
	{
		window = new RenderWindow(VideoMode(screanWidth, screanHeight), "Tank creation", Style::None);

		forConstructor();
	}

	Graphic(RenderWindow *windowForCopy);

	~Graphic();


	void setInformation(int numberOfButton, Button *button);

	void setInformation(int numberOfText, string *text, string *fontName, int *characterSize, int *xCoordinate, int *yCoordinate);

	void setInformation(int xCoordinate, int yCoordinate, int width, int height, string fileName);

	void setInformation(int width, int height, bool needInputField, int xCoordinate, int yCoordinate, int characterSize, string fontName, RenderTexture *renderTextureForBackground);


	void draw(Button *button);

	void draw(Button *button, string &inputField);
	

	void drawInRenderTexture(Button *button);

	void drawInRenderTexture(Button *button, string &inputField);


	long getTimeAsMilliseconds();

	long long getTimeAsMicroseconds();

	RenderWindow *getWindow();

	RenderTexture *getRenderTexture();

	bool isOpen();

	void close();

	bool pollEvent();

	Event getEvent();

	Vector2int getPositionOfMouse();
};