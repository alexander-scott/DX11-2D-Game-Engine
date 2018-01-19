#include "Scene.h"

Scene::Scene()
{

}

Scene::~Scene()
{
	for (auto go : mGameObjects)
	{
		if (go)
		{
			go = nullptr;
		}
	}
}

void Scene::CacheComponents(shared_ptr<GameObject> gameObj)
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

			break;
		}
	}

	ColliderComponent* goCollider = gameObj->GetComponent<ColliderComponent>();
	if (goCollider != nullptr)
	{
		mPhysicsManager.AddCollider(gameObj, goCollider);
	}

	ProjectileManagerComponent* goProjManager = gameObj->GetComponent<ProjectileManagerComponent>();
	if (goProjManager != nullptr)
	{
		for (auto go : goProjManager->GetAllInactiveGameObjects())
		{
			mPhysicsManager.AddCollider(go, go->GetComponent<ColliderComponent>());
		}
	}
}

void Scene::SetupPhysics(LevelData levelData)
{
	mLevelData = levelData;

	int width = (int)abs(mLevelData.levelLeftBounds - mLevelData.levelRightBounds);
	width *= 2;

	int height = (int)abs(mLevelData.levelTopBounds - mLevelData.levelBottomBounds);
	height *= 2;

	mPhysicsManager.BuildObjectGrid(width, height);
}

void Scene::Update(float deltaTime)
{
	// Update object rigid bodies
	mPhysicsManager.Update(deltaTime);

	// Update gameobjects
	for (auto& go : mGameObjects)
	{
		go->Update(deltaTime);
	}

}

void Scene::Draw()
{
	// Draw gameobjects in the render order
	for (auto& go : mRenderLayer0)
	{
		go->Draw(&Camera::Instance());
	}

	for (auto& go : mRenderLayer1)
	{
		go->Draw(&Camera::Instance());
	}

	for (auto& go : mRenderLayer2)
	{
		go->Draw(&Camera::Instance());
	}

	for (auto& go : mRenderLayer3)
	{
		go->Draw(&Camera::Instance());
	}
}
