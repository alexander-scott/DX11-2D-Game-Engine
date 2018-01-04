#include "GameLevel.h"

GameLevel::GameLevel()
{
	mScore = 0;


}

GameLevel::~GameLevel()
{
	for (auto go : mGameObjects)
	{
		if (go) // TODO: UMCOMMENTING THIS OUT CREATES A DELETION BUG ON WINDOW CLOSE
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

	BuildCustomObjects();
}

void GameLevel::BuildCustomObjects()
{
	GameObject* finishFlag = new GameObject("FinishFlag");
	TransformComponent* flagTrans = ComponentFactory::MakeTransform(Vec2(150, -30), 0, 1);
	finishFlag->AddComponent(flagTrans);
	SpriteRendererComponent* flagRenderer = ComponentFactory::MakeSpriteRenderer("FinishFlag", flagTrans, 64, 64, Vec2(0, 0));
	finishFlag->AddComponent(flagRenderer);
	RigidBodyComponent* flagRB = ComponentFactory::MakeRigidbody(0, 0, 0, false, false);
	flagRB->SetActive(false);
	finishFlag->AddComponent(flagRB);
	BoxColliderComponent* flagCollider = ComponentFactory::MakeBoxCollider(64, 64, flagTrans, flagRB);
	finishFlag->AddComponent(flagCollider);
	TriggerBoxComponent* flagTriggerBox = ComponentFactory::MakeTriggerBox("Player");
	finishFlag->AddComponent(flagTriggerBox);
	CacheComponents(finishFlag, 2);
}

void GameLevel::BuildGUI()
{
	GameObject* scoreText = new GameObject("Text");
	TransformComponent* scoreTransform = ComponentFactory::MakeTransform(Vec2(10, 10), 0, 0.5f);
	scoreText->AddComponent(scoreTransform);
	scoreText->AddComponent(ComponentFactory::MakeGUITextValueComponent("Score:", DirectX::Colors::Yellow, scoreTransform, mScore));
	CacheComponents(scoreText, 2);

	GameObject* healthText = new GameObject("Text");
	TransformComponent* healthTransform = ComponentFactory::MakeTransform(Vec2(SCREEN_WIDTH - 130, 10), 0, 0.5f);
	healthText->AddComponent(healthTransform);
	healthText->AddComponent(ComponentFactory::MakeGUITextValueComponent("Health:", DirectX::Colors::Red, healthTransform, FindGameObject("Player")->GetComponent<DamageableComponent>()->GetHealthAddress()));
	CacheComponents(healthText, 2);
}

void GameLevel::BuildCamera()
{
	GameCamera::Instance().SetFocusTrans(FindGameObject("Player")->GetComponent<TransformComponent>());

	GameCamera::Instance().SetLevelBounds(
		(mLevelData.levelLeftBounds) * TILE_WIDTH,
		(mLevelData.levelRightBounds) * TILE_WIDTH,
		(mLevelData.levelBottomBounds) * TILE_HEIGHT,
		(mLevelData.levelTopBounds) * TILE_HEIGHT);

	CacheComponents(&GameCamera::Instance(), -1);
}

void GameLevel::Update(float deltaTime)
{
	// Update object rigid bodies
	mPhysicsManager.Update(deltaTime);

	// Check all objects that can be damaged to see if they are dead or not. Do something additional if the object that died is special or not
	for (auto& dGo : mDamageableGameObjects)
	{
		// First is GameObject* and second is DamagableComponent*
		if (dGo.first->GetActive() && dGo.second->IsDead())
		{
			dGo.first->SetActive(false);

			if (dGo.first->GetTag() == "Player")
			{
				// PLAYER IS DEAD MAJOR PANIC @@@@@@@@@@@@@@@@@
			}
			else if (dGo.first->GetTag() == "Enemy")
			{
				// Increase score
				Audio::Instance().PlaySoundEffect("Death");
				mScore++;
			}
		}
	}

	// Update gameobjects
	for (auto& go : mGameObjects)
	{
		go->Update(deltaTime);
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
