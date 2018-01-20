#pragma once

#include "ObjectManager.h"
#include "PhysicsManager.h"
#include "IScene.h"

using namespace std;

class Scene : public IScene
{
public:
	Scene();
	~Scene();

	void Update(float deltaTime) override;
	void Draw() override;
	void CacheComponents(shared_ptr<GameObject> gameObj) override;

	void SetupPhysics(LevelData levelData);

private:
	PhysicsManager										mPhysicsManager;
};