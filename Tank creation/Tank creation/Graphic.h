#pragma once


#include "ButtonDraw.h"
#include "GraphicForNotificationWindow.h"
#include "TankDraw.h"
#include "ListDraw.h"


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
	
	int maxCharacterSize;
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
	
	bool needViewableObject;
	vector<ComponentDraw *> components;

	bool needTank;
	TankDraw *tankDraw;
	Texture *tankTexture;
	Sprite *tankSprite;

	bool needList;
	ListDraw *listDraw;
	Texture *listTexture;
	Sprite *listSprite;

	void forConstructor();

	void drawWindow();
	
	void drawPrivate();
	void drawPrivate(string *text);
	void drawPrivate(Button *button);
	void drawPrivate(string &inputField);
	void drawPrivate(vector<ViewableObject *> &objects, long timer);
	void drawPrivate(Tank &tank, long timer);
	void drawPrivate(List &list, long timer);

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
	void setInformation(vector<Component *> &componentsForData);
	void setInformation(Tank &tank);
	void setInformation(List &list);

	void draw(Button *button);
	void draw(Button *button, List &list, long timer);
	void draw(Button *button, Tank &tank, long timer);
	void draw(Button *button, vector<ViewableObject *> &objects, long timer);
	void draw(Button *button, vector<ViewableObject *> &objects, Tank &tank, long timer);
	void draw(Button *button, vector<ViewableObject *> &objects, Tank &tank, List &list, long timer);
	void draw(Button *button, string &inputField);
	void draw(Button *button, string &inputField, Tank &tank, long timer);
	void draw(Button *button, string &inputField, vector<ViewableObject *> &objects, long timer);
	void draw(Button *button, string &inputField, vector<ViewableObject *> &objects, Tank &tank, long timer);
	void draw(string *text, Button *button);
	void draw(string *text, Button *button, List &list, long timer);
	void draw(string *text, Button *button, Tank &tank, long timer);
	void draw(string *text, Button *button, vector<ViewableObject *> &objects, long timer);
	void draw(string *text, Button *button, vector<ViewableObject *> &objects, Tank &tank, long timer);
	void draw(string *text, Button *button, vector<ViewableObject *> &objects, Tank &tank, List &list, long timer);

	void drawInRenderTexture(Button *button);
	void drawInRenderTexture(Button *button, List &list, long timer);
	void drawInRenderTexture(Button *button, Tank &tank, long timer);
	void drawInRenderTexture(Button *button, vector<ViewableObject *> &objects, long timer);
	void drawInRenderTexture(Button *button, vector<ViewableObject *> &objects, Tank &tank, long timer);
	void drawInRenderTexture(Button *button, vector<ViewableObject *> &objects, Tank &tank, List &list, long timer);
	void drawInRenderTexture(Button *button, string &inputField);
	void drawInRenderTexture(Button *button, string &inputField, Tank &tank, long timer);
	void drawInRenderTexture(Button *button, string &inputField, vector<ViewableObject *> &objects, long timer);
	void drawInRenderTexture(Button *button, string &inputField, vector<ViewableObject *> &objects, Tank &tank, long timer);
	void drawInRenderTexture(string *text, Button *button);
	void drawInRenderTexture(string *text, Button *button, List &list, long timer);
	void drawInRenderTexture(string *text, Button *button, Tank &tank, long timer);
	void drawInRenderTexture(string *text, Button *button, vector<ViewableObject *> &objects, long timer);
	void drawInRenderTexture(string *text, Button *button, vector<ViewableObject *> &objects, Tank &tank, long timer);
	void drawInRenderTexture(string *text, Button *button, vector<ViewableObject *> &objects, Tank &tank, List &list, long timer);

	void saveTank(string fileName, Tank &tank, long timer);

	long getTimeAsMilliseconds();
	long long getTimeAsMicroseconds();

	RenderWindow *getWindow();
	RenderTexture *getRenderTexture();

	bool isOpen();
	void close();

	bool pollEvent();
	Event getEvent();

	bool hasFocus();

	Vector2int getPositionOfMouse();
};