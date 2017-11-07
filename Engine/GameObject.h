#pragma once

#include "Graphics.h"
#include "Consts.h"

#include "IComponent.h"
#include "IUpdateable.h"
#include "IDrawable.h"
#include "IMessageable.h"

class GameObject
{
public:
	void Draw(Graphics& gfx) const;
	void Update(float deltaTime);
	void SendMessageToComponents(IMessage& message);

	void AddComponent(IComponent* component);

	~GameObject();

private :
	std::vector<IComponent*> _components;
};