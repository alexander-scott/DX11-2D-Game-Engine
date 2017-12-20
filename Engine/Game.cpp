#include "Game.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd)
{
	_camera = new GameCamera("Camera");
	_camera->Initalise(wnd);

	_gameLevel.Initalise(_camera);
	_gameLevel.BuildLevel("Levels\\Level1.xml");

	//_gameObjects.push_back(_camera);

	//InitaliseLevel();

	//CacheSpecificComponents();
}

// Read in level data from an XML file and build the level
void Game::InitaliseLevel()
{
	// Init LevelManager (xStep, yStep, xOrigin, yOrigin)
	GameLevelManager levelManager(TILE_WIDTH, TILE_HEIGHT, 0, 0);
	levelManager.LoadLevel("Levels\\Level1Map.xml");

	// Build any objects that are dependecies to other objects (global vars). Such as player.
	InitaliseImportantObjects(levelManager.GetLevelData());

	// Build the background and add that first as that needs to get renderered at the very back
	InitaliseBackground(levelManager.GetLevelData());

	// Build any other objects that need drawing
	InitaliseObjects(levelManager.GetLevelData());

	// Build the tile level
	for (int i = 0; i < levelManager.GetLevelData().levelWidth; i++)
	{
		for (int j = 0; j < levelManager.GetLevelData().levelHeight; j++)
		{
			WorldTile* t = levelManager.GetTile(i, j);
			if (t != nullptr)
			{
				_gameObjects.push_back(t);
			}
		}
	}

	// Add the player last as that will need to be rendered above everything
	_gameObjects.push_back(_player);

	// GUI must always exist on top of everything
	InitaliseGUI();
}

// Create any objects which are dependecies to other objects
void Game::InitaliseImportantObjects(LevelData & levelData)
{
	_player = new GameObject("Player");

	// Initalise the players transform as this is needed by the parallax backgrounds
	TransformComponent* playerTransform = ComponentFactory::MakeTransform(Vec2(levelData.playerXPos, levelData.playerYPos), 0, 1);
	_player->AddComponent(playerTransform);
}

