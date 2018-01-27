#pragma once

#include "IScene.h"

#include "ICameraGameObject.h"

class EditorScene :	public IScene
{
public:
	EditorScene(ICameraGameObject* cam);
	~EditorScene();

	void Update(float deltaTime) override;
	void CacheComponents(shared_ptr<GameObject> gameObj) override;
};

