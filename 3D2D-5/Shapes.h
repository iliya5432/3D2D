#include <iostream>
#include <stdio.h>
#include "FileReader.h"
#include "SFML/Graphics.hpp"

#define Rotation_H
#ifdef Rotation_H
struct Rotation {
public:
    bool left, right, up, down, spinLeft, spinRight;
    float speed;
    Rotation();
    sf::Vector3f& getAngle();
    void setAngle(float x, float y, float z);
private:
    sf::Vector3f _angle;
};
#endif

#define Movement_H
#ifdef Movement_H
struct Movement {
public:
    bool left, right, up, down, forwards, backwards;
    float speed;
    Movement();
};
#endif

#define Mode_H
#ifdef Mode_H
struct Mode {
public:
    bool onColorChange;
    bool onSpeedChange;
    bool drawPoints;
    bool drawLines;
    bool drawColors;
    Mode()
    {
        onColorChange = false;
        onSpeedChange = false;
        drawPoints = false;
        drawLines = false;
        drawColors = false;
    }
};
#endif

#define Line_H
#ifdef Line_H
struct Line {
public:
    Line();
    Line(float x1, float y1, float x2, float y2, sf::Color color);
    sf::Vertex* getPoint();
private:
    sf::Vertex _points[2];
};
#endif

#define Triangle_H
#ifdef Triangle_H
constexpr int POINTS_NUMBER = 3;
struct Triangle {
public:
    
    
    Triangle(); 
    sf::Vector3f* getPoints();
    void setPoint(int index, sf::Vector3f point);

    sf::Vector3f* getRotatedPoints();
    void setRotatedPoint(int index, sf::Vector3f point);

    sf::Vector3f* getTranslatedPoints();
    void setTranslatedPoint(int index, sf::Vector3f point);

    sf::Vector3f* getProjectedPoints();
    void setProjectedPoint(int index, sf::Vector3f point);

    Line* getLine();
    
    void SetLine(int lineNumber, int PointNumber, float x, float y);

    bool GetActive();
    void setActive(bool active);

    sf::ConvexShape getFill();
    void SetFillColor(sf::Color color);

    void Update();
private:
    sf::Vector3f _points[POINTS_NUMBER];
    sf::Vector3f _rotatedPoints[POINTS_NUMBER];
    sf::Vector3f _translatedPoints[POINTS_NUMBER];
    sf::Vector3f _projectedPoints[POINTS_NUMBER];
    Line _line[POINTS_NUMBER];
    bool _isActive;
    sf::ConvexShape _fill;

};
#endif

#define GAMEOBJECT_H
#ifdef GAMEOBJECT_H
struct GameObject {
public:
    Rotation rotation;
    Movement movement;
    Mode mode;
    GameObject(std::string path);
    GameObject();
    Triangle& getTriangle(int index);
    void setTriangle(int index, Triangle triangle);
    void addTriangle(Triangle triangle);
    int getTrianglesSize();
    void Scale(sf::Vector2f screenSize);
    void Update();
    std::vector<Triangle>& getTriangleVector();
private:
    std::vector<Triangle> _triangles;
};
#endif 