// Create any other objects
void Game::InitaliseObjects(LevelData & levelData)
{
	TransformComponent* playerTransform = _player->GetComponent<TransformComponent>();

	RigidBodyComponent* playerRigidBody = ComponentFactory::MakeRigidbody(0.5f, 0.3f, 0.5f, false, true);
	_player->AddComponent(playerRigidBody);

	BoxColliderComponent* playerCollider = ComponentFactory::MakeBoxCollider(64, 64, playerTransform, playerRigidBody);
	_player->AddComponent(playerCollider);

	std::vector<AnimationDesc> animDescs;
	animDescs.push_back(AnimationDesc(0, 4, 64, 64, 64, 64, 8, 0.16f)); // Walking
	animDescs.push_back(AnimationDesc(4, 8, 0, 64, 64, 64, 1, 0.16f)); // Standing

	SpriteAnimatorComponent* playerAnimator = ComponentFactory::MakeSpriteAnimator("MageWalk", playerTransform, 64, 64, animDescs, (int)AnimationType::StandingDown);
	_player->AddComponent(playerAnimator);

	DamageableComponent* playerDamageable = ComponentFactory::MakeDamageableComponent(100);
	_player->AddComponent(playerDamageable);

	ProjectileManagerComponent* playerProjectiles = new ProjectileManagerComponent;
	for (int i = 0; i < 100; i++)
	{
		GameObject* ball = new GameObject("Ball");
		TransformComponent* ballTrans = ComponentFactory::MakeTransform(Vec2(0, 0), 0, 0.2f);
		ball->AddComponent(ballTrans);
		RigidBodyComponent* ballRb = ComponentFactory::MakeRigidbody(1, 0.3f, 0.5f, false, false); // Cache the rigidbody
		ball->AddComponent(ballRb);
		CircleColliderComponent* ballCollider = ComponentFactory::MakeCircleCollider(64, ballTrans, ballRb);
		ball->AddComponent(ballCollider);
		SpriteRendererComponent* ballRenderer = ComponentFactory::MakeSpriteRenderer("Ball", ballTrans, 128, 128, Vec2(0, 0));
		ball->AddComponent(ballRenderer);
		ProjectileComponent* ballProjectile = ComponentFactory::MakeProjectileComponent("Enemy", 10, 10);
		ball->AddComponent(ballProjectile);

		_gameObjects.push_back(ball);

		playerProjectiles->AddCreatedGameObject(ball);
	}
	_player->AddComponent(playerProjectiles);

	PlayerComponent* playerComponent = ComponentFactory::MakePlayerComponent(playerTransform, playerAnimator, playerRigidBody, playerDamageable, playerProjectiles, _camera->GetComponent<TransformComponent>());
	_player->AddComponent(playerComponent);

	GameObject* aiAgent = new GameObject("Enemy");
	TransformComponent* agentTransform = ComponentFactory::MakeTransform(Vec2(levelData.playerXPos + 400, levelData.playerYPos), 0, 1);

	RigidBodyComponent* agentRigidBody = ComponentFactory::MakeRigidbody(0.5f, 0.3f, 0.5f, false, true);
	agentRigidBody->LockRotation();
	aiAgent->AddComponent(agentRigidBody);

	BoxColliderComponent* agentCollider = ComponentFactory::MakeBoxCollider(64, 64, agentTransform, agentRigidBody);
	aiAgent->AddComponent(agentCollider);

	SpriteAnimatorComponent* agentAnimator = ComponentFactory::MakeSpriteAnimator("MageWalk", agentTransform, 64, 64, animDescs, (int)AnimationType::StandingDown);
	aiAgent->AddComponent(agentAnimator);

	DamageableComponent* agentDamageable = ComponentFactory::MakeDamageableComponent(100);
	aiAgent->AddComponent(agentDamageable);

	ProjectileManagerComponent* agentProjectiles = new ProjectileManagerComponent;
	for (int i = 0; i < 100; i++)
	{
		GameObject* ball = new GameObject("Ball");
		TransformComponent* ballTrans = ComponentFactory::MakeTransform(Vec2(0, 0), 0, 0.2f);
		ball->AddComponent(ballTrans);
		RigidBodyComponent* ballRb = ComponentFactory::MakeRigidbody(1, 0.3f, 0.5f, false, false); // Cache the rigidbody
		ball->AddComponent(ballRb);
		CircleColliderComponent* ballCollider = ComponentFactory::MakeCircleCollider(64, ballTrans, ballRb);
		ball->AddComponent(ballCollider);
		SpriteRendererComponent* ballRenderer = ComponentFactory::MakeSpriteRenderer("Ball", ballTrans, 128, 128, Vec2(0, 0));
		ball->AddComponent(ballRenderer);
		ProjectileComponent* ballProjectile = ComponentFactory::MakeProjectileComponent("Player", 10, 10);
		ball->AddComponent(ballProjectile);

		_gameObjects.push_back(ball);

		agentProjectiles->AddCreatedGameObject(ball);
	}
	aiAgent->AddComponent(agentProjectiles);

	AIAgentComponent* agentAI = ComponentFactory::MakeAIAgentComponent(agentTransform, agentAnimator, agentRigidBody, agentDamageable, agentProjectiles, _camera->GetComponent<TransformComponent>(), 5, AIAgentPatrolDirection::ePatrollingRight, 1);
	aiAgent->AddComponent(agentAI);

	_gameObjects.push_back(aiAgent);
}

