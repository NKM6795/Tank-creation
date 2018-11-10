#include "BackgroundDraw.h"


BackgroundDraw::BackgroundDraw(ComponentParameter *component)
{
	numberOfVariant = component->numberOfVariant;

	backgroundTexture = new Texture[numberOfVariant];
	backgroundSprite = new Sprite[numberOfVariant];

	for (int i = 0; i < numberOfVariant; ++i)
	{
		string fileName = component->objectName + component->typeName + component->identifierName + to_string(i + 1);

		backgroundTexture[i].loadFromFile(fileName);
		
		backgroundSprite[i].setTexture(backgroundTexture[i]);
	}
}

BackgroundDraw::~BackgroundDraw()
{
	delete[] backgroundSprite;
	
	delete[] backgroundTexture;
}


void BackgroundDraw::draw(RenderTexture &renderTexture, long timer, Object *object)
{

}
