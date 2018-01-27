#pragma once

#include "GameObject.h"
#include "ICameraGameObject.h"

using namespace std;

class IScene
{
public:
	IScene(ICameraGameObject* cam) : mCamera(cam) { }

	void Draw();

	virtual void Update(float deltaTime) = 0;
	virtual void CacheComponents(shared_ptr<GameObject> gameObj) = 0;

	ICameraGameObject* GetCamera() { return mCamera; }
	int GetNumberOfGameObjects() { return (int)mGameObjects.size(); }
	shared_ptr<GameObject> GetGameObjectAtIndex(int index) { return mGameObjects.at(index); }

	LevelData											SceneData;

protected:
	map<int, vector<shared_ptr<GameObject>>>			mRenderLayers;
	vector<shared_ptr<GameObject>>						mGameObjects;

	ICameraGameObject*									mCamera;
};