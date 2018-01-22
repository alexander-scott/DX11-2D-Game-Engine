#pragma once

#include "GameObject.h"
#include "ICameraGameObject.h"

using namespace std;

class IScene
{
public:
	IScene(ICameraGameObject* cam) : mCamera(cam) { }

	virtual void Update(float deltaTime) = 0;
	virtual void Draw() = 0;

	virtual void CacheComponents(shared_ptr<GameObject> gameObj) = 0;

	ICameraGameObject* GetCamera() { return mCamera; }
	int GetNumberOfGameObjects() { return (int)mGameObjects.size(); }
	shared_ptr<GameObject> GetGameObjectAtIndex(int index) { return mGameObjects.at(index); }

	LevelData											SceneData;

protected:
	vector<shared_ptr<GameObject>>						mRenderLayer0;
	vector<shared_ptr<GameObject>>						mRenderLayer1;
	vector<shared_ptr<GameObject>>						mRenderLayer2;
	vector<shared_ptr<GameObject>>						mRenderLayer3;

	vector<shared_ptr<GameObject>>						mGameObjects;

	ICameraGameObject*									mCamera;
};