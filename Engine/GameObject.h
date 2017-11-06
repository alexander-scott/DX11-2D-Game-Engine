#pragma once

#include "Graphics.h"
#include "Animation.h"
#include "Consts.h"

#include "IComponent.h"
#include "IUpdateable.h"
#include "IDrawable.h"

class GameObject
{
public:
	virtual void Init(const std::string& fileName);

	virtual void Draw(Graphics& gfx) const;
	virtual void Update(float deltaTime);

	void AddComponent(IComponent* component);

	~GameObject();

private :
	std::vector<IComponent*> _components;

protected:
	std::string				_fileName;
};