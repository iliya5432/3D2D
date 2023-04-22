#include <iostream>
#include "SFML/Graphics.hpp"
#define MATRIX3x3_H
#ifdef MATRIX3x3_H
struct Matrix3x3 {
public:
    float m[3][3];
    Matrix3x3(float x1, float x2, float x3,
        float y1, float y2, float y3,
        float z1, float z2, float z3
    );
    Matrix3x3();
};
#endif // MATRIX3x3_H

#define MATRIX4x4_H
#ifdef MATRIX4x4_H
struct Matrix4x4 {
public:
    float m[4][4];
    Matrix4x4(float x1, float x2, float x3, float x4,
        float y1, float y2, float y3, float y4,
        float z1, float z2, float z3, float z4,
        float w1, float w2, float w3, float w4
    );
    Matrix4x4();

};
#endif // MATRIX4x4_H

#define MATH_H
#ifdef MATH_H

class Math {
public:
    sf::Vector3f VectorMatrixMult3x3(sf::Vector3f& point, Matrix3x3 Matrix); 
    sf::Vector3f VectorMatrixMult4x4(sf::Vector3f& point, Matrix4x4 Matrix);
    void MatrixMult4x4(Matrix4x4& in1, Matrix4x4& in2, Matrix4x4& out); //Translation function
    void MatrixMult3x3(Matrix3x3& in1, Matrix3x3& in2, Matrix3x3& out);
    float ToRadian(float angle);
    float DotProduct(sf::Vector3f& vec1, sf::Vector3f vec2);
    sf::Vector3f CrossProduct(sf::Vector3f& vec1, sf::Vector3f vec2);
    sf::Vector3f Sub(sf::Vector3f& vec1, sf::Vector3f vec2);
};
#endif //MATH_H
