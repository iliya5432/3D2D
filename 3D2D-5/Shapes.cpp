#include "Shapes.h"

Rotation::Rotation() {
    left = false;
    right = false;
    up = false;
    down = false;
    spinLeft = false;
    spinRight = false;
    speed = 0.3f;
    _angle.x = 0.1f;
    _angle.y = 0.1f;
    _angle.z = 0.1f;
    
}
Movement::Movement()
{
    left = false;
    right = false;
    up = false;
    down = false;
    forwards = false;
    backwards = false;
    speed = 0.01f;
}

sf::Vector3f& Rotation::getAngle() {
    return _angle;
}

void Rotation::setAngle(float x, float y, float z) {
    _angle.x = x;
    _angle.y = y;
    _angle.z = z;
    if (x == 360)
        _angle.x = 0;
    if (y == 360)
        _angle.y = 0;
    if (z == 360)
        _angle.z = 0;
}



Line::Line(){}
Line::Line(float x1, float y1, float x2, float y2, sf::Color color) {   
    _points[0].position = sf::Vector2f(x1, y1);
    _points[1].position = sf::Vector2f(x2, y2);
    _points->color = color;
}
sf::Vertex* Line::getPoint()
{
    return _points;
}

   

    Triangle::Triangle() {
        for (int i = 0; i < 3; i++)
        {
            _points[i] = sf::Vector3f(0, 0, 0);
        }
        _isActive = false;
        _fill.setPointCount(3);
        Update();
    }

    sf::Vector3f *Triangle::getPoints() {
        return _points;
    }

    void Triangle::setPoint(int index, sf::Vector3f point) {
        _points[index] = point;
    }

    sf::Vector3f* Triangle:: getRotatedPoints() {
        return _rotatedPoints;
    }
    void Triangle::setRotatedPoint(int index, sf::Vector3f point) {
        _rotatedPoints[index] = point;
    }

    sf::Vector3f* Triangle::getTranslatedPoints() {
        return _translatedPoints;
    }
    void Triangle::setTranslatedPoint(int index, sf::Vector3f point) {
        _translatedPoints[index] = point;
    }

    sf::Vector3f* Triangle::getProjectedPoints() {
        return _projectedPoints;
    }
    void Triangle::setProjectedPoint(int index, sf::Vector3f point)
    {
        _projectedPoints[index] = point;
    }

    Line* Triangle::getLine()
    {
        return _line;
    }
   
    void Triangle::Update() {
        SetLine(0, 0, _projectedPoints[0].x, _projectedPoints[0].y); SetLine(0, 1, _projectedPoints[1].x, _projectedPoints[1].y);
        SetLine(1, 0, _projectedPoints[1].x, _projectedPoints[1].y); SetLine(1, 1, _projectedPoints[2].x, _projectedPoints[2].y);
        SetLine(2, 0, _projectedPoints[2].x, _projectedPoints[2].y); SetLine(2, 1, _projectedPoints[0].x, _projectedPoints[0].y);

        for (int i = 0; i < 3; i++)
        {
            _fill.setPoint(i, sf::Vector2f(_projectedPoints[i].x, _projectedPoints[i].y));
        }
    }

    void Triangle::SetLine(int lineNumber, int PointNumber, float x, float y)
    {
        _line[lineNumber].getPoint()[PointNumber].position.x = x;
        _line[lineNumber].getPoint()[PointNumber].position.y = y;
    }

    bool Triangle::GetActive() {
        return _isActive;
    }
    void Triangle::setActive(bool active) {
        _isActive = active;
    }
    sf::ConvexShape Triangle::getFill() {
        return _fill;
    }

    void Triangle::SetFillColor(sf::Color color) {
        _fill.setFillColor(color);
    }

    GameObject::GameObject(std::string path) {
        FileReader fileRead(path);

        
        int fileSize = fileRead.sizeOfTriangles();
        Triangle newTriangle;
        for (int i = 0; i < fileSize; i++)
        {
            for (int p = 0; p < 3; p++) {
                sf::Vector3f point = fileRead.getPoint(i, p);
                newTriangle.setPoint(p, point);
            }
            _triangles.push_back(newTriangle);
        }
       
    }
   
    Triangle& GameObject::getTriangle(int index) 
    {     
        return _triangles[index];
    }

    void GameObject::setTriangle(int index, Triangle triangle) {
        _triangles[index] = triangle;
    }

    void GameObject::addTriangle(Triangle triangle)
    {
        _triangles.push_back(triangle);
    }

    int GameObject::getTrianglesSize()
    {
        return _triangles.size();
    }
    void GameObject::Scale(sf::Vector2f screenSize)
    {
        for (int i = 0; i < getTrianglesSize(); i++)
        {
            for (int p = 0; p < 3; p++)
            {
                sf::Vector3f projected = _triangles[i].getProjectedPoints()[p];
                projected.x += 1.f;
                projected.y += 1.f;

                projected.x *= screenSize.x / 2;
                projected.y *= screenSize.y / 2;

                _triangles[i].setProjectedPoint(p, projected);              
            }
        }
    }

    void GameObject::Update() {

        for (int i = 0; i < _triangles.size(); i++)
        {
            _triangles[i].Update();
        }
    }

    std::vector<Triangle>& GameObject::getTriangleVector() {
        return _triangles;
    }