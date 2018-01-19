#pragma once

#include "Consts.h"

#include "IComponent.h"
#include "IUpdateable.h"
#include "IDrawable.h"
#include "IMessageable.h"

#include "ICamera.h"

using namespace std;

class GameObject
{
public:
	GameObject(string tag, int id);
	~GameObject();

	void Draw(ICamera* cam) const;
	virtual void Update(float deltaTime);

	void SendMessageToComponents(IMessage& message);
	void AddComponent(IComponent* component);

	string GetTag() { return mTag; }
	int GetID() { return mID; }
	vector<IComponent*> GetAllComponents() { return mComponents; }

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
	vector<T*> GetComponents()
	{
		vector<T*> components;
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

	template<class T>
	void RemoveComponent()
	{
		for (int i = 0; i < mComponents.size(); i++)
		{
			T* tComponent = dynamic_cast<T *> (mComponents[i]);

			if (tComponent != nullptr)
			{
				mComponents.erase(mComponents.begin() + i);
				delete tComponent;
				return;
			}
		}
	}

	static shared_ptr<GameObject> MakeGameObject(string tag, int ID);

protected:
	vector<IComponent*>		mComponents;
	string					mTag;
	int						mID;
	bool					mActive;
};
