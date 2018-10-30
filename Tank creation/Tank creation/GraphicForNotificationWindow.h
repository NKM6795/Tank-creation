#pragma once


#include "BasicElementDraw.h"


void drawLine(RenderTexture &renderTexture, int x1, int y1, int x2, int y2, Color color);

void drawRectangle(RenderTexture &renderTexture, int x1, int y1, int x2, int y2, Color color);

void drawFramework(RenderTexture &renderTexture, int x1, int y1, int x2, int y2);

Image *getForm(int width, int height);