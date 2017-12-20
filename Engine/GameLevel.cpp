#include "GameLevel.h"



GameLevel::GameLevel()
{
	mObjectManager.Initalise("Levels\\GameValues.xml");
	mObjectManager.SetCamera(mCamera);
}


GameLevel::~GameLevel()
{
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

		mGameObjects.push_back(obj);

		gameObject = gameObject->next_sibling("GameObject");
	}
}

void GameLevel::Update(float deltaTime)
{
	// Update gameobjects
	for (auto go : mGameObjects)
	{
		go->Update(deltaTime);
	}
}

void GameLevel::Draw()
{
	// Update gameobjects
	for (auto go : mGameObjects)
	{
		go->Draw(mCamera);
	}
}