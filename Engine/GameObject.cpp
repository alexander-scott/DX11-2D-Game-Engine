#include "GameObject.h"

GameObject::GameObject(string tag, int id)
{
	mTag = tag;
	mID = id;
	mParent = nullptr;
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

void GameObject::SetParent(shared_ptr<GameObject> parent)
{
	if (mParent != nullptr)
	{
		// Remove THIS GAMEOBJECT as a child from the previous parent
		mParent->RemoveChild(shared_ptr<GameObject>(this));
	}

	mParent = parent; // Set the new parent for THIS GAMEOBJECT

	// Set the parent transform in THIS GAMEOBJECT'S transform
	for (auto component : mComponents)
	{
		// Cast component to TransformComponent
		TransformComponent * transformComponent = dynamic_cast<TransformComponent *> (component);
		if (transformComponent != nullptr)
		{
			transformComponent->SetParent(mParent->GetComponent<TransformComponent>());
			break;
		}
	}

	if (mParent != nullptr)
	{
		mParent->AddChild(shared_ptr<GameObject>(this)); // Set THIS GAMEOBJECT as a child for the new parent
	}
}

void GameObject::AddChild(shared_ptr<GameObject> child)
{
	mChildren.push_back(child);
}

void GameObject::RemoveChild(shared_ptr<GameObject> child)
{
	// Remove a child from THIS GAMEOBJECTS vector of children
	auto it = std::find(mChildren.begin(), mChildren.end(), child);
	if (it != mChildren.end())
		mChildren.erase(it);
}

shared_ptr<GameObject> GameObject::MakeGameObject(string tag, int ID)
{
	auto gameObject = make_shared<GameObject>(tag, ID);
	return gameObject;
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