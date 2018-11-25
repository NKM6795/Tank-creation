#pragma once


#include "Bullet.h"
#include "PersonalTank.h"


pair<Vector2int, Vector2int> getObjectParametersForBullet(ViewableObject *object);

Vector2float getBuletPositionFromTime(ViewableObject *bullet, long timer);

void breakBullet(vector<Component *> &components, int bulletPositionInComponents, vector<ViewableObject *> &bullets, int index, long timer, bool completely = true);

bool collisionCheck(ViewableObject *object, ViewableObject *bullet, Vector2float position, Vector2int offset);

void workWithBullet(vector<Component *> &components, int bulletPositionInComponents, vector<ViewableObject *> &bullets, Vector2int offset, int screanWidth, long timer, int fps, int positionOfLand);