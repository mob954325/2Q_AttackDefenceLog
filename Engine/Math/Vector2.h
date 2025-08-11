#pragma once
#include <iostream>
#include <float.h>
#include <math.h>

struct Vector2
{
	float x, y;

	Vector2();
	Vector2(float valueX, float valueY);
	Vector2(int valueX, int valueY);

	static const Vector2& Down();
	static const Vector2& Left();
	static const Vector2& One();
	static const Vector2& Right();
	static const Vector2& Up();
	static const Vector2& Zero();

	Vector2 operator-() const;

	Vector2 operator+(const Vector2& other) const;
	Vector2 operator-(const Vector2& other) const;

	Vector2 operator*(float other) const;
	Vector2 operator*(int other) const;

	Vector2 operator/(float other) const;
	Vector2 operator/(int other) const;

	Vector2& operator+=(const Vector2& other);
	Vector2& operator-=(const Vector2& other);
	bool operator==(const Vector2& other);
	friend std::ostream& operator<<(std::ostream& os, Vector2 vec);

	bool IsZero() const;
	static float Dot(const Vector2& lhs, const Vector2& rhs);
	static float Cross(const Vector2& lhs, const Vector2& rhs);
	Vector2	Lerp(Vector2& start, Vector2& end, float t);
	float Megnituede() const;
	float SqrMegnitude() const;
	Vector2 Normalize() const;
};

// float * vector
inline Vector2 operator*(float scalar, const Vector2& vec)
{
	return vec * scalar;
}

// int * vector
inline Vector2 operator*(int scalar, const Vector2& vec)
{
	return vec * scalar;
}