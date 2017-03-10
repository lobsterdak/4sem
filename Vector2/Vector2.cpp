#include "Vector2.h"
#include <math.h>

Vector2::Vector2(double a, double b);
x(a), y(b)
{}

std::ostream& operator << (std::ostream& stream, const Vector2& v)
{
    stream << v.x << " " << v.y;
    return stream;
}

std::istream& operator >> (std::istream & stream, Vector2 & v)
{
    stream >> v.x >> v.y;
    return stream;
}

Vector2 operator*(double c, const Vector2& v)
{
    return v * c;
}

Vector2 operator*(const Vector2& v, double c)
{
    return Vector2(c * v.x, c * v.y);
}

Vector2 operator+(const Vector2& first, const Vector2& second)
{
    return Vector2(first.x + second.x, first.y + second.y);
}

Vector2 operator-(const Vector2& first, const Vector2& second)
{
    return Vector2(first.x - second.x, first.y - second.y);
}

double Vector2::len const
{
        return (sqrt(x * x + y * y));
}

Vector2 Vector2::unit_vector() const
{
    return Vector2(x , y) / len(); 
}

Vector2 Vector2::normal() const
{
    return Vector2(-y, x);
}

Vector2 Vector2::operator-() const
{
    return Vector2(-x, -y);
}

Vector2& Vector2::operator+=(const Vector2& other)
{
    x += other.x;
    y += other.y;
    return *this;
}

Vector2& Vector2::operator-=(const Vector2& other)
{
    x -= other.x;
    y -= other.y;
    return *this;
}

double Vector2::operator*(const Vector2 other) const
{
    return (x * other.x + y * other.y);
}

double Vector2::operator^(const Vector2 other) const
{
    return (x * other.y - y * other.x);
}

Vector2 operator/(const Vector2& v, double c)
{
    return Vector2(v.x / c, v.y / c);
}

Vector2 Vector2::getRotate(double degree) const
{
    return Vector2(x, y).rotate(degree);
}

Vector2 Vector2::rotate(double degree)
{
    double rad = degree / 180 * M_PI;
    double xtmp = x;
    x = x * cos(rad) - y * sin(rad);
    y = xtmp * sin(rad) + y * cos(rad);
    return *this;
}
