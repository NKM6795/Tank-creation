#include "WorkWithBullet.h"


void breakBullet(vector<Component *> &components, int bulletPositionInComponents, vector<ViewableObject *> &objects, int bulletPositionInObjects, int index, long timer, bool completely)
{
	if (!completely)
	{
		objects[index]->setHeath(objects[index]->getHealth() - 1);
		if (objects[index]->getHealth() == 0)
		{
			completely = true;
		}
		else
		{
			return;
		}
	}

	ViewableObject *bullet = objects[index],
		*father = bullet->getFather();

	vector<ViewableObject *> newObjects;

	if (bullet->getFather()->getComponentParameter()->indexOfComponents.size() == 1)
	{
		delete bullet;
		bullet = nullptr;
		objects[index] = nullptr;
	}
	else
	{
		int indexOfComponents = -1;
		for (int i = 0; i < int(father->getComponentParameter()->indexOfComponents.size()); ++i)
		{
			if (bullet->getIndex() == father->getComponentParameter()->indexOfComponents[i] + bulletPositionInComponents)
			{
				if (i == int(father->getComponentParameter()->indexOfComponents.size()) - 1)
				{
					indexOfComponents = -1;
				}
				else
				{
					indexOfComponents = father->getComponentParameter()->indexOfComponents[i + 1] + bulletPositionInComponents;
				}
			}
		}
		
		if (indexOfComponents != -1)
		{
			{
				ViewableObject *newBullet = new Bullet(components[indexOfComponents], indexOfComponents, father, 330.f, bullet->speed / 2.f, bullet->getBulletPosition(), timer);
				newBullet->damage = bullet->damage / 2;
				newBullet->canDoDamageToItself = true;

				newObjects.push_back(newBullet);
			}

			{
				ViewableObject *newBullet = new Bullet(components[indexOfComponents], indexOfComponents, father, 0.f, bullet->speed / 2.f, bullet->getBulletPosition(), timer);
				newBullet->damage = bullet->damage / 2;
				newBullet->canDoDamageToItself = true;

				newObjects.push_back(newBullet);
			}
			
			{
				ViewableObject *newBullet = new Bullet(components[indexOfComponents], indexOfComponents, father, 30.f, bullet->speed / 2.f, bullet->getBulletPosition(), timer);
				newBullet->damage = bullet->damage / 2;
				newBullet->canDoDamageToItself = true;

				newObjects.push_back(newBullet);
			}
		}

		delete bullet;
		bullet = nullptr;
		objects[index] = nullptr;
	}

	objects.erase(remove_if(objects.begin(), objects.end(), [](ViewableObject *object) { return object == nullptr; }), objects.end());

	if (newObjects.size() != 0)
	{
		objects.insert(objects.end(), newObjects.begin(), newObjects.end());
	}
}

bool collisionCheck(ViewableObject *object, ViewableObject *bullet, Vector2int offset)
{
	Vector2int objectPosition = object->getPosition(),
		bulletPosition = bullet->getPosition() + offset,
		objectSize = Vector2int(object->getComponentParameter()->width, object->getComponentParameter()->height) * 20,
		bulletSize = Vector2int(bullet->getComponentParameter()->width, bullet->getComponentParameter()->height);

	if (getLength(objectPosition + objectSize / 2, bulletPosition) > 80)
	{
		return false;
	}

	if (objectPosition.x > bulletPosition.x + bulletSize.x / 2)
	{
		return false;
	}
	if (objectPosition.x + objectSize.x < bulletPosition.x - bulletSize.x / 2)
	{
		return false;
	}
	if (objectPosition.y > bulletPosition.y + bulletSize.y / 2)
	{
		return false;
	}
	if (objectPosition.y + objectSize.y * 20 < bulletPosition.y - bulletSize.y / 2)
	{
		return false;
	}

	//Left
	Vector2int tempBulletPosition = bulletPosition + Vector2int(bulletSize.x / 2, 0);
	if (objectPosition <= tempBulletPosition && objectPosition + objectSize >= tempBulletPosition)
	{
		return true;
	}
	//Right
	tempBulletPosition = bulletPosition - Vector2int(bulletSize.x / 2, 0);
	if (objectPosition <= tempBulletPosition && objectPosition + objectSize >= tempBulletPosition)
	{
		return true;
	}
	//Up
	tempBulletPosition = bulletPosition - Vector2int(0, bulletSize.y / 2);
	if (objectPosition <= tempBulletPosition && objectPosition + objectSize >= tempBulletPosition)
	{
		return true;
	}
	//Down
	tempBulletPosition = bulletPosition + Vector2int(0, bulletSize.y / 2);
	if (objectPosition <= tempBulletPosition && objectPosition + objectSize >= tempBulletPosition)
	{
		return true;
	}

	if (getLength(objectPosition, bulletPosition) > bulletSize.x / 2)
	{
		return false;
	}
	if (getLength(objectPosition + Vector2int(objectSize.x, 0), bulletPosition) > bulletSize.x / 2)
	{
		return false;
	}
	if (getLength(objectPosition + Vector2int(0, objectSize.y), bulletPosition) > bulletSize.x / 2)
	{
		return false;
	}
	if (getLength(objectPosition + objectSize, bulletPosition) > bulletSize.x / 2)
	{
		return false;
	}

	return true;
}

void workWithBullet(vector<Component *> &components, int bulletPositionInComponents, vector<ViewableObject *> &objects, int bulletPositionInObjects, Vector2int offset, int screanWidth, long timer, int positionOfLand)
{
	vector<ViewableObject *> newObjects;

	for (int i = bulletPositionInObjects; i < int(objects.size()); ++i)
	{
		bool breakCheck = true;
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

			objects[i]->setPosition(objects[i]->getBulletPosition() + offset);

			if (objects[i]->getPosition().y + objects[i]->getComponentParameter()->width / 2 >= positionOfLand)
			{
				breakBullet(components, bulletPositionInComponents, objects, bulletPositionInObjects, i, timer);
				breakCheck = false;
			}
		}
		if (!breakCheck)
		{
			--i;
		}
	}

	objects.erase(remove_if(objects.begin(), objects.end(), [](ViewableObject *object) { return object == nullptr; }), objects.end());
}