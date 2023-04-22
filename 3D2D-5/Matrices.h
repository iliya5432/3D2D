#include <iostream>
#include "SFML/Graphics.hpp"
#include "Math.h"
#include "Shapes.h"

#define Matrices_H
#ifdef Matrices_H
class Matrices {
public:
	Matrix3x3 Rotate(float angleX, float angleY, float angleZ);
	Matrix3x3 SetRotation(float angleX, float angleY, float angleZ);
	Matrix4x4 Translate(float PosX, float PosY, float PosZ);
	void SetProjection(float aspectRatio, float znear, float zfar, float fov, Matrix4x4& matrix);
	void Normalize(sf::Vector3f& point, Matrix4x4& Matrix);
	void ProjectObject(int triangleIndex, GameObject& Object, Matrix3x3& rotationMatrix, Matrix4x4& translationMatrix, Matrix4x4& projectionMatrix, sf::Vector2f screenSize);
	void Scale(sf::Vector3f& point, float x, float y);
	Matrix3x3 SetRotationX(float angleX);
	Matrix3x3 SetRotationY(float angleY);
	Matrix3x3 SetRotationZ(float angleZ);
private:
	Math math;
	sf::Vector3f _projectedPointVec;
	sf::Vector3f _subTriP1;
	sf::Vector3f _subTriP2;
	sf::Vector3f _crossedTri;
	Matrix3x3 _rotationMatrixX;
	Matrix3x3 _rotationMatrixY;
	Matrix3x3 _rotationMatrixZ;
	Matrix3x3 _rotationMatrixXY;
	Matrix3x3 _finalRotation;
	Matrix4x4 _translationMatrix;
	float _dotProductedVec;
	void _sortTrianglesFaces(GameObject& Object);
};
#endif
