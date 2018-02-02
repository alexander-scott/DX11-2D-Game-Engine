#pragma once

#include "Consts.h"

#include "IObject.h"
#include "IComponent.h"
#include "IUpdateable.h"
#include "IDrawable.h"
#include "IMessageable.h"

#include "ICamera.h"

using namespace std;

class GameObject : public IObject
{
public:
	GameObject(string tag, int id);
	~GameObject();

	void Draw(ICamera* cam) const;
	virtual void Update(float deltaTime);

	void SendMessageToComponents(IMessage& message);
	void AddComponent(IComponent* component);

	vector<IComponent*> GetAllComponents() { return mComponents; }

	void SetActive(bool active);
	bool GetActive() { return mActive; }

	void SetParent(shared_ptr<GameObject> parent);
	shared_ptr<GameObject> GetParent() { return mParent; }

	void AddChild(shared_ptr<GameObject> child);
	void RemoveChild(shared_ptr<GameObject> child);
	vector<shared_ptr<GameObject>> GetChildren() { return mChildren; }

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
	vector<IComponent*>				mComponents;
	shared_ptr<GameObject>			mParent;
	vector<shared_ptr<GameObject>>	mChildren;
	bool							mActive;
};
