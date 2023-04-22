#include "SFML/Graphics.hpp"
#include "Matrices.h"

#define ObjectController_H
#ifdef ObjectController_H
class ObjectController {
public:
	ObjectController() {};
	void addObject(GameObject& gameObject);
	std::vector<GameObject*>& getGameObjectVec();
	void keyMap(sf::Event& event, GameObject& object);
	void keyControl(GameObject& Object, Matrix4x4& translationMatrix);

private:
	void _setRandomColor(GameObject& object);
	std::vector<GameObject*> _gameObjectsVec;
};
#endif