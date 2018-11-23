#include "WorkWithBullet.h"


void workWithBullet(vector<ViewableObject *> &objects, int bulletPositionInObjects)
{
	for (int i = bulletPositionInObjects; i < int(objects.size()); ++i)
	{
		objects[i]->setPosition(objects[i]->getPosition() + Vector2int(1, 1));
	}
}