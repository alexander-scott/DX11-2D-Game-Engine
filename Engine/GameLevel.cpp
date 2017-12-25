#include "GameLevel.h"

GameLevel::GameLevel(std::string fileName) : mfileName(fileName)
{

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

void GameLevel::BuildLevel()
{
	//Load the file
	std::ifstream inFile(mfileName);

	if (!inFile)
		throw "Could not load level: " + mfileName;

	//Dump contents of file into a string
	std::string xmlContents;

	//Blocked out of preference
	{
		std::string line;
		while (std::getline(inFile, line))
			xmlContents += line;
	}

	//Convert string to rapidxml readable char*
	std::vector<char> xmlData = std::vector<char>(xmlContents.begin(), xmlContents.end());
	xmlData.push_back('\0');

	//Create a parsed document with &xmlData[0] which is the char*
	xml_document<> doc;
	doc.parse<parse_no_data_nodes>(&xmlData[0]);

	//Get the root node
	xml_node<>* root = doc.first_node();

	ExtractLevelData(root);

	xml_node<>* gameObjectNode = root->first_node("GameObject");

	// Loop through every gameobject in the level
	while (gameObjectNode)
	{
		// Create an instance of the gameobject listed in the level xml
		GameObject* obj = mObjectManager.CreateObject(atoi(gameObjectNode->first_attribute("instanceid")->value()), 
			atoi(gameObjectNode->first_attribute("blueprintid")->value()));

		// Update its position from the original blueprint
		if (std::string(gameObjectNode->first_attribute("update")->value()) == "tilepos")
		{
			UpdateTilePos(gameObjectNode, obj);
		}

		// Cache it's components so they can be used regularly without having to refetch them 
		CacheComponents(obj, atoi(gameObjectNode->first_attribute("renderLayer")->value()));

		gameObjectNode = gameObjectNode->next_sibling("GameObject");
	}

	SetupCamera();
}

void GameLevel::ExtractLevelData(xml_node<>* node)
{
	mLevelData.levelLeftBounds = (float)atof(node->first_attribute("leftBound")->value());
	mLevelData.levelRightBounds = (float)atof(node->first_attribute("rightBound")->value());
	mLevelData.levelBottomBounds = -(float)atof(node->first_attribute("bottomBound")->value()); // Make negative
	mLevelData.levelTopBounds = -(float)atof(node->first_attribute("topBound")->value());
}

void GameLevel::UpdateTilePos(xml_node<>* node, GameObject* obj)
{
	float x = (float)atof(node->first_attribute("val1")->value());
	float y = (float)atof(node->first_attribute("val2")->value());

	Vec2 newPos = Vec2((float)X_ORIGIN + (x * TILE_WIDTH), (float)Y_ORIGIN + -(y * TILE_HEIGHT));

	obj->GetComponent<TransformComponent>()->SetPosition(newPos);
}

void GameLevel::SetupCamera()
{
	GameCamera::Instance().SetFocusTrans(mObjectManager.GetCreatedObject(0)->GetComponent<TransformComponent>()); // HARDCODEDDDDDD

	GameCamera::Instance().SetLevelBounds((mLevelData.levelLeftBounds) * TILE_WIDTH,
		(mLevelData.levelRightBounds) * TILE_WIDTH,
		(mLevelData.levelBottomBounds) * TILE_HEIGHT,
		(mLevelData.levelTopBounds) * TILE_HEIGHT);

	CacheComponents(&GameCamera::Instance(), -1);
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

void GameLevel::Update(float deltaTime)
{
	// Update object rigid bodies
	mPhysicsManager.Update(deltaTime);

	// Check all objects that can be damaged to see if they are dead or not. Do something additional if the object that died is special or not
	for (auto dGo : mDamageableGameObjects)
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
	for (auto go : mGameObjects)
	{
		go->Update(deltaTime);
	}
}

void GameLevel::Draw()
{
	// Draw gameobjects in the render order
	for (auto go : mRenderLayer0)
	{
		go->Draw(&GameCamera::Instance());
	}

	for (auto go : mRenderLayer1)
	{
		go->Draw(&GameCamera::Instance());
	}

	for (auto go : mRenderLayer2)
	{
		go->Draw(&GameCamera::Instance());
	}
}