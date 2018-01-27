#pragma once

#include "PhysicsManager.h"
#include "IScene.h"

#include "ICameraGameObject.h"

using namespace std;

class PlayScene : public IScene
{
public:
	PlayScene(ICameraGameObject* cam);
	~PlayScene();

	void Update(float deltaTime) override;
	void CacheComponents(shared_ptr<GameObject> gameObj) override;

private:
	void SetupPhysics();

	PhysicsManager			mPhysicsManager;
};