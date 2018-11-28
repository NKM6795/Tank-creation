#pragma once


#include "Bullet.h"
#include "PersonalTank.h"


pair<Vector2int, Vector2int> getObjectParametersForBullet(ViewableObject *object);

Vector2float getBuletPositionFromTime(ViewableObject *bullet, long timer);

void breakBullet(vector<Component *> &components, int bulletPositionInComponents, vector<ViewableObject *> &bullets, int index, long timer, bool completely = true, vector<vector<ViewableObject *> > *objects = nullptr, Vector2int objectPositionInTank = Vector2int(-1, -1), Vector2int offset = Vector2int(0, 0), int special = 0);

bool collisionCheck(ViewableObject *object, ViewableObject *bullet, Vector2float position, Vector2int offset);

void workWithBullet(vector<Component *> &components, int bulletPositionInComponents, vector<ViewableObject *> &bullets, Vector2int offset, int screanWidth, long timer, int fps, int positionOfLand);