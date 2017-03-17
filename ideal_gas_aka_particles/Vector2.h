#pragma once
#include <iostream>

/*
Зачем этот define нужен? // Чтобы работалa поддержка константы M_PI = pi;
*/
#define _USE_MATH_DEFINES
#include <math.h>


class Vector2
{
public:
    double x, y;
    Vector2()
    {}
    Vector2(double a, double b);
    ~Vector2() {}
    Vector2& operator+=(const Vector2& other);
    Vector2& operator-=(const Vector2& other);
    Vector2 operator-() const;
    double operator*(const Vector2 other) const;
    double operator^(const Vector2 other) const;
    double len() const;
    Vector2 unit_vector() const;
    Vector2 normal() const;
    Vector2 rotate(double degree);
    Vector2 getRotate(double degree) const;
};

std::istream&  operator >> (std::istream& stream, Vector2& v);
std::ostream&  operator<<(std::ostream& stream, const Vector2& v);
Vector2 operator*(double c, const Vector2& v);
Vector2 operator*(const Vector2& v, double c);
Vector2 operator+(const Vector2& first, const Vector2& second);
Vector2 operator-(const Vector2& first, const Vector2& second);
Vector2 operator/(const Vector2& v, double c);
