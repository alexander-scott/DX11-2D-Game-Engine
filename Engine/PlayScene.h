#pragma once

#include "PhysicsManager.h"
#include "IScene.h"

#include "Camera.h"

using namespace std;

class PlayScene : public IScene
{
public:
	PlayScene(Camera* cam);
	~PlayScene();

	void Update(float deltaTime) override;
	void Draw() override;
	void CacheComponents(shared_ptr<GameObject> gameObj) override;

private:
	void SetupPhysics();

	PhysicsManager			mPhysicsManager;
};