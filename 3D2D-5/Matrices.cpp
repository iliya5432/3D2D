#include "Matrices.h"

Matrix3x3 Matrices::Rotate(float angleX, float angleY, float angleZ) {

    _rotationMatrixX = SetRotationX(math.ToRadian(angleX));
    _rotationMatrixY = SetRotationY(math.ToRadian(angleY));
    _rotationMatrixZ = SetRotationZ(math.ToRadian(angleZ));
    math.MatrixMult3x3(_rotationMatrixX, _rotationMatrixY, _rotationMatrixXY);
    math.MatrixMult3x3(_rotationMatrixXY, _rotationMatrixZ, _finalRotation);
    return _finalRotation;
}

Matrix3x3 Matrices::SetRotationX(float angleX)
{
    Matrix3x3 matrix(
        1,       0,           0,
        0,  cos(angleX),  sin(angleX),
        0, -sin(angleX),  cos(angleX)
    );
    return matrix;
}

Matrix3x3 Matrices::SetRotationY(float angleY)
{   
    Matrix3x3 matrix(
        cos(angleY), 0, -sin(angleY),
            0,       1,     0,
        sin(angleY), 0, cos(angleY)
    );
    return matrix;
}
Matrix3x3 Matrices::SetRotationZ(float angleZ)
{
    Matrix3x3 matrix(
        cos(angleZ),  sin(angleZ),      0,
       -sin(angleZ),  cos(angleZ),      0,
            0,             0,           1
    );
    return matrix;
}
Matrix4x4 Matrices::Translate(float PosX, float PosY, float PosZ) {
    Matrix4x4 translationMatrix = Matrix4x4(
        1.f, 0.f, 0.f, PosX,
        0.f, 1.f, 0.f, PosY,
        0.f, 0.f, 1.f, PosZ,
        0.f, 0.f, 0.f, 1.f
    );
    return translationMatrix;
}

void Matrices::SetProjection(float aspectRatio, float znear, float zfar, float fov, Matrix4x4& matrix)
{
    fov = tanf(((fov / 2.f) * 3.14159265f) / 180.f);
    matrix = Matrix4x4(
        (1.0f / (aspectRatio * fov)), 0.f, 0.f, 0.f,
        0.f, (-1.0f / fov), 0.f, 0.f,
        0.f, 0.f, (zfar / (zfar - znear)), 1.f,
        0.f, 0.f, (-znear * zfar / (zfar - znear)), 0.f
    );
}

void Matrices::ProjectObject(int triangleIndex, GameObject& Object, Matrix3x3& rotationMatrix, Matrix4x4& translationMatrix, Matrix4x4& projectionMatrix, sf::Vector2f screenSize) {
    //Projection
    for (int i = 0; i < triangleIndex; i++)
    {
        for (int p = 0; p < 3; p++)
        {
            //Set rotated points
            Object.getTriangle(i).setRotatedPoint(p, math.VectorMatrixMult3x3(Object.getTriangle(i).getPoints()[p], rotationMatrix));
            //Set transofrmed points
            Object.getTriangle(i).setTranslatedPoint(p, math.VectorMatrixMult4x4(Object.getTriangle(i).getRotatedPoints()[p], translationMatrix));
            //Set projected Points
            Object.getTriangle(i).setProjectedPoint(p, Object.getTriangle(i).getTranslatedPoints()[p]);
            //Project object (Z axis division)
            Normalize(Object.getTriangle(i).getProjectedPoints()[p], projectionMatrix);
            //Set triangle faces activation as false
            Object.getTriangle(i).setActive(false);
        }
    }
    //Sort projected triangles from back to front
    _sortTrianglesFaces(Object);
    for (int i = 0; i < triangleIndex; i++)
    {
        for (int p = 0; p < 3; p++)
        {
            //Find which point is facing the view
            //Vec3 of triangle.point1 - triangle.point0
            _subTriP1 = math.Sub(Object.getTriangle(i).getProjectedPoints()[1], Object.getTriangle(i).getProjectedPoints()[0]);
            //Vec3 of triangle.point2 - triangle.point0
            _subTriP2 = math.Sub(Object.getTriangle(i).getProjectedPoints()[2], Object.getTriangle(i).getProjectedPoints()[0]);
            //Vec3 of cross producted triangle.point1 and triangle.point2
            _crossedTri = math.CrossProduct(Object.getTriangle(i).getProjectedPoints()[1], Object.getTriangle(i).getProjectedPoints()[2]);
            //Float of dotproducted crossVec3 and any point on screen
            _dotProductedVec = math.DotProduct(_crossedTri, Object.getTriangle(i).getProjectedPoints()[0]);
            //If value facing origin set it active
            if (_dotProductedVec >= 0)
                Object.getTriangle(i).setActive(true);
            else
                Object.getTriangle(i).setActive(false);
        }
    }
    Object.Scale(sf::Vector2f(screenSize));
    Object.Update();
}

void Matrices::Normalize(sf::Vector3f& point, Matrix4x4& Matrix)
{

    math.VectorMatrixMult4x4(point, Matrix);
    float w = (point.x * Matrix.m[0][3]) + (point.y * Matrix.m[1][3]) + (point.z * Matrix.m[2][3]) + Matrix.m[3][3];
    if (w != 0.0f)
    {
        point.x /= w;
        point.y /= w;
        point.z /= w;
    }
}

void Matrices::_sortTrianglesFaces(GameObject& object) {   
    std::sort(object.getTriangleVector().begin(), object.getTriangleVector().end(), [](Triangle& t1, Triangle& t2) {
        float z1 = (t1.getTranslatedPoints()[0].z + t1.getTranslatedPoints()[1].z + t1.getTranslatedPoints()[2].z) / 3.0f;
        float z2 = (t2.getTranslatedPoints()[0].z + t2.getTranslatedPoints()[1].z + t2.getTranslatedPoints()[2].z) / 3.0f;
        return z1 > z2;
        });
}

void Matrices::Scale(sf::Vector3f& point, float x, float y) {
    point.x += 1.f;
    point.y += 1.f;

    point.x *= x;
    point.y *= y;
}