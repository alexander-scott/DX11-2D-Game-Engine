#include "GameObject.h"

GameObject::GameObject(std::string tag)
{
	mTag = tag;
}

GameObject::~GameObject()
{
	for (auto component : mComponents)
	{
		delete component;
		component = nullptr;
	}
}

void GameObject::AddComponent(IComponent * component)
{
	if (component != nullptr)
	{
		mComponents.push_back(component);
	}
}

void GameObject::SetActive(bool active)
{
	mActive = active;
	for (auto component : mComponents)
	{
		component->SetActive(active);
	}
}

void GameObject::SendMessageToComponents(IMessage & message)
{
	for (auto component : mComponents)
	{
		if (component->GetActive())
		{
			// Cast component to IMessageable
			IMessageable * messageableComponent = dynamic_cast<IMessageable *> (component);

			if (messageableComponent != nullptr)
			{
				// Is messageable
				messageableComponent->RecieveMessage(message);
			}
		}
	}
}

void GameObject::Draw(ICamera* cam) const
{
	for (auto component : mComponents)
	{
		if (component->GetActive())
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
}

void GameObject::Update(float deltaTime)
{
	// Update all updateable components
	for (auto component : mComponents)
	{
		if (component->GetActive())
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
}