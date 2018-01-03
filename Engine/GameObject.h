#pragma once

#include "DX11Graphics.h"
#include "Consts.h"

#include "IComponent.h"
#include "IUpdateable.h"
#include "IDrawable.h"
#include "IMessageable.h"

#include "ICamera.h"

class GameObject
{
public:
	GameObject(std::string tag);
	~GameObject();

	void Draw(ICamera* cam) const;

	virtual void Update(float deltaTime);

	void SendMessageToComponents(IMessage& message);
	void AddComponent(IComponent* component);

	std::string GetTag() { return mTag; }

	void SetActive(bool active);
	bool GetActive() { return mActive; }

	template<class T>
	T * GetComponent()
	{
		for (auto component : mComponents)
		{
			T* tComponent = dynamic_cast<T *> (component);

			if (tComponent != nullptr)
			{
				return tComponent;
			}
		}

		return nullptr;
	}

	template<class T>
	std::vector<T*> GetComponents()
	{
		std::vector<T*> components;
		for (auto component : mComponents)
		{
			T* tComponent = dynamic_cast<T *> (component);

			if (tComponent != nullptr)
			{
				components.push_back(tComponent);
			}
		}

		return components;
	}

protected:
	std::vector<IComponent*>	mComponents;
	std::string					mTag;
	bool						mActive;
};