// Create objects that draw the background. Also create level limit colliders. Also create the camera and define it's bounds.
void Game::InitaliseBackground(LevelData& levelData)
{
	_camera->SetFocusTrans(_player->GetComponent<TransformComponent>());

	_camera->SetLevelBounds((levelData.levelLeftBounds) * TILE_WIDTH,
		(levelData.levelRightBounds) * TILE_WIDTH,
		(levelData.levelBottomBounds) * TILE_HEIGHT,
		(levelData.levelTopBounds) * TILE_HEIGHT);

	GameObject* skyBackground = new GameObject("Background");
	TransformComponent* skyTrans = ComponentFactory::MakeTransform(Vec2(0, 0), 0, 1);
	skyBackground->AddComponent(skyTrans);
	skyBackground->AddComponent(ComponentFactory::MakeTiledBGRenderer("BG_Sky", 640, 480, 0.1f,
		TiledBGDirection::eHoriztonalAndVertical, skyTrans, _player->GetComponent<TransformComponent>()));
	_gameObjects.push_back(skyBackground);

	GameObject* vegBackground = new GameObject("Background");
	TransformComponent* vegTrans = ComponentFactory::MakeTransform(Vec2(0, -400), 0, 1);
	vegBackground->AddComponent(vegTrans);
	vegBackground->AddComponent(ComponentFactory::MakeTiledBGRenderer("BG_Vegetation", 640, 480, 0.5f,
		TiledBGDirection::eHorizontal, vegTrans, _player->GetComponent<TransformComponent>()));
	_gameObjects.push_back(vegBackground);

	GameObject* groundBackground = new GameObject("Background");
	TransformComponent* groundTrans = ComponentFactory::MakeTransform(Vec2(0, -400), 0, 1);
	groundBackground->AddComponent(groundTrans);
	groundBackground->AddComponent(ComponentFactory::MakeTiledBGRenderer("BG_Ground", 640, 480, 3,
		TiledBGDirection::eHorizontal, groundTrans, _player->GetComponent<TransformComponent>()));
	_gameObjects.push_back(groundBackground);

	GameObject* leftSideCollider = new GameObject("LevelCollider");
	TransformComponent* leftSideTrans = ComponentFactory::MakeTransform(Vec2(levelData.levelLeftBounds * TILE_WIDTH, 0), 0, 1);
	leftSideCollider->AddComponent(leftSideTrans);
	RigidBodyComponent* leftSideRb = ComponentFactory::MakeRigidbody(1, 1, 1, true, false);
	leftSideCollider->AddComponent(leftSideRb);

	Vec2 *vertices = new Vec2[4];
	vertices[0].Set(1, 10000); // Bot right
	vertices[1].Set(-1, 10000); // Bot left
	vertices[2].Set(1, -10000); // Top right
	vertices[3].Set(-1, -10000); // Top left
	PolygonColliderComponent* leftSidePolyCollide = ComponentFactory::MakePolygonCollider(vertices, 4, leftSideTrans, leftSideRb);
	leftSideCollider->AddComponent(leftSidePolyCollide);
	leftSideRb->SetStatic();
	_gameObjects.push_back(leftSideCollider);

	GameObject* rightSideCollider = new GameObject("LevelCollider");
	TransformComponent* rightSideTrans = ComponentFactory::MakeTransform(Vec2(levelData.levelRightBounds * TILE_WIDTH, 0), 0, 1);
	rightSideCollider->AddComponent(rightSideTrans);
	RigidBodyComponent* rightSideRb = ComponentFactory::MakeRigidbody(1, 1, 1, true, false);
	rightSideCollider->AddComponent(rightSideRb);

	vertices = new Vec2[4];
	vertices[0].Set(1, 10000); // Bot right
	vertices[1].Set(-1, 10000); // Bot left
	vertices[2].Set(1, -10000); // Top right
	vertices[3].Set(-1, -10000); // Top left
	PolygonColliderComponent* rightSidePolyCollide = ComponentFactory::MakePolygonCollider(vertices, 4, rightSideTrans, rightSideRb);
	rightSideCollider->AddComponent(rightSidePolyCollide);
	rightSideRb->SetStatic();
	_gameObjects.push_back(rightSideCollider);

	GameObject* bottomSideCollider = new GameObject("LevelCollider");
	TransformComponent* bottomSideTrans = ComponentFactory::MakeTransform(Vec2(0, levelData.levelBottomBounds * TILE_HEIGHT), 0, 1);
	bottomSideCollider->AddComponent(bottomSideTrans);
	RigidBodyComponent* bottomSideRb = ComponentFactory::MakeRigidbody(1, 1, 1, true, false);
	bottomSideCollider->AddComponent(bottomSideRb);

	vertices = new Vec2[4];
	vertices[0].Set(10000, 1); // Bot right
	vertices[1].Set(10000, -1); // Bot left
	vertices[2].Set(-10000, 1); // Top right
	vertices[3].Set(-10000, -1); // Top left
	PolygonColliderComponent* bottomSidePolyCollide = ComponentFactory::MakePolygonCollider(vertices, 4, bottomSideTrans, bottomSideRb);
	bottomSideCollider->AddComponent(bottomSidePolyCollide);
	bottomSideRb->SetStatic();
	_gameObjects.push_back(bottomSideCollider);

	GameObject* topSideCollider = new GameObject("LevelCollider");
	TransformComponent* topSideTrans = ComponentFactory::MakeTransform(Vec2(0, levelData.levelTopBounds * TILE_HEIGHT), 0, 1);
	topSideCollider->AddComponent(topSideTrans);
	RigidBodyComponent* topSideRb = ComponentFactory::MakeRigidbody(1, 1, 1, true, false);
	topSideCollider->AddComponent(topSideRb);

	vertices = new Vec2[4];
	vertices[0].Set(10000, 1); // Bot right
	vertices[1].Set(10000, -1); // Bot left
	vertices[2].Set(-10000, 1); // Top right
	vertices[3].Set(-10000, -1); // Top left
	PolygonColliderComponent* topSidePolyCollide = ComponentFactory::MakePolygonCollider(vertices, 4, topSideTrans, topSideRb);
	topSideCollider->AddComponent(topSidePolyCollide);
	topSideRb->SetStatic();
	_gameObjects.push_back(topSideCollider);
}

