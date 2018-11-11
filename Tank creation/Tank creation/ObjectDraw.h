#pragma once


#include "BackgroundDraw.h"
#include "SmallBlockDraw.h"
#include "BigBlockDraw.h"


void objectDraw(RenderTexture &renderTexture, long timer, vector<Object *> &objects, vector<ComponentDraw *> &components);