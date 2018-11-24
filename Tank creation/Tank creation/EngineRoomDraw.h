#pragma once


#include "ComponentDraw.h"
#include "EngineRoom.h"


class EngineRoomDraw : public ComponentDraw
{
	Texture *backgroundTexture;
	Sprite *backgroundSprite;
	int numberOfVariantBackground;

	Texture *roomTexture;
	Sprite *roomSprite;
	int numberOfVariantRoom;

	Texture *personWorksTexture;
	Sprite *personWorksSprite;
	int numberOfVariantPerson;
	
	int xOffsetForRoom,
		yOffsetForRoom;
	int xOffsetForPerson,
		yOffsetForPerson;

public:
	EngineRoomDraw(ComponentParameter *component);

	~EngineRoomDraw();

	void draw(RenderTexture &renderTexture, long timer, ViewableObject *object, int compulsoryDrawing = false);
};