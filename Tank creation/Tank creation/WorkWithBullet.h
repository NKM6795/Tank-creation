#pragma once


#include "Bullet.h"
#include "PersonalTank.h"


void breakBullet(vector<Component *> &components, int bulletPositionInComponents, vector<ViewableObject *> &objects, int bulletPositionInObjects, int index, long timer, bool completely = true);

bool collisionCheck(ViewableObject *object, ViewableObject *bullet, Vector2int offset);

void workWithBullet(vector<Component *> &components, int bulletPositionInComponents, vector<ViewableObject *> &objects, int bulletPositionInObjects, Vector2int offset, int screanWidth, long timer, int positionOfLand);