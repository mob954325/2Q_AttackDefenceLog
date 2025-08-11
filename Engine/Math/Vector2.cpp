#include "Vector2.h"

Vector2::Vector2()
{
	x = 0;
	y = 0;
}

Vector2::Vector2(float valueX, float valueY)
{
	x = valueX;
	y = valueY;
}

Vector2::Vector2(int valueX, int valueY)
{
	x = (float)valueX;
	y = (float)valueY;
}

const Vector2& Vector2::Down()
{
	static const Vector2 down(0.0f, -1.0f);
	return down;
}

const Vector2& Vector2::Left()
{
	static const Vector2 left(-1.0f, 0.0f);
	return left;
}

const Vector2& Vector2::One()
{
	static const Vector2 one(1.0f, 1.0f);
	return one;
}

const Vector2& Vector2::Right()
{
	static const Vector2 right(1.0f, 0.0f);
	return right;
}

const Vector2& Vector2::Up()
{
	static const Vector2 up(0.0f, 1.0f);
	return up;
}

const Vector2& Vector2::Zero()
{
	static const Vector2 zero(0.0f, 0.0f);
	return zero;
}

Vector2 Vector2::operator-() const
{
	return Vector2(-x, -y);
}

Vector2 Vector2::operator+(const Vector2& other) const
{
	return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator-(const Vector2& other) const
{
	return Vector2(x - other.x, y - other.y);
}

Vector2 Vector2::operator*(float other) const
{
	return Vector2(x * other, y * other);
}

Vector2 Vector2::operator*(int other) const
{
	return Vector2(x * other, y * other);
}

Vector2 Vector2::operator/(float other) const
{
	return Vector2(x / other, y / other);
}

Vector2 Vector2::operator/(int other) const
{
	return Vector2(x / other, y / other);
}

Vector2& Vector2::operator+=(const Vector2& other)
{
	x += other.x; y += other.y;
	return *this;
}

Vector2& Vector2::operator-=(const Vector2& other)
{
	x -= other.x; y -= other.y;
	return *this;
}

bool Vector2::operator==(const Vector2& other)
{
	return (x == other.x) && (y == other.y);
}

bool Vector2::IsZero() const
{
	return x < FLT_EPSILON + 1.1e-13f && y < FLT_EPSILON + 1.1e-13f;
}

float Vector2::Dot(const Vector2& lhs, const Vector2& rhs)
{
	return lhs.x * rhs.x + lhs.y * rhs.y;
}

float Vector2::Cross(const Vector2& lhs, const Vector2& rhs)
{
	return lhs.x * rhs.y - lhs.y * rhs.x;
}

float Vector2::Megnituede() const
{
	return sqrt(x * x + y * y);
}

float Vector2::SqrMegnitude() const
{
	return x * x + y * y;
}

Vector2 Vector2::Normalize() const
{
	float len = Megnituede();
	if (len < FLT_EPSILON)
		return Vector2(0.0f, 0.0f);
	return Vector2(x / len, y / len);
}

Vector2	Vector2::Lerp(Vector2& start, Vector2& end, float t)
{
	Vector2 lerpVec = (1.0f - t) * start + t * end;
	return lerpVec;
}

std::ostream& operator<<(std::ostream& os, Vector2 vec)
{
	os << vec.x << ", " << vec.y;
	return os;
}
