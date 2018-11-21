#pragma once


#include "TankEditor.h"
#include "Button.h"


class List
{
	//Open and close list
	bool open;
	bool needClose;

	//Indexes and position
	int position;
	int searchEngineHeight;
	int index;
	int indexOfSelectedObject;
	int mainIndex;
	int mainIndexOfSelectedObject;
	bool needDirect;
	bool up;
	bool needSelect;
	int deltaPosition;
	int fragmentHeight;
	int width,
		height;
	int xCoordinate,
		yCoordinate;

	//Information
	bool needInformation;

	//Mouse
	bool mouseButtonIsPressed;
	long timerForDoubleClick;
	bool firstClick;
	Vector2int oldMousePosition;

	//Scrollbar
	bool needButton;
	Button *button;
	float conversionFactor;

	//Objects
	vector<ViewableObject *> mainObjects;
	vector<ViewableObject *> objects;
	string fileName;
	int objectWidth,
		objectHeight;
	int separationThickness;

	//Filter
	string inputField;
	int maxSizeOfText;

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
	int getIndexOfSelectedObject();
	int getMainIndex();
	int getMainIndexOfSelectedObject();

	int getPosition();

	bool getNeedButton();

	Button *getButton();

	vector<ViewableObject *> &getViewableObjects();
	vector<ViewableObject *> &getViewableMainObjects();

	vector<ViewableObject *> getHighlightedViewableObject();
	vector<ViewableObject *> getSelectedViewableObject();

	void copyViewableObject(ViewableObject *object);

	Vector2int getOffset();
	void setOffset(Vector2int offset);
	void setOffset(int x, int y);

	void setDirect(bool up);
	void select();

	int getFragmentHeight();

	int getWidth();
	int getHeight();

	int getViewableObjectWidth();
	int getViewableObjectHeight();

	int getSearchEngineHeight();

	string getInputField();

	void showInformation();
	bool getNeedInformation();

	void work(Vector2int mousePosition, bool isPressed, long timer, int fps, bool rightIsPressed = false);
	void workWithText(int unicode);
};