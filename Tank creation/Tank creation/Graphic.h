#pragma once


#include "ButtonDraw.h"


class Graphic
{
	Clock globalTimer;
	Event event;

	int screanWidth;
	int screanHeight;
	RenderWindow *window;
	RenderTexture textureForWindow;

	int numberOfButtonDraw;
	ButtonDraw *buttonDraw;
	
	int numberOfTextDraw;
	Text *textDraw;
	Font *font;

	
	int sizeOfDateArrayDraw;
	
	void forConstructor();


	void drawWindow();


	void drawPrivate();

	void drawPrivate(Button *button);

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


	void draw(Button *button);
	

	long getTimeAsMilliseconds();

	long long getTimeAsMicroseconds();

	RenderWindow *getWindow();

	bool isOpen();

	void close();

	bool pollEvent();

	Event getEvent();

	Vector2int getPositionOfMouse();
};