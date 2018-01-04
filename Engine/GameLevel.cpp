#include "GameLevel.h"

GameLevel::GameLevel()
{
	Score = 0;
	mLevelState = LevelState::ePlaying;
}

GameLevel::~GameLevel()
{
	for (auto go : mGameObjects)
	{
		if (go)
		{
			delete go;
		}
	}
}

void GameLevel::CacheComponents(GameObject* gameObj, int renderLayer)
{
	mGameObjects.push_back(gameObj);

	switch (renderLayer)
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
	}

	ColliderComponent* goCollider = gameObj->GetComponent<ColliderComponent>();
	if (goCollider != nullptr)
	{
		mPhysicsManager.AddCollider(gameObj, goCollider);
	}

	DamageableComponent* goDamagable = gameObj->GetComponent<DamageableComponent>();
	if (goDamagable != nullptr)
	{
		mDamageableGameObjects.insert(std::make_pair(gameObj, goDamagable));
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

	int width = (int)std::abs(mLevelData.levelLeftBounds - mLevelData.levelRightBounds);
	width *= TILE_WIDTH;

	int height = (int)std::abs(mLevelData.levelTopBounds - mLevelData.levelBottomBounds);
	height *= TILE_HEIGHT;

	mPhysicsManager.BuildObjectGrid(width, height);
}

void GameLevel::PostBuildEvents()
{
	SetupCamera();
	RegisterFinishFlag();
}

void GameLevel::SetupCamera()
{
	GameCamera::Instance().SetFocusTrans(FindGameObject("Player")->GetComponent<TransformComponent>());

	GameCamera::Instance().SetLevelBounds(
		(mLevelData.levelLeftBounds) * TILE_WIDTH,
		(mLevelData.levelRightBounds) * TILE_WIDTH,
		(mLevelData.levelBottomBounds) * TILE_HEIGHT,
		(mLevelData.levelTopBounds) * TILE_HEIGHT);
}

void GameLevel::RegisterFinishFlag()
{
	GameObject* finishFlag = FindGameObject("FinishFlag");
	if (finishFlag == nullptr)
	{
		throw std::exception("No finish flag created in XML level!!!");
	}
	mFinishFlagTrigger = finishFlag->GetComponent<TriggerBoxComponent>();
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
	for (auto& dGo : mDamageableGameObjects)
	{
		// First is GameObject* and second is DamagableComponent*
		if (dGo.first->GetActive() && dGo.second->IsDead())
		{
			dGo.first->SetActive(false);

			if (dGo.first->GetTag() == "Player")
			{
				// Player died
				mLevelState = LevelState::eDead;
				Audio::Instance().PlaySoundEffect("Gameover");
			}
			else if (dGo.first->GetTag() == "Enemy")
			{
				// Increase score
				Audio::Instance().PlaySoundEffect("Death");
				Score++;
			}
		}
	}

	// Update gameobjects
	for (auto& go : mGameObjects)
	{
		go->Update(deltaTime);
	}

	// Check gameover
	if (mFinishFlagTrigger->GetTriggeredReference())
	{
		mLevelState = LevelState::eWon;
		Audio::Instance().PlaySoundEffect("Win");
	}
}

void GameLevel::Draw()
{
	// Draw gameobjects in the render order
	for (auto& go : mRenderLayer0)
	{
		go->Draw(&GameCamera::Instance());
	}

	for (auto& go : mRenderLayer1)
	{
		go->Draw(&GameCamera::Instance());
	}

	for (auto& go : mRenderLayer2)
	{
		go->Draw(&GameCamera::Instance());
	}
}

GameObject* GameLevel::FindGameObject(std::string tag)
{
	for (auto& go : mGameObjects)
	{
		if (go->GetTag() == tag)
			return go;
	}

	return nullptr;
}
