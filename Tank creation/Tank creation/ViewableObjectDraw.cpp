#include "ViewableObjectDraw.h"


void objectDraw(RenderTexture &renderTexture, long timer, vector<ViewableObject *> &objects, vector<ComponentDraw *> &components, int compulsoryDrawing)
{
	int number = int(objects.size());

	for (int i = 0; i < number; ++i)
	{
		if (objects[i] != nullptr && typeid(*objects[i]) != typeid(AdditionToBigBlock) && typeid(*objects[i]) != typeid(AdditionToEngineRoom) && typeid(*objects[i]) != typeid(AdditionToGun) && typeid(*objects[i]) != typeid(AdditionToTrack))
		{
			int j = objects[i]->getIndex();

			components[j]->draw(renderTexture, timer, objects[i], compulsoryDrawing);
		}
	}
}