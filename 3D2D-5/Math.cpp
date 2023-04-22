#include "Math.h"

Matrix3x3::Matrix3x3(
    float x1, float x2, float x3,
    float y1, float y2, float y3,
    float z1, float z2, float z3){
    m[0][0] = x1; m[0][1] = x2; m[0][2] = x3;
    m[1][0] = y1; m[1][1] = y2; m[1][2] = y3;
    m[2][0] = z1; m[2][1] = z2; m[2][2] = z3;
    }

Matrix3x3::Matrix3x3()
{
    for (int p = 0; p < 3; p++)
    {
        m[p][0] = 0.f;
        m[p][1] = 0.f;
        m[p][2] = 0.f;
    }
}
    

   Matrix4x4::Matrix4x4(
       float x1, float x2, float x3, float x4,
        float y1, float y2, float y3, float y4,
        float z1, float z2, float z3, float z4,
        float w1, float w2, float w3, float w4) {
        m[0][0] = x1; m[0][1] = x2; m[0][2] = x3; m[0][3] = x4;
        m[1][0] = y1; m[1][1] = y2; m[1][2] = y3; m[1][3] = y4;
        m[2][0] = z1; m[2][1] = z2; m[2][2] = z3; m[2][3] = z4;
        m[3][0] = w1; m[3][1] = w2; m[3][2] = w3; m[3][3] = w4;
    }
   Matrix4x4::Matrix4x4() {
       for (int p = 0; p < 4; p++)
       {
           m[p][0] = 0.f;
           m[p][1] = 0.f;
           m[p][2] = 0.f;
           m[p][3] = 0.f;
       }
    }


   sf::Vector3f Math::VectorMatrixMult4x4(sf::Vector3f& point, Matrix4x4 Matrix)
   {
       sf::Vector3f newPoint = point;
       newPoint.x = (point.x * Matrix.m[0][0]) + (-point.y * Matrix.m[0][1]) + (point.z * Matrix.m[0][2]) + Matrix.m[0][3];
       newPoint.y = (point.x * Matrix.m[1][0]) + (-point.y * Matrix.m[1][1]) + (point.z * Matrix.m[1][2]) + Matrix.m[1][3];
       newPoint.z = (point.x * Matrix.m[2][0]) + (-point.y * Matrix.m[2][1]) + (point.z * Matrix.m[2][2]) + Matrix.m[2][3];   
       return newPoint;
   }

   sf::Vector3f Math::VectorMatrixMult3x3(sf::Vector3f& point, Matrix3x3 Matrix)
   {
       sf::Vector3f newPoint = point;
       newPoint.x = (point.x * Matrix.m[0][0]) + (point.y * Matrix.m[0][1]) + (point.z * Matrix.m[0][2]);
       newPoint.y = (point.x * Matrix.m[1][0]) + (point.y * Matrix.m[1][1]) + (point.z * Matrix.m[1][2]);
       newPoint.z = (point.x * Matrix.m[2][0]) + (point.y * Matrix.m[2][1]) + (point.z * Matrix.m[2][2]);

       return newPoint;
   }

   void Math::MatrixMult4x4(Matrix4x4& in1, Matrix4x4& in2, Matrix4x4& out)
   {
       
       for (int i = 0; i < 4; i++) //columns
       {
           out.m[0][i] = (in1.m[0][0] * in2.m[0][i]) + (in1.m[0][1] * in2.m[1][i]) + (in1.m[0][2] * in2.m[2][i]) + (in1.m[0][3] * in2.m[3][i]);
           out.m[1][i] = (in1.m[1][0] * in2.m[0][i]) + (in1.m[1][1] * in2.m[1][i]) + (in1.m[1][2] * in2.m[2][i]) + (in1.m[1][3] * in2.m[3][i]);
           out.m[2][i] = (in1.m[2][0] * in2.m[0][i]) + (in1.m[2][1] * in2.m[1][i]) + (in1.m[2][2] * in2.m[2][i]) + (in1.m[2][3] * in2.m[3][i]);
           out.m[3][i] = (in1.m[3][0] * in2.m[0][i]) + (in1.m[3][1] * in2.m[1][i]) + (in1.m[3][2] * in2.m[2][i]) + (in1.m[3][3] * in2.m[3][i]);
       }
      
   }

   void Math::MatrixMult3x3(Matrix3x3& in1, Matrix3x3& in2, Matrix3x3& out)
   {
       
       for (int i = 0; i < 3; i++) //columns
       {
           out.m[0][i] = (in1.m[0][0] * in2.m[0][i]) + (in1.m[0][1] * in2.m[1][i]) + (in1.m[0][2] * in2.m[2][i]);
           out.m[1][i] = (in1.m[1][0] * in2.m[0][i]) + (in1.m[1][1] * in2.m[1][i]) + (in1.m[1][2] * in2.m[2][i]);
           out.m[2][i] = (in1.m[2][0] * in2.m[0][i]) + (in1.m[2][1] * in2.m[1][i]) + (in1.m[2][2] * in2.m[2][i]);
       }
       
   }
   
  
   float Math::ToRadian(float angle)
   {
       return ((angle * 3.14159265f) / 180.f);
   }

   float Math::DotProduct(sf::Vector3f& vec1, sf::Vector3f vec2) {
       return (vec1.x * vec2.x) + (vec1.y * vec2.y) + (vec1.z * vec2.z);
   }

   sf::Vector3f Math::CrossProduct(sf::Vector3f& vec1, sf::Vector3f vec2)
   {
       return sf::Vector3f(
           (vec1.y * vec2.z - vec1.z * vec2.y),
           (vec1.z * vec2.x - vec1.x * vec2.z),
           (vec1.x * vec2.y - vec1.y * vec2.x));
   }

   sf::Vector3f Math::Sub(sf::Vector3f& vec1, sf::Vector3f vec2) {
       return sf::Vector3f(
           (vec1.x - vec2.x),
           (vec1.y - vec2.y),
           (vec1.z - vec2.z)
       );
   }