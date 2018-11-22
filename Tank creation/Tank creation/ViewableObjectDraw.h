#pragma once


#include "BackgroundDraw.h"
#include "SmallBlockDraw.h"
#include "BigBlockDraw.h"
#include "EngineRoomDraw.h"
#include "TrackDraw.h"
#include "GunDraw.h"
#include "TankPictureDraw.h"
#include "SpeedometerDraw.h"
#include "AllotmentDraw.h"
#include "BulletDraw.h"


void objectDraw(RenderTexture &renderTexture, long timer, vector<ViewableObject *> &objects, vector<ComponentDraw *> &components);