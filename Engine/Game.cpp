#include "Game.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd)
{
	_camera = new GameCamera();
	_camera->Initalise(wnd);

	InitaliseObjects();
	InitaliseLevel();

	InitalisePhysics();
}

// Create any custom objects such as player
void Game::InitaliseObjects()
{
	TransformComponent* guiTextTransform = ComponentFactory::MakeTransform(Vec2(100, 20), 0, 1);
	TextRendererComponent* guiTextRenderer = ComponentFactory::MakeTextRenderer("DirectXTK Simple Sample", guiTextTransform);
	GameObject* guiText = new GameObject();
	guiText->AddComponent(guiTextTransform);
	guiText->AddComponent(guiTextRenderer);
	_gameObjects.push_back(guiText);

	_gameObjects.push_back(_camera);
}

// Read in level data from an XML file and build the level
void Game::InitaliseLevel()
{
	// Init LevelManager (xStep, yStep, xOrigin, yOrigin)
	GameLevelManager levelManager(TILE_WIDTH, TILE_HEIGHT, 0, 0);
	levelManager.LoadLevel("Levels\\level1.xml");

	Player* p = new Player(levelManager.GetLevelData().playerXPos, levelManager.GetLevelData().playerYPos);

	_camera->SetFocusTrans(p->GetComponent<TransformComponent>());
	// WHY IS IT -8 AND -10 ??????????
	_camera->SetLevelBounds((levelManager.GetLevelData().levelLeftBounds - 8) * TILE_WIDTH, 
		(levelManager.GetLevelData().levelRightBounds - 10) * TILE_HEIGHT, 
		(-levelManager.GetLevelData().levelBottomBounds - 7) * TILE_HEIGHT, 
		(-levelManager.GetLevelData().levelTopBounds) * TILE_HEIGHT);

	GameObject* skyBackground = new GameObject();
	TransformComponent* skyTrans = ComponentFactory::MakeTransform(Vec2(0, 0), 0, 1);
	skyBackground->AddComponent(skyTrans);
	skyBackground->AddComponent(ComponentFactory::MakeTiledBGRenderer("BG_Sky", 640, 480, 0.1f, 
		TiledBGDirection::eHoriztonalAndVertical, skyTrans,  p->GetComponent<TransformComponent>()));
	_gameObjects.push_back(skyBackground);

	GameObject* vegBackground = new GameObject();
	TransformComponent* vegTrans = ComponentFactory::MakeTransform(Vec2(0, -400), 0, 1);
	vegBackground->AddComponent(vegTrans);
	vegBackground->AddComponent(ComponentFactory::MakeTiledBGRenderer("BG_Vegetation", 640, 480, 0.5f, 
		TiledBGDirection::eHorizontal, vegTrans, p->GetComponent<TransformComponent>()));
	_gameObjects.push_back(vegBackground);

	GameObject* groundBackground = new GameObject();
	TransformComponent* groundTrans = ComponentFactory::MakeTransform(Vec2(0, -400), 0, 1);
	groundBackground->AddComponent(groundTrans);
	groundBackground->AddComponent(ComponentFactory::MakeTiledBGRenderer("BG_Ground", 640, 480, 3, 
		TiledBGDirection::eHorizontal, groundTrans, p->GetComponent<TransformComponent>()));
	_gameObjects.push_back(groundBackground);

	_gameObjects.push_back(p);

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

	GameObject* leftSideCollider = new GameObject();
	TransformComponent* leftSideTrans = ComponentFactory::MakeTransform(Vec2((levelManager.GetLevelData().levelLeftBounds - 1) * TILE_WIDTH, 0), 0, 1);
	leftSideCollider->AddComponent(leftSideTrans);
	RigidBodyComponent* leftSideRb = ComponentFactory::MakeRigidbody(true);
	leftSideCollider->AddComponent(leftSideRb);

	Vec2 *vertices = new Vec2[4];
	vertices[0].Set(1, 10000); // Bot right
	vertices[1].Set(-1, 10000); // Bot left
	vertices[2].Set(1, -10000); // Top right
	vertices[3].Set(-1, -10000); // Top left
	PolygonColliderComponent* leftSidePolyCollide = ComponentFactory::MakePolygonCollider(vertices, 4, leftSideTrans, leftSideRb);
	leftSideCollider->AddComponent(leftSidePolyCollide);
	_gameObjects.push_back(leftSideCollider);

	GameObject* rightSideCollider = new GameObject();
	TransformComponent* rightSideTrans = ComponentFactory::MakeTransform(Vec2((levelManager.GetLevelData().levelRightBounds - 1) * TILE_WIDTH, 0), 0, 1);
	rightSideCollider->AddComponent(rightSideTrans);
	RigidBodyComponent* rightSideRb = ComponentFactory::MakeRigidbody(true);
	rightSideCollider->AddComponent(rightSideRb);

	vertices = new Vec2[4];
	vertices[0].Set(1, 10000); // Bot right
	vertices[1].Set(-1, 10000); // Bot left
	vertices[2].Set(1, -10000); // Top right
	vertices[3].Set(-1, -10000); // Top left
	PolygonColliderComponent* rightSidePolyCollide = ComponentFactory::MakePolygonCollider(vertices, 4, rightSideTrans, rightSideRb);
	rightSideCollider->AddComponent(rightSidePolyCollide);
	_gameObjects.push_back(rightSideCollider);
}

// Add all gameobjects which have colliders to a physics manager which will then check for collisions every frame.
void Game::InitalisePhysics()
{
	for (auto go : _gameObjects)
	{
		ColliderComponent* goCollider = go->GetComponent<ColliderComponent>();

		if (goCollider != nullptr)
		{
			_physicsManager.AddCollider(goCollider);
		}
	}
}

void Game::Update()
{
	_camera->BeginFrame();

	UpdateModel();
	ComposeFrame();

	_camera->EndFrame();
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

	_physicsManager.Update(deltaTime);

	// Update gameobjects
	for (auto go : _gameObjects)
	{
		go->Update(deltaTime);
	}
}

void Game::ComposeFrame()
{
	for (auto go : _gameObjects)
	{
		go->Draw(_camera);
	}
}
