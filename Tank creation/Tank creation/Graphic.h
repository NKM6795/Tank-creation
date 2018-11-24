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

	bool firstDraw;
	bool needSpritesForRender;
	RenderTexture *renderTextureForBackground;
	RenderTexture *renderTextureForHighlighte;
	Sprite *spriteForRenderBackground;
	Sprite *spriteForRenderHighlighte;

	bool needTank;
	TankDraw *tankDraw;
	RenderTexture *renderTextureForTank;
	bool needHighlight;
	RenderTexture *renderTextureForGunsForTank;
	Sprite *tankSprite;

	bool needList;
	ListDraw *listDraw;
	RenderTexture *renderTextureForList;
	Sprite *listSprite;

	void forConstructor();

	void drawWindow();
	
	void drawPrivate();
	void drawPrivate(string *text);
	void drawPrivate(map<string, Button> &button);
	void drawPrivate(string &inputField);
	void drawPrivate(vector<ViewableObject *> &objects, long timer);
	void drawPrivate(vector<ViewableObject *> &objects, long timer, int needUpdate);
	void drawPrivate(Tank &tank, long timer, bool highlight = false, bool needUpdateRender = false);
	void drawPrivate(List &list, long timer);

public:
	Graphic(int screanWidth, int screanHeight) : screanWidth(screanWidth), screanHeight(screanHeight)
	{
		window = new RenderWindow(VideoMode(screanWidth, screanHeight), "Tank creation", Style::None);

		forConstructor();
	}
	Graphic(RenderWindow *windowForCopy);

	~Graphic();

	void setInformation(int numberOfButton, map<string, Button> &button);
	void setInformation(int numberOfText, string *text, string *fontName, int *characterSize, int *xCoordinate, int *yCoordinate);
	void setInformation(int xCoordinate, int yCoordinate, int width, int height, string fileName);
	void setInformation(int width, int height, bool needInputField, int xCoordinate, int yCoordinate, int characterSize, string fontName, RenderTexture *renderTextureForBackground);
	void setInformation(vector<Component *> &componentsForData);
	void setInformation(Tank &tank);
	void setInformation(List &list);
	void setInformation(int screanWidth, int screanHeight);

	void draw(map<string, Button> &button);
	void draw(map<string, Button> &button, List &list, long timer);
	void draw(map<string, Button> &button, Tank &tank, long timer);
	void draw(map<string, Button> &button, vector<ViewableObject *> &objects, long timer);
	void draw(map<string, Button> &button, vector<ViewableObject *> &objects, Tank &tank, long timer);
	void draw(map<string, Button> &button, vector<ViewableObject *> &backgrounds, bool needUpdateBackground, vector<ViewableObject *> &bullets, Tank &tank, bool highlight, bool needUpdateRender, vector<ViewableObject *> &highlights, bool needUpdateHighlights, long timer);
	void draw(map<string, Button> &button, vector<ViewableObject *> &objects, Tank &tank, List &list, long timer);
	void draw(map<string, Button> &button, string &inputField);
	void draw(map<string, Button> &button, string &inputField, Tank &tank, long timer);
	void draw(map<string, Button> &button, string &inputField, vector<ViewableObject *> &objects, long timer);
	void draw(map<string, Button> &button, string &inputField, vector<ViewableObject *> &objects, Tank &tank, long timer);
	void draw(string *text, map<string, Button> &button);
	void draw(string *text, map<string, Button> &button, List &list, long timer);
	void draw(string *text, map<string, Button> &button, Tank &tank, long timer);
	void draw(string *text, map<string, Button> &button, vector<ViewableObject *> &objects, long timer);
	void draw(string *text, map<string, Button> &button, vector<ViewableObject *> &objects, Tank &tank, long timer);
	void draw(string *text, map<string, Button> &button, vector<ViewableObject *> &objects, Tank &tank, bool needUpdateRender, List &list, long timer);

	void drawInRenderTexture(map<string, Button> &button);
	void drawInRenderTexture(map<string, Button> &button, List &list, long timer);
	void drawInRenderTexture(map<string, Button> &button, Tank &tank, long timer);
	void drawInRenderTexture(map<string, Button> &button, vector<ViewableObject *> &objects, long timer);
	void drawInRenderTexture(map<string, Button> &button, vector<ViewableObject *> &objects, Tank &tank, long timer);
	void drawInRenderTexture(map<string, Button> &button, vector<ViewableObject *> &backgrounds, bool needUpdateBackground, vector<ViewableObject *> &bullets, Tank &tank, bool highlight, bool needUpdateRender, vector<ViewableObject *> &highlights, bool needUpdateHighlights, long timer);
	void drawInRenderTexture(map<string, Button> &button, vector<ViewableObject *> &objects, Tank &tank, List &list, long timer);
	void drawInRenderTexture(map<string, Button> &button, string &inputField);
	void drawInRenderTexture(map<string, Button> &button, string &inputField, Tank &tank, long timer);
	void drawInRenderTexture(map<string, Button> &button, string &inputField, vector<ViewableObject *> &objects, long timer);
	void drawInRenderTexture(map<string, Button> &button, string &inputField, vector<ViewableObject *> &objects, Tank &tank, long timer);
	void drawInRenderTexture(string *text, map<string, Button> &button);
	void drawInRenderTexture(string *text, map<string, Button> &button, List &list, long timer);
	void drawInRenderTexture(string *text, map<string, Button> &button, Tank &tank, long timer);
	void drawInRenderTexture(string *text, map<string, Button> &button, vector<ViewableObject *> &objects, long timer);
	void drawInRenderTexture(string *text, map<string, Button> &button, vector<ViewableObject *> &objects, Tank &tank, bool needUpdateRender, long timer);
	void drawInRenderTexture(string *text, map<string, Button> &button, vector<ViewableObject *> &objects, Tank &tank, bool needUpdateRender, List &list, long timer);

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