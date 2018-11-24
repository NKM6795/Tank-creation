#include "WorkWithBullet.h"


Vector2float getBuletPositionFromTime(ViewableObject *bullet, Vector2int offset, long timer)
{
	float time = float(timer - bullet->timerForObject) / 200.f;
	Vector2float newPosition(bullet->getBulletPosition(true).x + float(time) * bullet->speed * sin(bullet->tiltAngle * PI / 180.f), bullet->getBulletPosition(true).y - float(time) * bullet->speed * cos(bullet->tiltAngle * PI / 180.f));

if (!bullet->getFather()->getComponentParameter()->horizontally)
{
	newPosition.y = bullet->getBulletPosition(true).y + GRAVITY * 0.5f * time * time - bullet->speed * time * cos(bullet->tiltAngle * PI / 180.f);
}

return newPosition;
}

void breakBullet(vector<Component *> &components, int bulletPositionInComponents, vector<ViewableObject *> &bullets, int index, long timer, bool completely)
{
	if (!completely)
	{
		bullets[index]->setHeath(bullets[index]->getHealth() - 1);
		if (bullets[index]->getHealth() == 0)
		{
			completely = true;
		}
		else
		{
			return;
		}
	}

	ViewableObject *bullet = bullets[index],
		*father = bullet->getFather();

	vector<ViewableObject *> newObjects;

	if (bullet->getFather()->getComponentParameter()->indexOfComponents.size() == 1)
	{
		delete bullet;
		bullet = nullptr;
		bullets[index] = nullptr;
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
		bullets[index] = nullptr;
	}

	bullets.erase(remove_if(bullets.begin(), bullets.end(), [](ViewableObject *object) { return object == nullptr; }), bullets.end());

	if (newObjects.size() != 0)
	{
		bullets.insert(bullets.end(), newObjects.begin(), newObjects.end());
	}
}

bool collisionCheck(ViewableObject *object, ViewableObject *bullet, Vector2float position, Vector2int offset)
{
	Vector2int objectPosition = object->getPosition(),
		bulletPosition = position + offset,
		mainObjectSize = Vector2int(object->getComponentParameter()->width, object->getComponentParameter()->height) * 20,
		objectSize = Vector2int(object->getComponentParameter()->width, object->getComponentParameter()->height) * 20,
		bulletSize = Vector2int(bullet->getComponentParameter()->width, bullet->getComponentParameter()->height);

	//for gun
	if ((typeid(*object) == typeid(Gun)))
	{
		if (objectSize.x == 20)
		{
			objectSize.x = 13;
		}
		else if (object->getComponentParameter()->horizontally && objectSize.x != 60)
		{
			objectSize.x = 17;
		}
		else if (object->getComponentParameter()->horizontally && objectSize.x == 60)
		{
			objectPosition.y += 4;
			objectSize = Vector2int(17, 52);
		}
		else if (objectSize.x == 40)
		{
			objectSize.y = 19;
			objectPosition.y += 21;
		}
		else if (objectSize.x == 60)
		{
			objectSize = Vector2int(34, 45);
			objectPosition.x += 13;
			objectPosition.y += 15;
		}
		else
		{
			objectSize = Vector2int(58, 78);
			objectPosition.x += 11;
			objectPosition.y += 2;
		}
	}

	//common
	{
		if (getLength(objectPosition + objectSize / 2, bulletPosition) > 80)
		{
			return false;
		}
	}

	//outside
	{
		//left
		if (objectPosition.x > bulletPosition.x + bulletSize.x / 2)
		{
			return false;
		}
		//right
		if (objectPosition.x + objectSize.x < bulletPosition.x - bulletSize.x / 2)
		{
			return false;
		}
		//top
		if (objectPosition.y > bulletPosition.y + bulletSize.y / 2)
		{
			return false;
		}
		//bottom
		if (objectPosition.y + objectSize.y * 20 < bulletPosition.y - bulletSize.y / 2)
		{
			return false;
		}
	}

	//inside
	{
		//Right
		Vector2int tempBulletPosition = bulletPosition + Vector2int(bulletSize.x / 2, 0);
		if (objectPosition <= tempBulletPosition && objectPosition + objectSize >= tempBulletPosition)
		{
			return true;
		}
		//Left
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
	}

	//at the corners
	{
		//top left
		if (getLength(objectPosition, bulletPosition) > bulletSize.x / 2)
		{
			return false;
		}
		//top right
		if (getLength(objectPosition + Vector2int(objectSize.x, 0), bulletPosition) > bulletSize.x / 2)
		{
			return false;
		}
		//bottom left
		if (getLength(objectPosition + Vector2int(0, objectSize.y), bulletPosition) > bulletSize.x / 2)
		{
			return false;
		}
		//bottom right
		if (getLength(objectPosition + objectSize, bulletPosition) > bulletSize.x / 2)
		{
			return false;
		}
	}

	return true;
}

void workWithBullet(vector<Component *> &components, int bulletPositionInComponents, vector<ViewableObject *> &bullets, Vector2int offset, int screanWidth, long timer, int fps, int positionOfLand)
{
	vector<ViewableObject *> newObjects;

	for (int i = 0; i < int(bullets.size()); ++i)
	{
		bool breakCheck = true;
		if (getLength(bullets[i]->getBulletPosition(), bullets[i]->getBulletPosition(true)) > float(screanWidth))
		{
			delete bullets[i];
			bullets[i] = nullptr;
		}
		else
		{
			bullets[i]->setBulletPosition(getBuletPositionFromTime(bullets[i], offset, timer));

			bullets[i]->setPosition(bullets[i]->getBulletPosition() + offset);

			if (bullets[i]->getPosition().y + bullets[i]->getComponentParameter()->width / 2 >= positionOfLand)
			{
				breakBullet(components, bulletPositionInComponents, bullets, i, timer - fps);
				breakCheck = false;
			}
		}
		if (!breakCheck)
		{
			--i;
		}
	}

	bullets.erase(remove_if(bullets.begin(), bullets.end(), [](ViewableObject *object) { return object == nullptr; }), bullets.end());
}