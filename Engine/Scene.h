#pragma once

#include "PhysicsManager.h"
#include "IScene.h"

#include "Camera.h"

using namespace std;

class Scene : public IScene
{
public:
	Scene();
	~Scene();

	void Update(float deltaTime) override;
	void Draw() override;
	void CacheComponents(shared_ptr<GameObject> gameObj) override;

private:
	void SetupPhysics();

	PhysicsManager										mPhysicsManager;
};