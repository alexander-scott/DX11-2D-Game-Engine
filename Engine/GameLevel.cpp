#include "GameLevel.h"


void GameLevel::Initalise(GameCamera* cam)
{
	mCamera = cam;
	mObjectManager.Initalise("Levels\\GameValues.xml");
	mObjectManager.SetCamera(cam);
}

void GameLevel::BuildLevel(std::string fileName)
{
	//Loads a level from xml file
	//Load the file
	std::ifstream inFile(fileName);

	if (!inFile)
		throw "Could not load tileset: " + fileName;

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
	mLevelData.levelLeftBounds = atoi(root->first_attribute("leftBound")->value());
	mLevelData.levelRightBounds = atoi(root->first_attribute("rightBound")->value());
	mLevelData.levelBottomBounds = -atoi(root->first_attribute("bottomBound")->value()); // Make negative
	mLevelData.levelTopBounds = -atoi(root->first_attribute("topBound")->value());

	xml_node<>* gameObject = root->first_node("GameObject");
	while (gameObject)
	{
		GameObject* obj = mObjectManager.CreateObject(atoi(gameObject->first_attribute("instanceid")->value()), atoi(gameObject->first_attribute("blueprintid")->value()));

		// Update its position from the original blueprint
		if (std::string(gameObject->first_attribute("update")->value()) == "tilepos")
		{
			float x = atof(gameObject->first_attribute("val1")->value());
			float y = atof(gameObject->first_attribute("val2")->value());

			Vec2 newPos = Vec2((float)X_ORIGIN + (x * TILE_WIDTH), (float)Y_ORIGIN + -(y * TILE_HEIGHT));

			obj->GetComponent<TransformComponent>()->SetPosition(newPos);
		}

		CacheComponents(obj, atoi(gameObject->first_attribute("renderLayer")->value()));

		gameObject = gameObject->next_sibling("GameObject");
	}

	mCamera->SetFocusTrans(mObjectManager.GetCreatedObject(0)->GetComponent<TransformComponent>()); // HARDCODEDDDDDD

	mCamera->SetLevelBounds((mLevelData.levelLeftBounds) * TILE_WIDTH,
		(mLevelData.levelRightBounds) * TILE_WIDTH,
		(mLevelData.levelBottomBounds) * TILE_HEIGHT,
		(mLevelData.levelTopBounds) * TILE_HEIGHT);

	CacheComponents(mCamera, -1);
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
}

void GameLevel::Update(float deltaTime)
{
	// Update object rigid bodies
	mPhysicsManager.Update(deltaTime);

	// Update gameobjects
	for (auto go : mGameObjects)
	{
		go->Update(deltaTime);
	}
}

void GameLevel::Draw()
{
	// Draw gameobjects
	for (auto go : mRenderLayer0)
	{
		go->Draw(mCamera);
	}

	for (auto go : mRenderLayer1)
	{
		go->Draw(mCamera);
	}

	for (auto go : mRenderLayer2)
	{
		go->Draw(mCamera);
	}
}