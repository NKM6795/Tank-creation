#pragma once


#include "Bullet.h"
#include "PersonalTank.h"


Vector2float getBuletPositionFromTime(ViewableObject *bullet, Vector2int offset, long timer);

void breakBullet(vector<Component *> &components, int bulletPositionInComponents, vector<ViewableObject *> &bullets, int index, long timer, bool completely = true);

bool collisionCheck(ViewableObject *object, ViewableObject *bullet, Vector2float position, Vector2int offset);

void workWithBullet(vector<Component *> &components, int bulletPositionInComponents, vector<ViewableObject *> &bullets, Vector2int offset, int screanWidth, long timer, int positionOfLand);