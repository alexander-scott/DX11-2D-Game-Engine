#include "LevelBuilder.h"

void LevelBuilder::InitaliseGameplayValues(std::string fileName)
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
	std::vector<char> mXmlData = std::vector<char>(xmlContents.begin(), xmlContents.end());
	mXmlData.push_back('\0');

	//Create a parsed document with &xmlData[0] which is the char*
	xml_document<> doc;
	doc.parse<parse_no_data_nodes>(&mXmlData[0]);

	//Get the root node
	xml_node<>* root = doc.first_node();
	xml_node<>*	valuesNode = root->first_node("values");

	PLAYER_PROJECTILE_DAMAGE = (float)atof(valuesNode->first_node("PlayerProjectileDamage")->first_attribute("val")->value());
	PLAYER_PROJECTILE_SPEED = (float)atof(valuesNode->first_node("PlayerProjectileSpeed")->first_attribute("val")->value());
	PLAYER_LATERAL_MAX_SPEED = (float)atof(valuesNode->first_node("PlayerLateralMaxSpeed")->first_attribute("val")->value());
	AI_PROJECTILE_DAMAGE = (float)atof(valuesNode->first_node("AIProjectileDamage")->first_attribute("val")->value());
	AI_PROJECTILE_SPEED = (float)atof(valuesNode->first_node("AIProjectileSpeed")->first_attribute("val")->value());
	AI_LATERAL_MAX_SPEED = (float)atof(valuesNode->first_node("AILateralMaxSpeed")->first_attribute("val")->value());
}

GameLevel * LevelBuilder::BuildGameLevel(std::string fileName)
{
	//Load the file
	std::ifstream inFile(fileName);

	if (!inFile)
		throw "Could not load level: " + fileName;

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

	GameLevel* gameLevel = new GameLevel();
	ObjectManager objectManager;
	LevelData levelData = ExtractLevelData(root);

	gameLevel->SetLevelData(levelData);

	xml_node<>* gameObjectNode = root->first_node("GameObject");

	// Loop through every gameobject in the level
	while (gameObjectNode)
	{
		// Create an instance of the gameobject listed in the level xml
		GameObject* obj = objectManager.CreateObject(atoi(gameObjectNode->first_attribute("instanceid")->value()),
			atoi(gameObjectNode->first_attribute("blueprintid")->value()));

		// Update its position from the original blueprint
		if (std::string(gameObjectNode->first_attribute("update")->value()) == "tilepos")
		{
			UpdateTilePos(gameObjectNode, obj);
		}

		// Cache it's components so they can be used regularly without having to refetch them 
		gameLevel->CacheComponents(obj, atoi(gameObjectNode->first_attribute("renderLayer")->value()));

		gameObjectNode = gameObjectNode->next_sibling("GameObject");
	}

	GameCamera::Instance().SetFocusTrans(objectManager.GetCreatedObject(0)->GetComponent<TransformComponent>()); // HARDCODEDDDDDD

	GameCamera::Instance().SetLevelBounds(
		(levelData.levelLeftBounds) * TILE_WIDTH,
		(levelData.levelRightBounds) * TILE_WIDTH,
		(levelData.levelBottomBounds) * TILE_HEIGHT,
		(levelData.levelTopBounds) * TILE_HEIGHT);

	gameLevel->CacheComponents(&GameCamera::Instance(), -1);

	return gameLevel;
}

LevelData LevelBuilder::ExtractLevelData(xml_node<>* node)
{
	LevelData levelData;
	levelData.levelLeftBounds = (float)atof(node->first_attribute("leftBound")->value());
	levelData.levelRightBounds = (float)atof(node->first_attribute("rightBound")->value());
	levelData.levelBottomBounds = -(float)atof(node->first_attribute("bottomBound")->value()); // Make negative
	levelData.levelTopBounds = -(float)atof(node->first_attribute("topBound")->value());

	return levelData;
}

void LevelBuilder::UpdateTilePos(xml_node<>* node, GameObject * obj)
{
	float x = (float)atof(node->first_attribute("val1")->value());
	float y = (float)atof(node->first_attribute("val2")->value());

	Vec2 newPos = Vec2((float)X_ORIGIN + (x * TILE_WIDTH), (float)Y_ORIGIN + -(y * TILE_HEIGHT));

	obj->GetComponent<TransformComponent>()->SetPosition(newPos);
}
