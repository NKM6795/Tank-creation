#include "WorkWithBullet.h"


void workWithBullet(vector<ViewableObject *> &objects, int bulletPositionInObjects, Vector2int globalOffset, int screanWidth, long timer, long fps)
{
	for (int i = bulletPositionInObjects; i < int(objects.size()); ++i)
	{
		if (getLength(objects[i]->getBulletPosition(), objects[i]->getBulletPosition(true)) > float(screanWidth))
		{
			delete objects[i];
			objects[i] = nullptr;
		}
		else if (timer - objects[i]->timerForObject >= fps)
		{
			objects[i]->timerForObject += fps;

			if (objects[i]->getFather()->getComponentParameter()->horizontally)
			{
				Vector2float deltaPositon(-1.f * objects[i]->speed * sin(objects[i]->tiltAngle * PI / 180.f), objects[i]->speed * cos(objects[i]->tiltAngle * PI / 180.f));
				objects[i]->setBulletPosition(objects[i]->getBulletPosition() - deltaPositon);
			}


			objects[i]->setPosition(objects[i]->getBulletPosition() + globalOffset);
		}
	}

	objects.erase(remove_if(objects.begin(), objects.end(), [](ViewableObject *object) { return object == nullptr; }), objects.end());
}