void Game::InitaliseGUI()
{
	GameObject* guiText = new GameObject("GUI");
	TransformComponent* guiTextTransform = ComponentFactory::MakeTransform(Vec2(100, -500), 0, 1);
	TextRendererComponent* guiTextRenderer = ComponentFactory::MakeTextRenderer("DirectXTK Simple Sample", guiTextTransform);
	guiText->AddComponent(guiTextTransform);
	guiText->AddComponent(guiTextRenderer);
	_gameObjects.push_back(guiText);
}

// Cache gameobjects with specific components so components aren't fetched every frame
void Game::CacheSpecificComponents()
{
	for (auto go : _gameObjects)
	{
		ColliderComponent* goCollider = go->GetComponent<ColliderComponent>();
		if (goCollider != nullptr)
		{
			_physicsManager.AddCollider(go, goCollider);
		}

		DamageableComponent* goDamagable = go->GetComponent<DamageableComponent>();
		if (goDamagable != nullptr)
		{
			_damageableGameObjects.insert(std::make_pair(go, goDamagable));
		}
	}
}

void Game::Update()
{
	_camera->BeginFrame();

	UpdateModel();
	ComposeFrame();

	_camera->EndFrame();

	Audio::Instance().Update();
}

Game::~Game()
{
	for (auto go : _gameObjects)
	{
		go->~GameObject();
	}
}

void Game::UpdateModel()
{
	float deltaTime = _frameTimer.Mark();

	// Update object rigid bodies
	_physicsManager.Update(deltaTime);

	// Check all objects that can be damaged to see if they are dead or not. Do something additional if the object that died is special or not
	for (auto dGo : _damageableGameObjects)
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
			}
		}
	}

	// Update gameobjects
	for (auto go : _gameObjects)
	{
		go->Update(deltaTime);
	}

	_gameLevel.Update(deltaTime);
}

void Game::ComposeFrame()
{
	for (auto go : _gameObjects)
	{
		go->Draw(_camera);
	}

	_gameLevel.Draw();
}
