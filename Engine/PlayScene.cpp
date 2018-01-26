#include "PlayScene.h"

PlayScene::PlayScene(ICameraGameObject * cam) : IScene(cam)
{
}

PlayScene::~PlayScene()
{
	for (auto go : mGameObjects)
	{
		if (go)
		{
			go = nullptr;
		}
	}
}

void PlayScene::CacheComponents(shared_ptr<GameObject> gameObj)
{
	mGameObjects.push_back(gameObj);

	for (auto component : gameObj->GetAllComponents())
	{
		IDrawable * drawableComponent = dynamic_cast<IDrawable *> (component);

		if (drawableComponent != nullptr)
		{
			switch (drawableComponent->RenderLayer)
			{
				case 0:
					mRenderLayer0.push_back(gameObj);
					break;
				case 1:
					mRenderLayer1.push_back(gameObj);
					break;
				case 2:
					mRenderLayer2.push_back(gameObj);
					break;
				case 3:
					mRenderLayer3.push_back(gameObj);
					break;
			}
		}
	}

	ColliderComponent* goCollider = gameObj->GetComponent<ColliderComponent>();
	if (goCollider != nullptr)
	{
		if (!mPhysicsManager.GetSetup())
			SetupPhysics();

		mPhysicsManager.AddCollider(gameObj, goCollider);
	}

	ProjectileManagerComponent* goProjManager = gameObj->GetComponent<ProjectileManagerComponent>();
	if (goProjManager != nullptr)
	{
		for (auto go : goProjManager->GetAllInactiveGameObjects())
		{
			mGameObjects.push_back(go);
			mPhysicsManager.AddCollider(go, go->GetComponent<ColliderComponent>());
		}
	}
}

void PlayScene::SetupPhysics()
{
	int width = (int)abs(SceneData.levelLeftBounds - SceneData.levelRightBounds);
	width *= 2;

	int height = (int)abs(SceneData.levelTopBounds - SceneData.levelBottomBounds);
	height *= 2;

	mPhysicsManager.BuildObjectGrid(width, height);
}

void PlayScene::Update(float deltaTime)
{
	mCamera->Update(deltaTime);

	// Update object rigid bodies
	mPhysicsManager.Update(deltaTime);

	// Update gameobjects
	for (auto& go : mGameObjects)
	{
		go->Update(deltaTime);
	}

}

void PlayScene::Draw()
{
	// Draw gameobjects in the render order
	for (auto& go : mRenderLayer0)
	{
		go->Draw(mCamera);
	}

	for (auto& go : mRenderLayer1)
	{
		go->Draw(mCamera);
	}

	for (auto& go : mRenderLayer2)
	{
		go->Draw(mCamera);
	}

	for (auto& go : mRenderLayer3)
	{
		go->Draw(mCamera);
	}
}
