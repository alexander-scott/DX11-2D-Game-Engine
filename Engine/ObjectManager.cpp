#include "ObjectManager.h"

void ObjectManager::Initalise(std::string fileName)
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

	//Go through each tile
	mGameObjectBluePrints = root->first_node("GameObjects");
}

GameObject* ObjectManager::CreateObject(int id)
{
	while (mGameObjectBluePrints)
	{
		xml_node<>* gameObject = mGameObjectBluePrints->first_node("GameObject");
		while (gameObject)
		{
			int objID = atoi(gameObject->first_attribute("id")->value());
			if (id == objID)
			{
				// Create the gameobject
				GameObject* go = new GameObject(gameObject->first_attribute("tag")->value());

				// Push it to the map with it's ID
				mGameObjects.insert(std::make_pair(id, go));

				xml_node<>* component = gameObject->first_node("Component");
				while (component) // Create all this game objects components
				{
					go->AddComponent(CreateComponent(component));
					component = component->next_sibling("Component");
				}
				return go;
			}

			gameObject = gameObject->next_sibling("GameObject");
		}
	}

	throw std::exception("DID NOT FIND ID");
	return nullptr;
}

IComponent* ObjectManager::CreateComponent(xml_node<>* node)
{
	if (node->first_attribute("type")->value() == "TransformComponent")
	{
		float xPos = atof(node->first_attribute("xpos")->value());
		float yPos = atof(node->first_attribute("ypos")->value());
		float rot = atof(node->first_attribute("rotation")->value());
		float scale = atof(node->first_attribute("scale")->value());

		return ComponentFactory::MakeTransform(Vec2(xPos, yPos), rot, scale);
	}
	else if (node->first_attribute("type")->value() == "SpriteRendererComponent")
	{
		std::string fileName = node->first_attribute("filename")->value();
		TransformComponent* trans = mGameObjects[atoi(node->first_attribute("transformcomponentid")->value())]->GetComponent<TransformComponent>();
		float width = atof(node->first_attribute("width")->value());
		float height = atof(node->first_attribute("height")->value());
		float xOffset = atof(node->first_attribute("xoffset")->value());
		float yOffset = atof(node->first_attribute("yoffset")->value());

		return ComponentFactory::MakeSpriteRenderer(fileName, trans, width, height, Vec2(xOffset, yOffset));
	}
	else if (node->first_attribute("type")->value() == "SpriteAnimatorComponent")
	{
		std::string fileName = node->first_attribute("filename")->value();
		TransformComponent* trans = mGameObjects[atoi(node->first_attribute("transformcomponentid")->value())]->GetComponent<TransformComponent>();
		float width = atof(node->first_attribute("width")->value());
		float height = atof(node->first_attribute("height")->value());

		std::vector<AnimationDesc> animDescriptions;
		xml_node<>* animDescs = node->first_node("AnimDesc");
		while (animDescs)
		{
			int startingIndex = atoi(node->first_attribute("startingindex")->value());
			int endingIndex = atoi(node->first_attribute("endingindex")->value());
			int x = atoi(node->first_attribute("x")->value());
			int y = atoi(node->first_attribute("y")->value());
			int width = atoi(node->first_attribute("width")->value());
			int height = atoi(node->first_attribute("height")->value());
			int frameCount = atoi(node->first_attribute("framecount")->value());
			float holdTime = atof(node->first_attribute("holdtime")->value());

			animDescriptions.push_back(AnimationDesc(startingIndex, endingIndex, x, y, width, height, frameCount, holdTime));

			animDescs->next_sibling("AnimDesc");
		}

		int currentAnim = atoi(node->first_attribute("currentAnim")->value());

		return ComponentFactory::MakeSpriteAnimator(fileName, trans, width, height, animDescriptions, currentAnim);
	}
	else if (node->first_attribute("type")->value() == "RigidBodyComponent")
	{
		float staticF = atof(node->first_attribute("staticfriction")->value());
		float dynamicF = atof(node->first_attribute("dynamicfriction")->value());
		float restitution = atof(node->first_attribute("restitution")->value());

		return ComponentFactory::MakeRigidbody(staticF, dynamicF, restitution);
	}
	else if (node->first_attribute("type")->value() == "TextRendererComponent")
	{
		std::string text = node->first_attribute("text")->value();
		TransformComponent* trans = mGameObjects[atoi(node->first_attribute("transformcomponentid")->value())]->GetComponent<TransformComponent>();

		return ComponentFactory::MakeTextRenderer(text, trans);
	}
	else if (node->first_attribute("type")->value() == "CircleColliderComponent")
	{
		float radius = atof(node->first_attribute("radius")->value());
		TransformComponent* trans = mGameObjects[atoi(node->first_attribute("transformcomponentid")->value())]->GetComponent<TransformComponent>();
		RigidBodyComponent* rb = mGameObjects[atoi(node->first_attribute("rigidbodycomponentid")->value())]->GetComponent<RigidBodyComponent>();
		
		return ComponentFactory::MakeCircleCollider(radius, trans, rb);
	}
	else if (node->first_attribute("type")->value() == "PolygonColliderComponent")
	{
		throw;
	}
	else if (node->first_attribute("type")->value() == "BoxColliderComponent")
	{
		float width = atof(node->first_attribute("width")->value());
		float height = atof(node->first_attribute("height")->value());
		TransformComponent* trans = mGameObjects[atoi(node->first_attribute("transformcomponentid")->value())]->GetComponent<TransformComponent>();
		RigidBodyComponent* rb = mGameObjects[atoi(node->first_attribute("rigidbodycomponentid")->value())]->GetComponent<RigidBodyComponent>();

		return ComponentFactory::MakeBoxCollider(width, height, trans, rb);
	}
	else if (node->first_attribute("type")->value() == "ColliderRendererComponent")
	{
		throw;
	}
	else if (node->first_attribute("type")->value() == "TiledBGRenderer")
	{
		std::string spriteName = node->first_attribute("spritename")->value();
		float width = atof(node->first_attribute("spritewidth")->value());
		float height = atof(node->first_attribute("spriteheight")->value());
		float moveRate = atof(node->first_attribute("moverate")->value());
		TiledBGDirection dir;
		if (node->first_attribute("direction")->value() == "horizontal")
			dir = TiledBGDirection::eHorizontal;
		else if (node->first_attribute("direction")->value() == "vertical")
			dir = TiledBGDirection::eVertical;
		else
			dir = TiledBGDirection::eHoriztonalAndVertical;
		TransformComponent* trans = mGameObjects[atoi(node->first_attribute("transformcomponentid")->value())]->GetComponent<TransformComponent>();
		TransformComponent* focusTrans = mGameObjects[atoi(node->first_attribute("focustransformcomponentid")->value())]->GetComponent<TransformComponent>();

		return ComponentFactory::MakeTiledBGRenderer(spriteName, width, height, moveRate, dir, trans, focusTrans);
	}
	else if (node->first_attribute("type")->value() == "PlayerComponent")
	{
		TransformComponent* trans = mGameObjects[atoi(node->first_attribute("transformcomponentid")->value())]->GetComponent<TransformComponent>();
		SpriteAnimatorComponent* anim = mGameObjects[atoi(node->first_attribute("animatorcomponentid")->value())]->GetComponent<SpriteAnimatorComponent>();
		RigidBodyComponent* rb = mGameObjects[atoi(node->first_attribute("rigidbodycomponentid")->value())]->GetComponent<RigidBodyComponent>();
		DamageableComponent* dmg = mGameObjects[atoi(node->first_attribute("damageablecomponentid")->value())]->GetComponent<DamageableComponent>();

		ProjectileManager* projectiles = new ProjectileManager;
		int projectileCount = atoi(node->first_attribute("projectilecount")->value());
		std::string projectHitTag = node->first_attribute("projecthittag")->value();
		for (int i = 0; i < projectileCount; i++)
		{
			GameObject* ball = new GameObject("Ball");
			TransformComponent* ballTrans = ComponentFactory::MakeTransform(Vec2(0, 0), 0, 0.2f);
			ball->AddComponent(ballTrans);
			RigidBodyComponent* ballRb = ComponentFactory::MakeRigidbody(1, 0.3f, 0.5f); // Cache the rigidbody
			ball->AddComponent(ballRb);
			CircleColliderComponent* ballCollider = ComponentFactory::MakeCircleCollider(64, ballTrans, ballRb);
			ball->AddComponent(ballCollider);
			SpriteRendererComponent* ballRenderer = ComponentFactory::MakeSpriteRenderer("Ball", ballTrans, 128, 128, Vec2(0, 0));
			ball->AddComponent(ballRenderer);
			ProjectileComponent* ballProjectile = ComponentFactory::MakeProjectileComponent(projectHitTag, 10, 10);
			ball->AddComponent(ballProjectile);

			projectiles->AddCreatedGameObject(ball);
		}

		return ComponentFactory::MakePlayerComponent(trans, anim, rb, dmg, projectiles, mCamera->GetComponent<TransformComponent>());
	}
	else if (node->first_attribute("type")->value() == "DamageableComponent")
	{
		float startHealth = atoi(node->first_attribute("damageablecomponentid")->value());

		return ComponentFactory::MakeDamageableComponent(startHealth);
	}
	else if (node->first_attribute("type")->value() == "ProjectileComponent")
	{
		std::string affectedTag = node->first_attribute("affectedTag")->value();
		float lifeSpan = atoi(node->first_attribute("lifespan")->value());
		float damage = atoi(node->first_attribute("damage")->value());

		return ComponentFactory::MakeProjectileComponent(affectedTag, lifeSpan, damage);
	}
	else if (node->first_attribute("type")->value() == "AIAgentComponent")
	{
		TransformComponent* trans = mGameObjects[atoi(node->first_attribute("transformcomponentid")->value())]->GetComponent<TransformComponent>();
		SpriteAnimatorComponent* anim = mGameObjects[atoi(node->first_attribute("animatorcomponentid")->value())]->GetComponent<SpriteAnimatorComponent>();
		RigidBodyComponent* rb = mGameObjects[atoi(node->first_attribute("rigidbodycomponentid")->value())]->GetComponent<RigidBodyComponent>();
		DamageableComponent* dmg = mGameObjects[atoi(node->first_attribute("damageablecomponentid")->value())]->GetComponent<DamageableComponent>();

		ProjectileManager* projectiles = new ProjectileManager;
		int projectileCount = atoi(node->first_attribute("projectilecount")->value());
		std::string projectHitTag = node->first_attribute("projecthittag")->value();
		for (int i = 0; i < projectileCount; i++)
		{
			GameObject* ball = new GameObject("Ball");
			TransformComponent* ballTrans = ComponentFactory::MakeTransform(Vec2(0, 0), 0, 0.2f);
			ball->AddComponent(ballTrans);
			RigidBodyComponent* ballRb = ComponentFactory::MakeRigidbody(1, 0.3f, 0.5f); // Cache the rigidbody
			ball->AddComponent(ballRb);
			CircleColliderComponent* ballCollider = ComponentFactory::MakeCircleCollider(64, ballTrans, ballRb);
			ball->AddComponent(ballCollider);
			SpriteRendererComponent* ballRenderer = ComponentFactory::MakeSpriteRenderer("Ball", ballTrans, 128, 128, Vec2(0, 0));
			ball->AddComponent(ballRenderer);
			ProjectileComponent* ballProjectile = ComponentFactory::MakeProjectileComponent(projectHitTag, 10, 10);
			ball->AddComponent(ballProjectile);

			projectiles->AddCreatedGameObject(ball);
		}

		float patrolTime = atof(node->first_attribute("patrolTime")->value());

		AIAgentPatrolDirection dir;
		if (node->first_attribute("startdirection")->value() == "left")
			dir = AIAgentPatrolDirection::ePatrollingLeft;
		else if (node->first_attribute("startdirection")->value() == "right")
			dir = AIAgentPatrolDirection::ePatrollingRight;

		float idleTime = atof(node->first_attribute("idletime")->value());

		return ComponentFactory::MakeAIAgentComponent(trans, anim, rb, dmg, projectiles, mCamera->GetComponent<TransformComponent>(), patrolTime, dir, idleTime);
	}

	throw;
	return nullptr;
}
