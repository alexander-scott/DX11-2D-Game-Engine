#include "EditorScene.h"

EditorScene::EditorScene(ICameraGameObject * cam) : IScene(cam)
{
}

EditorScene::~EditorScene()
{
	for (auto go : mGameObjects)
	{
		if (go)
		{
			go = nullptr;
		}
	}
}

void EditorScene::Update(float deltaTime)
{
	// UPDATE CAMERA
	mCamera->Update(deltaTime);
}

void EditorScene::CacheComponents(shared_ptr<GameObject> gameObj)
{
	mGameObjects.push_back(gameObj);

	for (auto component : gameObj->GetAllComponents())
	{
		IDrawable * drawableComponent = dynamic_cast<IDrawable *> (component);

		if (drawableComponent != nullptr)
		{
			mRenderLayers[drawableComponent->RenderLayer].push_back(gameObj);
		}
	}

	ProjectileManagerComponent* goProjManager = gameObj->GetComponent<ProjectileManagerComponent>();
	if (goProjManager != nullptr)
	{
		for (auto go : goProjManager->GetAllInactiveGameObjects())
		{
			mGameObjects.push_back(go);
		}
	}
}
