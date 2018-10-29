#pragma once


#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <string>
#include <algorithm>


using namespace std;


struct Vector2int
{
	int x;
	int y;

	Vector2int() : x(0), y(0) {}

	Vector2int(int x, int y) : x(x), y(y) {}
};

bool inArea(int width, int height, int xCoordinate, int yCoordinate, int x, int y);

bool inArea(int width, int height, int xCoordinate, int yCoordinate, Vector2int position);

float getLength(float x1, float y1, float x2, float y2);