#pragma once
#include <iostream>

/*
    Зачем этот define нужен?
*/
#define _USE_MATH_DEFINES
#include <math.h>


class Vector2
{
    public:
        double x, y;
    
        /*
            Уберите реализацию в cpp файл.
            
            Можно написать так, кстати:
            Vector2(double x, double y): x(x), y(y)
            {}
            
            Либо
            
            Vector2(double x, double y):
            {
                this->x = x;
                this->y = y;
            }
            
            Мы просто ещё не успели на семинаре обсудить, что такое this,
            и что такое списки инициализации.
        */
        Vector2(double a, double b):
        x (a), y (b)
        {}
    
        /*
            fixit: нужен ещё пустой конструктор.
            Если бы вы не написали никакого контструктора, то пустой сгенерился бы автоматически.
            Если вы написали сами хоть какой-то, то пустой автоматически не сгенерируется.
        */
    
        /*
            Можно было бы деструктор не писать, и он бы сгенерировался таким сам.
        */
        ~Vector2(){}
    
        Vector2& operator+=(const Vector2& other);
        Vector2& operator-=(const Vector2& other);
        Vector2 operator-() const;
        double operator*(const Vector2 other) const;
        double operator^(const Vector2 other) const;
        double len() const;
        Vector2 unit_vector() const;
        Vector2 normal() const;
        Vector2 rotate(double degree);
        Vector2& getRotate(double degree);
};

std::istream&  operator>>(std::istream& stream, Vector2& v);
std::ostream&  operator<<(std::ostream& stream, const Vector2& v);
Vector2 operator*(double c, const Vector2& v);
Vector2 operator*(const Vector2& v, double c);
Vector2 operator+(const Vector2& first, const Vector2& second);
Vector2 operator-(const Vector2& first, const Vector2& second);
Vector2 operator/(const Vector2& v, double c);
