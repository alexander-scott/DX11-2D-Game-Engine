#include "SceneBuilder.h"

void SceneBuilder::InitaliseGameplayValues(string fileName)
{
	//Loads a level from xml file
	//Load the file
	ifstream inFile(fileName);

	if (!inFile)
		throw "Could not load tileset: " + fileName;

	//Dump contents of file into a string
	string xmlContents;

	//Blocked out of preference
	{
		string line;
		while (getline(inFile, line))
			xmlContents += line;
	}

	//Convert string to rapidxml readable char*
	vector<char> mXmlData = vector<char>(xmlContents.begin(), xmlContents.end());
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

void SceneBuilder::BuildScene(shared_ptr<IScene> scene, string fileName)
{
	//Load the file
	ifstream inFile(fileName);

	if (!inFile)
		throw "Could not load scene: " + fileName;

	//Dump contents of file into a string
	string xmlContents;

	//Blocked out of preference
	{
		string line;
		while (getline(inFile, line))
			xmlContents += line;
	}

	//Convert string to rapidxml readable char*
	vector<char> xmlData = vector<char>(xmlContents.begin(), xmlContents.end());
	xmlData.push_back('\0');

	//Create a parsed document with &xmlData[0] which is the char*
	xml_document<> doc;
	doc.parse<parse_no_data_nodes>(&xmlData[0]);

	//Get the root node
	xml_node<>* root = doc.first_node();

	ObjectManager objectManager = ObjectManager();
	LevelData levelData = ExtractLevelData(root);

	scene->SceneData = levelData;;

	xml_node<>* gameObjectNode = root->first_node("GameObject");

	// Loop through every gameobject in the level
	while (gameObjectNode)
	{
		// Create an instance of the gameobject listed in the level xml
		auto gameObject = objectManager.CreateObject(gameObjectNode);

		// Cache it's components so they can be used regularly without having to refetch them 
		scene->CacheComponents(gameObject);

		gameObjectNode = gameObjectNode->next_sibling("GameObject");
	}
}

LevelData SceneBuilder::ExtractLevelData(xml_node<>* node)
{
	LevelData levelData;
	levelData.levelLeftBounds = (float)atof(node->first_attribute("leftBound")->value());
	levelData.levelRightBounds = (float)atof(node->first_attribute("rightBound")->value());
	levelData.levelBottomBounds = abs((float)atof(node->first_attribute("bottomBound")->value())); // Make negative
	levelData.levelTopBounds = abs((float)atof(node->first_attribute("topBound")->value()));

	return levelData;
}