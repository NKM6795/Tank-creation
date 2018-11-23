#pragma once


#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <string>
#include <algorithm>
#include <map>


#define PI 3.1415f
#define GRAVITY 9.8f


using namespace std;


template <typename T>
struct Vector2type
{
	T x, y;

	Vector2type() : x(T()), y(T()) {}

	Vector2type(T x, T y) : x(x), y(y) {}

	template <typename U>
	Vector2type(const Vector2type<U> &right)
	{
		*this = right;
	}

	Vector2type & operator = (const Vector2type &right)
	{
		if (this != &right)
		{
			x = right.x;
			y = right.y;
		}
		return *this;
	}

	template <typename U>
	Vector2type & operator = (const Vector2type<U> &right)
	{
		x = T(right.x);
		y = T(right.y);
		
		return *this;
	}

	inline Vector2type operator + (const Vector2type &right) const
	{
		return Vector2type(x + right.x, y + right.y);
	}

	inline Vector2type operator + (T value) const
	{
		return Vector2type(x + value, y + value);
	}

	inline Vector2type operator - (const Vector2type &right) const
	{
		return Vector2type(x - right.x, y - right.y);
	}

	inline Vector2type operator - (T value) const
	{
		return Vector2type(x - value, y - value);
	}

	inline Vector2type operator * (T value) const
	{
		return Vector2type(x * value, y * value);
	}

	inline Vector2type operator / (T value) const
	{
		return Vector2type(x / value, y / value);
	}

	inline bool operator < (const Vector2type &right) const
	{
		return this->x < right.x && this->y < right.y;
	}
	
	inline bool operator > (const Vector2type &right) const
	{
		return this->x > right.x && this->y > right.y;
	}

	inline bool operator <= (const Vector2type &right) const
	{
		return this->x <= right.x && this->y <= right.y;
	}

	inline bool operator >= (const Vector2type &right) const
	{
		return this->x >= right.x && this->y >= right.y;
	}

	inline bool operator == (const Vector2type &right) const
	{
		return this->x == right.x && this->y == right.y;
	}

	inline bool operator != (const Vector2type &right) const
	{
		return this->x != right.x || this->y != right.y;
	}
};

typedef Vector2type<int> Vector2int;
typedef Vector2type<float> Vector2float;


bool inArea(int width, int height, int xCoordinate, int yCoordinate, int x, int y);

bool inArea(int width, int height, int xCoordinate, int yCoordinate, Vector2int position);

float getLength(float x1, float y1, float x2, float y2);

float getLength(Vector2float first, Vector2float second);

float getAngel(float x1, float y1, float x2, float y2);

float getAngel(Vector2float first, Vector2float second);

float getAngel(int x1, int y1, int x2, int y2);

float getAngel(Vector2int first, Vector2int second);
