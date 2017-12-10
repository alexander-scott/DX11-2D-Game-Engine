#pragma once

#include <string>

using namespace std;

class GameObject;

class IComponent
{
protected:
	string			_type;
	GameObject*		_gameObject;

public:
	virtual string GetType() { return _type; }

	void SetGameObject(GameObject* go) { _gameObject = go; }
	GameObject* GetGameObject() { return _gameObject; }
};