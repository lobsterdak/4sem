#include <iostream>
#include "Vector2.h"



int main()
{
    Vector2  vec1(1, 1), vec2(2, 2), vec3(4, 3), vec4(1, 0);
    std::cout << "(1;1) + (2;2) = " << vec1 + vec2 << "\n";
    std::cout << "(1;1) - (2;2) = " << vec1 - vec2 << "\n";
    std::cout << "(1;1) * (2;2) = " << vec1 * vec2 << "\n";
    std::cout << "(1;1) ^ (2;2) = " << (vec1 ^ vec2) << "\n";
    std::cout << "(1;1) / 10 = " << (vec1 / 10) << "\n";
    std::cout << "(1;1) * 10 = " << (vec1 * 10) << "\n";
    std::cout << "10 * (1;1) = " << (10 * vec1) << "\n";
    std::cout << "(1;1) += (2;2) = " << (vec1 += vec2) << "\n";
    std::cout << "(3;3) -= (2;2) = " << (vec1 -= vec2) << "\n";
    std::cout << "len(4;3) = " << vec3.len() << "\n";
    std::cout << "norma(4;3) = " << vec3.unit_vector() << "\n";
    std::cout << "normal(4;3) = " << vec3.normal() << "\n";
    std::cout << "rotate(90) (1;0) = " << vec4.getRotate(90) << "\n";
    std::cout << "rotate(90) (0;1) = " << vec4.rotate(90) << "\n";
    return 0;
}