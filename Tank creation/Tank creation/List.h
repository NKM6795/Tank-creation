#pragma once


#include "TankEditor.h"
#include "Button.h"


class List
{
	bool open;

	bool needClose;

	long timerForInformation;

	string fileName;

	vector<ViewableObject *> objects;

	int objectWidth,
		objectHeight;
	int fragmentHeight;

	int width,
		height;
	int xCoordinate,
		yCoordinate;

	int index;
	int position;
	float conversionFactor;

	bool needButton;
	Button *button;
	int deltaPosition;

	int separationThickness;

	bool needDirect;
	bool up;

	bool needInformation;

	bool mouseButtonIsPressed;

	Vector2int oldMousePosition;

	void updateViewableObject();

public:
	List(vector<ViewableObject *> objects, int width, int height, int xCoordinate, int yCoordinate, int objectWidth = 60, int objectHeight = 40, int fragmentHeight = 50, int separationThickness = 1);

	~List();

	bool isOpen();
	void openList(Vector2int mousePosition);
	void closeList();

	void setNeedClose();

	bool inFocuse(Vector2int mousePosition);

	bool canAddElement(bool isPressed);

	string getFileName();
	void setFileName(string fileName);

	int getIndex();

	int getPosition();

	Button *getButton();

	vector<ViewableObject *> &getViewableObjects();

	vector<ViewableObject *> getSelectedViewableObject();

	void copyViewableObject(ViewableObject *object);

	Vector2int getOffset();
	void setOffset(Vector2int offset);
	void setOffset(int x, int y);

	void setDirect(bool up);

	int getFragmentHeight();

	int getWidth();
	int getHeight();

	int getViewableObjectWidth();
	int getViewableObjectHeight();

	bool getNeedInformation();

	void work(Vector2int mousePosition, bool isPressed, long timer, int fps, bool rightIsPressed = false);
};