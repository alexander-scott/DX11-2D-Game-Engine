#include "Game.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd)
{
	_camera = new GameCamera();
	_camera->Initalise(wnd);
	_gameObjects.push_back(_camera);

	
	InitaliseLevel();

	InitalisePhysics();
}

// Create any custom objects
void Game::InitaliseObjects(LevelData& levelData)
{
	Ball* b = new Ball(levelData.playerXPos + 200, levelData.playerYPos - 200);
	_gameObjects.push_back(b);

	Ball* b2 = new Ball(levelData.playerXPos + 230, levelData.playerYPos - 400);
	_gameObjects.push_back(b2);

	Ball* b3 = new Ball(levelData.playerXPos + 170, levelData.playerYPos - 600);
	_gameObjects.push_back(b3);
}

// Read in level data from an XML file and build the level
void Game::InitaliseLevel()
{
	// Init LevelManager (xStep, yStep, xOrigin, yOrigin)
	GameLevelManager levelManager(TILE_WIDTH, TILE_HEIGHT, 0, 0);
	levelManager.LoadLevel("Levels\\level1.xml");

	// Build any objects that are dependecies to other objects (global vars). Such as player.
	_player = new Player(levelManager.GetLevelData().playerXPos, levelManager.GetLevelData().playerYPos);

	// Build the background and add that first as that needs to get renderered at the very back
	InitaliseBackground(levelManager.GetLevelData());

	// Build objects that will exist in the level and render that on top of the background layers
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

void Game::InitaliseBackground(LevelData& levelData)
{
	_camera->SetFocusTrans(_player->GetComponent<TransformComponent>());

	// WHY ARE WE SUBTRACTING THESE HARD VALUES?!?!?!!?
	_camera->SetLevelBounds((levelData.levelLeftBounds - 9) * TILE_WIDTH,
		(levelData.levelRightBounds - 10) * TILE_HEIGHT,
		(levelData.levelBottomBounds - 7) * TILE_HEIGHT,
		(levelData.levelTopBounds) * TILE_HEIGHT);

	GameObject* skyBackground = new GameObject();
	TransformComponent* skyTrans = ComponentFactory::MakeTransform(Vec2(0, 0), 0, 1);
	skyBackground->AddComponent(skyTrans);
	skyBackground->AddComponent(ComponentFactory::MakeTiledBGRenderer("BG_Sky", 640, 480, 0.1f,
		TiledBGDirection::eHoriztonalAndVertical, skyTrans, _player->GetComponent<TransformComponent>()));
	_gameObjects.push_back(skyBackground);

	GameObject* vegBackground = new GameObject();
	TransformComponent* vegTrans = ComponentFactory::MakeTransform(Vec2(0, -400), 0, 1);
	vegBackground->AddComponent(vegTrans);
	vegBackground->AddComponent(ComponentFactory::MakeTiledBGRenderer("BG_Vegetation", 640, 480, 0.5f,
		TiledBGDirection::eHorizontal, vegTrans, _player->GetComponent<TransformComponent>()));
	_gameObjects.push_back(vegBackground);

	GameObject* groundBackground = new GameObject();
	TransformComponent* groundTrans = ComponentFactory::MakeTransform(Vec2(0, -400), 0, 1);
	groundBackground->AddComponent(groundTrans);
	groundBackground->AddComponent(ComponentFactory::MakeTiledBGRenderer("BG_Ground", 640, 480, 3,
		TiledBGDirection::eHorizontal, groundTrans, _player->GetComponent<TransformComponent>()));
	_gameObjects.push_back(groundBackground);

	GameObject* leftSideCollider = new GameObject();
	TransformComponent* leftSideTrans = ComponentFactory::MakeTransform(Vec2((levelData.levelLeftBounds - 1) * TILE_WIDTH, 0), 0, 1);
	leftSideCollider->AddComponent(leftSideTrans);
	RigidBodyComponent* leftSideRb = ComponentFactory::MakeRigidbody(1, 1, 1);
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

	GameObject* rightSideCollider = new GameObject();
	TransformComponent* rightSideTrans = ComponentFactory::MakeTransform(Vec2((levelData.levelRightBounds - 1) * TILE_WIDTH, 0), 0, 1);
	rightSideCollider->AddComponent(rightSideTrans);
	RigidBodyComponent* rightSideRb = ComponentFactory::MakeRigidbody(1, 1, 1);
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

	GameObject* bottomSideCollider = new GameObject();
	TransformComponent* bottomSideTrans = ComponentFactory::MakeTransform(Vec2(0, (levelData.levelBottomBounds) * TILE_HEIGHT), 0, 1);
	bottomSideCollider->AddComponent(bottomSideTrans);
	RigidBodyComponent* bottomSideRb = ComponentFactory::MakeRigidbody(1, 1, 1);
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

	GameObject* topSideCollider = new GameObject();
	TransformComponent* topSideTrans = ComponentFactory::MakeTransform(Vec2(0, (levelData.levelTopBounds + 6) * TILE_HEIGHT), 0, 1);
	topSideCollider->AddComponent(topSideTrans);
	RigidBodyComponent* topSideRb = ComponentFactory::MakeRigidbody(1, 1, 1);
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
	GameObject* guiText = new GameObject();
	TransformComponent* guiTextTransform = ComponentFactory::MakeTransform(Vec2(100, -500), 0, 1);
	TextRendererComponent* guiTextRenderer = ComponentFactory::MakeTextRenderer("DirectXTK Simple Sample", guiTextTransform);
	guiText->AddComponent(guiTextTransform);
	guiText->AddComponent(guiTextRenderer);
	_gameObjects.push_back(guiText);
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
