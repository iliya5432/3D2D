#include "SFML/Graphics.hpp"
#include <Windows.h>
#include <iostream>
#include <chrono>
#include "ObjectController.h"
using namespace sf;

RenderWindow window(VideoMode(1200, 1000), "3D2D");
ObjectController controller;
Math math;
Matrices matrix;
Vector2f screenSize(Vector2f(window.getSize().x, window.getSize().y));
CircleShape NewDot(float fRadius, float x, float y); //Default CircleShape Object of SFML library setter function
void DrawLines(GameObject& object);
void DrawSides(GameObject& object);
void DrawPoints(float dotRadius, GameObject& object);
bool once = false;
int main()
{
    //Console window handler
    HWND hWnd = GetConsoleWindow();

    //Console window hide
    ShowWindow(hWnd, SW_SHOW);

    //event handle
    Event e;

    //SFML window framerate 
    window.setFramerateLimit(144);

    //CircleShape object radius size
    float dotRadius = 2.f;
    Matrix3x3 teaPotRotationMatrix = matrix.Rotate(0, 0, 0);
    Matrix4x4 translationMatrix = matrix.Translate(0.f, 0.f, 3.f);
    Matrix4x4 projectionMatrix;
    matrix.SetProjection(window.getSize().x / window.getSize().y, 0.1f, 1000.0f, 90.0f, projectionMatrix);

    //GameObject cube("D:/Projects/CPP/3D2D-5/x64/Debug/Cube.txt");
    GameObject pyramid("D:/Projects/CPP/3D2D-5/x64/Debug/Pyramid.txt");
    controller.addObject(pyramid);
    //GameObject teaPot("D:/Projects/CPP/3D2D-5/x64/Debug/Teapot.txt");
    //controller.addObject(teaPot);
    
    //Game loop
    while (window.isOpen())
    {
            auto start = std::chrono::high_resolution_clock::now();
            for (auto obj : controller.getGameObjectVec())
                teaPotRotationMatrix = matrix.Rotate(obj->rotation.getAngle().x, obj->rotation.getAngle().y, obj->rotation.getAngle().z);
        //Event handler loop
        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                window.close();
            //Foreach object in controller object vector
            for (auto obj : controller.getGameObjectVec())
                //Object key handler
                controller.keyMap(e, *obj);
            
        }
        //Clear SFML window before drawing
        window.clear();
     
        //Foreach object in controller object vector
        for (auto obj : controller.getGameObjectVec())
            //Object movement & rotation controller
            controller.keyControl(*obj, translationMatrix);

        //For object in controller object vector
        for (int i = 0; i < controller.getGameObjectVec().size(); i++)
        {
                //Project object
                matrix.ProjectObject(controller.getGameObjectVec()[i]->getTrianglesSize(), *controller.getGameObjectVec()[i], teaPotRotationMatrix, translationMatrix, projectionMatrix, screenSize);        
                //Check for controller drawing modes
            if (controller.getGameObjectVec()[i]->mode.drawColors) //If object's sides (faces) color bool is true
                DrawSides(*controller.getGameObjectVec()[i]); //Draw sides (faces)
            if (controller.getGameObjectVec()[i]->mode.drawLines) //If object's lines bool is true
                DrawLines(*controller.getGameObjectVec()[i]); //Draw lines
            if (controller.getGameObjectVec()[i]->mode.drawPoints) //If object's points bool is true
                DrawPoints(2.0f, *controller.getGameObjectVec()[i]); //Draw points
        }

        /*loop time counter*/
        //Stops time counting
        auto stop = std::chrono::high_resolution_clock::now();
        //Calculating duration of time counted
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        //Print time in milliseconds
        std::cout << duration.count() / 1000 << " ms\n";

        //SFML window display
        window.display();
    }
}


void DrawPoints(float dotRadius, GameObject& object)
{
    CircleShape point;
    for (int i = 0; i < object.getTrianglesSize(); i++)
    {
        for (int p = 0; p < 3; p++)
        {
            point = NewDot(dotRadius, object.getTriangle(i).getProjectedPoints()[p].x - dotRadius, object.getTriangle(i).getProjectedPoints()[p].y - dotRadius);
            window.draw(point);
        }
    }
}

void DrawLines(GameObject& object)
{
    for (int i = 0; i < object.getTrianglesSize(); i++)
    {
        for (int p = 0; p < 3; p++)
        {
            for (int p = 0; p < 3; p++)
                window.draw(object.getTriangle(i).getLine()[p].getPoint(), 2, Lines);
        }
    }
}
void DrawSides(GameObject& object)
{
    for (int i = 0; i < object.getTrianglesSize(); i++)
    {
            if (object.getTriangle(i).GetActive())
                window.draw(object.getTriangle(i).getFill());     
    }
}

CircleShape NewDot(float fRadius, float x, float y) {
    CircleShape newDot(fRadius);
    newDot.setPosition(Vector2f(x, y));
    newDot.setFillColor(Color().Green);
    return newDot;
}