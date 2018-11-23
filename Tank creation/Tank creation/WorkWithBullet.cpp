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
		else
		{
			float time = float(timer - objects[i]->timerForObject) / 200.f;
			Vector2float newPosition(objects[i]->getBulletPosition(true).x + float(time) * objects[i]->speed * sin(objects[i]->tiltAngle * PI / 180.f), objects[i]->getBulletPosition(true).y - float(time) * objects[i]->speed * cos(objects[i]->tiltAngle * PI / 180.f));

			if (!objects[i]->getFather()->getComponentParameter()->horizontally)
			{
				newPosition.y = objects[i]->getBulletPosition(true).y + GRAVITY * 0.5f * time * time - objects[i]->speed * time * cos(objects[i]->tiltAngle * PI / 180.f);
			}

			objects[i]->setBulletPosition(newPosition);

			objects[i]->setPosition(objects[i]->getBulletPosition() + globalOffset);
		}
	}

	objects.erase(remove_if(objects.begin(), objects.end(), [](ViewableObject *object) { return object == nullptr; }), objects.end());
}