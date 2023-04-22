#include "ObjectController.h"

void ObjectController::addObject(GameObject& gameObject) {
    _gameObjectsVec.push_back(&gameObject);
}
std::vector<GameObject*>& ObjectController::getGameObjectVec() {
    return _gameObjectsVec;
}

void ObjectController::keyMap(sf::Event& event, GameObject& object)
{
    if (event.type == event.KeyPressed)
    {
        switch (event.key.code) {
        case sf::Keyboard::Numpad4:
            object.rotation.left = true;
            break;
        case sf::Keyboard::Numpad6:
            object.rotation.right = true;
            break;
        case sf::Keyboard::Numpad8:
            object.rotation.up = true;
            break;
        case sf::Keyboard::Numpad5:
            object.rotation.down = true;
            break;
        case sf::Keyboard::Numpad7:
            object.rotation.spinLeft = true;
            break;
        case sf::Keyboard::Numpad9:
            object.rotation.spinRight = true;
            break;
        case sf::Keyboard::A:
            object.movement.left = true;
            break;
        case sf::Keyboard::D:
            object.movement.right = true;
            break;
        case sf::Keyboard::Space:
            object.movement.up = true;
            break;
        case sf::Keyboard::LControl:
            object.movement.down = true;
            break;
        case sf::Keyboard::W:
            object.movement.forwards = true;
            break;
        case sf::Keyboard::S:
            object.movement.backwards = true;
            break;
        case sf::Keyboard::V:
            if (object.mode.onColorChange == false) {
                _setRandomColor(object);
                object.mode.onColorChange = true;
            }
            break;

        case sf::Keyboard::Add:
            if (object.mode.onSpeedChange == false)
            {
                object.rotation.speed += 0.3f;
                object.movement.speed += 0.01f;
            }
            object.mode.onSpeedChange = true;
            break;
        case sf::Keyboard::Subtract:
            if (object.mode.onSpeedChange == false)
            {
                object.rotation.speed -= 0.3f;
                object.movement.speed -= 0.01f;
            }
            object.mode.onSpeedChange = true;
            break;

        case sf::Keyboard::P:
            object.mode.drawPoints = !object.mode.drawPoints; 
            break;
        case sf::Keyboard::L:
            object.mode.drawLines = !object.mode.drawLines;
            break;
        case sf::Keyboard::C:
            object.mode.drawColors = !object.mode.drawColors;
            break;
        }
    }
    if (event.type == event.KeyReleased)
    {
        switch (event.key.code) {
        case sf::Keyboard::Numpad4:
            object.rotation.left = false;
            break;
        case sf::Keyboard::Numpad6:
            object.rotation.right = false;
            break;
        case sf::Keyboard::Numpad8:
            object.rotation.up = false;
            break;
        case sf::Keyboard::Numpad5:
            object.rotation.down = false;
            break;
        case sf::Keyboard::Numpad7:
            object.rotation.spinLeft = false;
            break;
        case sf::Keyboard::Numpad9:
            object.rotation.spinRight = false;
            break;
        case sf::Keyboard::A:
            object.movement.left = false;
            break;
        case sf::Keyboard::D:
            object.movement.right = false;
            break;
        case sf::Keyboard::Space:
            object.movement.up = false;
            break;
        case sf::Keyboard::LControl:
            object.movement.down = false;
            break;
        case sf::Keyboard::W:
            object.movement.forwards = false;
            break;
        case sf::Keyboard::S:
            object.movement.backwards = false;
            break;
        case sf::Keyboard::V:
            object.mode.onColorChange = false;
            break;
        case sf::Keyboard::Add:
                object.mode.onSpeedChange = false;
            break;
        case sf::Keyboard::Subtract:
            object.mode.onSpeedChange = false;
            break;
        }
    }
}


void ObjectController::keyControl(GameObject& Object, Matrix4x4& translationMatrix)
{
    if (Object.rotation.left == true)
        Object.rotation.getAngle().y -= Object.rotation.speed;
    if (Object.rotation.right == true)
        Object.rotation.getAngle().y += Object.rotation.speed;
    if (Object.rotation.up == true)
        Object.rotation.getAngle().x -= Object.rotation.speed;
    if (Object.rotation.down == true)
        Object.rotation.getAngle().x += Object.rotation.speed;
    if (Object.rotation.spinLeft == true)
        Object.rotation.getAngle().z -= Object.rotation.speed;
    if (Object.rotation.spinRight == true)
        Object.rotation.getAngle().z += Object.rotation.speed;
    if (Object.movement.left == true)
        translationMatrix.m[0][3] -= Object.movement.speed;
    if (Object.movement.right == true)
        translationMatrix.m[0][3] += Object.movement.speed;
    if (Object.movement.up == true)
        translationMatrix.m[1][3] -= Object.movement.speed;
    if (Object.movement.down == true)
        translationMatrix.m[1][3] += Object.movement.speed;
    if (Object.movement.forwards == true)
        translationMatrix.m[2][3] += Object.movement.speed;
    if (Object.movement.backwards == true)
        translationMatrix.m[2][3] -= Object.movement.speed;

}


void ObjectController::_setRandomColor(GameObject& object)
{
    int random[3] = { 0, 0, 0 };
    for (int i = 0; i < object.getTrianglesSize(); i++)
    {
        for (int p = 0; p < 3; p++)
        {
            random[p] = rand() & 254 + 1;
        }
        object.getTriangle(i).SetFillColor(sf::Color(random[0], random[1], random[2]));
    }
}