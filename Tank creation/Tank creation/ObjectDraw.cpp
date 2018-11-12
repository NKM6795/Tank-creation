#include "ObjectDraw.h"


void objectDraw(RenderTexture &renderTexture, long timer, vector<Object *> &objects, vector<ComponentDraw *> &components)
{
	int number = int(objects.size());

	for (int i = 0; i < number; ++i)
	{
		if (objects[i] != nullptr)
		{
			int j = objects[i]->getIndex();

			components[j]->draw(renderTexture, timer, objects[i]);
		}
	}
}