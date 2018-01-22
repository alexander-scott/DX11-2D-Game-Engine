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

void EditorScene::Draw()
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

void EditorScene::CacheComponents(shared_ptr<GameObject> gameObj)
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
}
