#pragma once

#include "ObjectManager.h"
#include "PhysicsManager.h"

using namespace std;

class Scene
{
public:
	Scene();
	~Scene();

	void Update(float deltaTime);
	void Draw(Camera& camera);

	void CacheComponents(shared_ptr<GameObject> gameObj);
	void SetupPhysics(LevelData levelData);

	int GetNumberOfGameObjects() { return (int)mGameObjects.size(); }
	shared_ptr<GameObject> GetGameObjectAtIndex(int index) { return mGameObjects.at(index); }

private:
	PhysicsManager										mPhysicsManager;
	LevelData											mLevelData;

	vector<shared_ptr<GameObject>>						mRenderLayer0;
	vector<shared_ptr<GameObject>>						mRenderLayer1;
	vector<shared_ptr<GameObject>>						mRenderLayer2;
	vector<shared_ptr<GameObject>>						mRenderLayer3;

	vector<shared_ptr<GameObject>>						mGameObjects;
};