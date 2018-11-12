#pragma once


#include "BackgroundDraw.h"
#include "SmallBlockDraw.h"
#include "BigBlockDraw.h"
#include "EngineRoomDraw.h"
#include "TrackDraw.h"
#include "GunDraw.h"


void objectDraw(RenderTexture &renderTexture, long timer, vector<Object *> &objects, vector<ComponentDraw *> &components);