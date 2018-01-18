#include "GameLevel.h"

GameLevel::GameLevel(float startScore) : mScore(startScore)
{
	mLevelState = LevelState::ePlaying;
}

GameLevel::~GameLevel()
{
	for (auto go : mGameObjects)
	{
		if (go)
		{
			go = nullptr;
		}
	}
}

void GameLevel::CacheComponents(shared_ptr<GameObject> gameObj)
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

	DamageableComponent* goDamagable = gameObj->GetComponent<DamageableComponent>();
	if (goDamagable != nullptr)
	{
		mDamageableGameObjects.insert(make_pair(gameObj, goDamagable));
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

void GameLevel::ConstructLevel(LevelData levelData)
{
	mLevelData = levelData;

	int width = (int)abs(mLevelData.levelLeftBounds - mLevelData.levelRightBounds);
	width *= TILE_WIDTH;

	int height = (int)abs(mLevelData.levelTopBounds - mLevelData.levelBottomBounds);
	height *= TILE_HEIGHT;

	mPhysicsManager.BuildObjectGrid(width, height);
}

void GameLevel::ConstructionComplete()
{
	RegisterFinishFlag();
}

void GameLevel::RegisterFinishFlag()
{
	auto finishFlagGO = FindGameObject("FinishFlag");
	if (finishFlagGO == nullptr)
	{
		throw exception("No finish flag created in XML level!!!");
	}
	mFinishFlagTrigger = finishFlagGO->GetComponent<TriggerBoxComponent>();
}

void GameLevel::Update(float deltaTime)
{
	// Update object rigid bodies
	mPhysicsManager.Update(deltaTime);

	if (mLevelState != LevelState::ePlaying)
	{
		return;
	}

	// Check all objects that can be damaged to see if they are dead or not. Do something additional if the object that died is special or not
	//for (auto& dGo : mDamageableGameObjects)
	//{
	//	// First is GameObject* and second is DamagableComponent*
	//	if (dGo.first->GetActive() && dGo.second->IsDead())
	//	{
	//		dGo.first->SetActive(false);

	//		if (dGo.first->GetTag() == "Player")
	//		{
	//			// Player died
	//			mLevelState = LevelState::eDead;
	//			Audio::Instance().PlaySoundEffect("Gameover");
	//		}
	//		else if (dGo.first->GetTag() == "Enemy")
	//		{
	//			// Increase score
	//			Audio::Instance().PlaySoundEffect("Death");
	//			mScore++;
	//		}
	//	}
	//}

	// Update gameobjects
	for (auto& go : mGameObjects)
	{
		go->Update(deltaTime);
	}

	// Check gameover
	/*if (mFinishFlagTrigger->GetTriggeredReference())
	{
		mLevelState = LevelState::eWon;
		Audio::Instance().PlaySoundEffect("Win");
		mScore += 10;
	}*/
}

void GameLevel::Draw()
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

shared_ptr<GameObject> GameLevel::FindGameObject(string tag)
{
	for (auto& go : mGameObjects)
	{
		if (go->GetTag() == tag)
			return go;
	}

	return nullptr;
}
