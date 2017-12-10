#include "GameObject.h"

GameObject::GameObject(std::string tag)
{
	_tag = tag;
}

GameObject::~GameObject()
{
	for (auto component : _components)
	{
		delete component;
		component = nullptr;
	}
}

void GameObject::AddComponent(IComponent * component)
{
	if (component != nullptr)
	{
		_components.push_back(component);
	}
}

void GameObject::SendMessageToComponents(IMessage & message)
{
	for (auto component : _components)
	{
		// Cast component to IDrawable
		IMessageable * messageableComponent = dynamic_cast<IMessageable *> (component);

		if (messageableComponent != nullptr)
		{
			// Is drawable
			messageableComponent->RecieveMessage(message);
		}
	}
}

void GameObject::Draw(ICamera* cam) const
{
	for (auto component : _components)
	{
		// Cast component to IDrawable
		IDrawable * drawableComponent = dynamic_cast<IDrawable *> (component);

		if (drawableComponent != nullptr)
		{
			// Is drawable
			drawableComponent->Draw(cam);
		}
	}
}

void GameObject::Update(float deltaTime)
{
	// Update all updateable components
	for (auto component : _components)
	{
		// Cast component to IUpdateable - This is bad!!
		IUpdateable * updateableComponent = dynamic_cast<IUpdateable *> (component);

		if (updateableComponent != nullptr)
		{
			// Is updateable
			updateableComponent->Update(deltaTime);
		}
	}
}