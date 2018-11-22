#pragma once


#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <string>
#include <algorithm>
#include <map>


#define PI 3.1415f


using namespace std;


struct Vector2int
{
	int x, y;

	Vector2int() : x(0), y(0) {}

	Vector2int(int x, int y) : x(x), y(y) {}

	Vector2int & operator = (const Vector2int &right)
	{
		if (this != &right)
		{
			x = right.x;
			y = right.y;
		}
		return *this;
	}

	inline Vector2int operator + (const Vector2int &right) const
	{
		return Vector2int(x + right.x, y + right.y);
	}

	inline Vector2int operator + (int value) const
	{
		return Vector2int(x + value, y + value);
	}

	inline Vector2int operator - (const Vector2int &right) const
	{
		return Vector2int(x - right.x, y - right.y);
	}

	inline Vector2int operator - (int value) const
	{
		return Vector2int(x - value, y - value);
	}

	inline Vector2int operator * (int value) const
	{
		return Vector2int(x * value, y * value);
	}

	inline Vector2int operator / (int value) const
	{
		return Vector2int(x / value, y / value);
	}

	inline bool operator < (const Vector2int &right) const
	{
		return this->x < right.x && this->y < right.y;
	}
	
	inline bool operator > (const Vector2int &right) const
	{
		return this->x > right.x && this->y > right.y;
	}

	inline bool operator <= (const Vector2int &right) const
	{
		return this->x <= right.x && this->y <= right.y;
	}

	inline bool operator >= (const Vector2int &right) const
	{
		return this->x >= right.x && this->y >= right.y;
	}

	inline bool operator == (const Vector2int &right) const
	{
		return this->x == right.x && this->y == right.y;
	}

	inline bool operator != (const Vector2int &right) const
	{
		return this->x != right.x || this->y != right.y;
	}
};


bool inArea(int width, int height, int xCoordinate, int yCoordinate, int x, int y);

bool inArea(int width, int height, int xCoordinate, int yCoordinate, Vector2int position);

float getLength(float x1, float y1, float x2, float y2);

float getAngel(float x1, float y1, float x2, float y2);

float getAngel(int x1, int y1, int x2, int y2);

float getAngel(Vector2int first, Vector2int second);
