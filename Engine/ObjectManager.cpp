#include "ObjectManager.h"

GameObject* ObjectManager::GetCreatedObject(int instanceID)
{
	return mGameObjects[instanceID];
}

GameObject* ObjectManager::CreateObject(int instanceID, int prefabID)
{
	//Loads a level from xml file
	//Load the file
	std::ifstream inFile(mfileName);

	if (!inFile)
		throw "Could not load tileset: " + mfileName;

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

	//Go through each tile
	xml_node<>*	gameObjectList = root->first_node("GameObjects");
	while (gameObjectList)
	{
		xml_node<>* gameObject = gameObjectList->first_node("GameObject");
		while (gameObject)
		{
			int objprefabID = atoi(gameObject->first_attribute("prefabid")->value());
			if (prefabID == objprefabID)
			{
				// Create the gameobject
				GameObject* go = new GameObject(gameObject->first_attribute("tag")->value());

				if (instanceID != -1)
				{
					// Push it to the map with it's ID
					mGameObjects.insert(std::make_pair(instanceID, go));
				}
				else
				{
					int rand = std::rand();
					auto it = mGameObjects.find(rand);
					while (it != mGameObjects.end()) // Make sure it doesn't already exist in the map
					{
						rand = std::rand();
						it = mGameObjects.find(rand);
					}
					mGameObjects.insert(std::make_pair(rand, go));
				}

				xml_node<>* component = gameObject->first_node("Component");
				while (component) // Create all this gameobject's components
				{
					IComponent* newComponent = CreateComponent(go, component);

					if (component->first_attribute("componentinactive") != nullptr)
						newComponent->SetActive(false);

					go->AddComponent(newComponent);
					component = component->next_sibling("Component");
				}

				return go;
			}

			gameObject = gameObject->next_sibling("GameObject");
		}
	}

	throw std::exception("DID NOT FIND prefab ID");

	return nullptr;
}

IComponent* ObjectManager::CreateComponent(GameObject* go, xml_node<>* node)
{
	if (std::string(node->first_attribute("type")->value()) == "TransformComponent")
	{
		float xPos = (float)atof(node->first_attribute("xpos")->value());
		float yPos = (float)atof(node->first_attribute("ypos")->value());
		float rot = (float)atof(node->first_attribute("rotation")->value());
		float scale = (float)atof(node->first_attribute("scale")->value());

		return ComponentFactory::MakeTransform(Vec2(xPos, yPos), rot, scale);
	}
	else if (std::string(node->first_attribute("type")->value()) == "SpriteRendererComponent")
	{
		std::string fileName = std::string(node->first_attribute("filename")->value());

		TransformComponent* trans;
		int transformComponentID = atoi(node->first_attribute("transformcomponentid")->value());
		if (transformComponentID == -1)
			trans = go->GetComponent<TransformComponent>();
		else
			trans = mGameObjects[atoi(node->first_attribute("transformcomponentid")->value())]->GetComponent<TransformComponent>();

		float width = (float)atof(node->first_attribute("width")->value());
		float height = (float)atof(node->first_attribute("height")->value());
		float xOffset = (float)atof(node->first_attribute("xoffset")->value());
		float yOffset = (float)atof(node->first_attribute("yoffset")->value());

		return ComponentFactory::MakeSpriteRenderer(fileName, trans, width, height, Vec2(xOffset, yOffset));
	}
	else if (std::string(node->first_attribute("type")->value()) == "SpriteAnimatorComponent")
	{
		std::string fileName = std::string(node->first_attribute("filename")->value());

		TransformComponent* trans;
		int transformComponentID = atoi(node->first_attribute("transformcomponentid")->value());
		if (transformComponentID == -1)
			trans = go->GetComponent<TransformComponent>();
		else
			trans = mGameObjects[atoi(node->first_attribute("transformcomponentid")->value())]->GetComponent<TransformComponent>();

		float width = (float)atof(node->first_attribute("width")->value());
		float height = (float)atof(node->first_attribute("height")->value());

		std::vector<AnimationDesc> animDescriptions;
		xml_node<>* animDescs = node->first_node("AnimDesc");
		while (animDescs)
		{
			int startingIndex = atoi(animDescs->first_attribute("startingindex")->value());
			int endingIndex = atoi(animDescs->first_attribute("endingindex")->value());
			int x = atoi(animDescs->first_attribute("x")->value());
			int y = atoi(animDescs->first_attribute("y")->value());
			int width = atoi(animDescs->first_attribute("width")->value());
			int height = atoi(animDescs->first_attribute("height")->value());
			int frameCount = atoi(animDescs->first_attribute("framecount")->value());
			float holdTime = (float)atof(animDescs->first_attribute("holdtime")->value());

			animDescriptions.push_back(AnimationDesc(startingIndex, endingIndex, x, y, width, height, frameCount, holdTime));

			animDescs = animDescs->next_sibling("AnimDesc");
		}

		int currentAnim = atoi(node->first_attribute("currentAnim")->value());

		return ComponentFactory::MakeSpriteAnimator(fileName, trans, width, height, animDescriptions, currentAnim);
	}
	else if (std::string(node->first_attribute("type")->value()) == "RigidBodyComponent")
	{
		float staticF = (float)atof(node->first_attribute("staticfriction")->value());
		float dynamicF = (float)atof(node->first_attribute("dynamicfriction")->value());
		float restitution = (float)atof(node->first_attribute("restitution")->value());

		bool isStatic = false;
		if (std::string(node->first_attribute("static")->value()) == "true")
			isStatic = true;

		bool lockRotation = false;
		if (std::string(node->first_attribute("lockrotation")->value()) == "true")
			lockRotation = true;

		return ComponentFactory::MakeRigidbody(staticF, dynamicF, restitution, isStatic, lockRotation);
	}
	else if (std::string(node->first_attribute("type")->value()) == "TextRendererComponent")
	{
		std::string text = std::string(node->first_attribute("text")->value());

		TransformComponent* trans;
		int transformComponentID = atoi(node->first_attribute("transformcomponentid")->value());
		if (transformComponentID == -1)
			trans = go->GetComponent<TransformComponent>();
		else
			trans = mGameObjects[atoi(node->first_attribute("transformcomponentid")->value())]->GetComponent<TransformComponent>();

		return ComponentFactory::MakeTextRenderer(text, DirectX::Colors::Yellow, trans); // TODO: Remove default yellow colour
	}
	else if (std::string(node->first_attribute("type")->value()) == "CircleColliderComponent")
	{
		float radius = (float)atof(node->first_attribute("radius")->value());

		TransformComponent* trans;
		int transformComponentID = atoi(node->first_attribute("transformcomponentid")->value());
		if (transformComponentID == -1)
			trans = go->GetComponent<TransformComponent>();
		else
			trans = mGameObjects[atoi(node->first_attribute("transformcomponentid")->value())]->GetComponent<TransformComponent>();

		RigidBodyComponent* rb;
		int rigidBodyComponentID = atoi(node->first_attribute("rigidbodycomponentid")->value());
		if (rigidBodyComponentID == -1)
			rb = go->GetComponent<RigidBodyComponent>();
		else
			rb = mGameObjects[atoi(node->first_attribute("rigidbodycomponentid")->value())]->GetComponent<RigidBodyComponent>();
		
		return ComponentFactory::MakeCircleCollider(radius, trans, rb);
	}
	else if (std::string(node->first_attribute("type")->value()) == "PolygonColliderComponent")
	{
		throw std::exception("WRONG");
	}
	else if (std::string(node->first_attribute("type")->value()) == "BoxColliderComponent")
	{
		float width = (float)atof(node->first_attribute("width")->value());
		float height = (float)atof(node->first_attribute("height")->value());

		TransformComponent* trans;
		int transformComponentID = atoi(node->first_attribute("transformcomponentid")->value());
		if (transformComponentID == -1)
			trans = go->GetComponent<TransformComponent>();
		else
			trans = mGameObjects[atoi(node->first_attribute("transformcomponentid")->value())]->GetComponent<TransformComponent>();

		RigidBodyComponent* rb;
		int rigidBodyComponentID = atoi(node->first_attribute("rigidbodycomponentid")->value());
		if (rigidBodyComponentID == -1)
			rb = go->GetComponent<RigidBodyComponent>();
		else
			rb = mGameObjects[atoi(node->first_attribute("rigidbodycomponentid")->value())]->GetComponent<RigidBodyComponent>();

		return ComponentFactory::MakeBoxCollider(width, height, trans, rb);
	}
	else if (std::string(node->first_attribute("type")->value()) == "ColliderRendererComponent")
	{
		throw;
	}
	else if (std::string(node->first_attribute("type")->value()) == "TiledBGRenderer")
	{
		std::string spriteName = std::string(node->first_attribute("spritename")->value());
		float width = (float)atof(node->first_attribute("spritewidth")->value());
		float height = (float)atof(node->first_attribute("spriteheight")->value());
		float moveRate = (float)atof(node->first_attribute("moverate")->value());

		TiledBGDirection dir;
		if (std::string(node->first_attribute("direction")->value()) == "horizontal")
			dir = TiledBGDirection::eHorizontal;
		else if (std::string(node->first_attribute("direction")->value()) == "vertical")
			dir = TiledBGDirection::eVertical;
		else
			dir = TiledBGDirection::eHoriztonalAndVertical;

		TransformComponent* trans;
		int transformComponentID = atoi(node->first_attribute("transformcomponentid")->value());
		if (transformComponentID == -1)
			trans = go->GetComponent<TransformComponent>();
		else
			trans = mGameObjects[atoi(node->first_attribute("transformcomponentid")->value())]->GetComponent<TransformComponent>();

		TransformComponent* focusTrans = mGameObjects[atoi(node->first_attribute("focustransformcomponentid")->value())]->GetComponent<TransformComponent>();

		return ComponentFactory::MakeTiledBGRenderer(spriteName, width, height, moveRate, dir, trans, focusTrans);
	}
	else if (std::string(node->first_attribute("type")->value()) == "PlayerComponent")
	{
		TransformComponent* trans;
		int transformComponentID = atoi(node->first_attribute("transformcomponentid")->value());
		if (transformComponentID == -1)
			trans = go->GetComponent<TransformComponent>();
		else
			trans = mGameObjects[atoi(node->first_attribute("transformcomponentid")->value())]->GetComponent<TransformComponent>();

		SpriteAnimatorComponent* anim;
		int animComponentID = atoi(node->first_attribute("animatorcomponentid")->value());
		if (animComponentID == -1)
			anim = go->GetComponent<SpriteAnimatorComponent>();
		else
			anim = mGameObjects[atoi(node->first_attribute("animatorcomponentid")->value())]->GetComponent<SpriteAnimatorComponent>();

		RigidBodyComponent* rb;
		int rigidBodyComponentID = atoi(node->first_attribute("rigidbodycomponentid")->value());
		if (rigidBodyComponentID == -1)
			rb = go->GetComponent<RigidBodyComponent>();
		else
			rb = mGameObjects[atoi(node->first_attribute("rigidbodycomponentid")->value())]->GetComponent<RigidBodyComponent>();

		DamageableComponent* dmg;
		int dmgComponentID = atoi(node->first_attribute("damageablecomponentid")->value());
		if (dmgComponentID == -1)
			dmg = go->GetComponent<DamageableComponent>();
		else
			dmg = mGameObjects[atoi(node->first_attribute("damageablecomponentid")->value())]->GetComponent<DamageableComponent>();

		ProjectileManagerComponent* projectileManager;
		int projmanagerID = atoi(node->first_attribute("projectilemangercomponentid")->value());
		if (projmanagerID == -1)
			projectileManager = go->GetComponent<ProjectileManagerComponent>();
		else
			projectileManager = mGameObjects[atoi(node->first_attribute("projectilemangercomponentid")->value())]->GetComponent<ProjectileManagerComponent>();

		return ComponentFactory::MakePlayerComponent(trans, anim, rb, dmg, projectileManager, GameCamera::Instance().GetComponent<TransformComponent>());
	}
	else if (std::string(node->first_attribute("type")->value()) == "DamageableComponent")
	{
		float startHealth = (float)atof(node->first_attribute("starthealth")->value());
		std::string hitNoise = std::string(node->first_attribute("hitnoise")->value());

		return ComponentFactory::MakeDamageableComponent(startHealth, hitNoise);
	}
	else if (std::string(node->first_attribute("type")->value()) == "ProjectileComponent")
	{
		std::string affectedTag = std::string(node->first_attribute("affectedTag")->value());
		float lifeSpan = (float)atof(node->first_attribute("lifespan")->value());
		float damage = (float)atof(node->first_attribute("damage")->value());

		return ComponentFactory::MakeProjectileComponent(affectedTag, lifeSpan, damage);
	}
	else if (std::string(node->first_attribute("type")->value()) == "AIAgentComponent")
	{
		TransformComponent* trans;
		int transformComponentID = atoi(node->first_attribute("transformcomponentid")->value());
		if (transformComponentID == -1)
			trans = go->GetComponent<TransformComponent>();
		else
			trans = mGameObjects[atoi(node->first_attribute("transformcomponentid")->value())]->GetComponent<TransformComponent>();

		SpriteAnimatorComponent* anim;
		int animComponentID = atoi(node->first_attribute("animatorcomponentid")->value());
		if (animComponentID == -1)
			anim = go->GetComponent<SpriteAnimatorComponent>();
		else
			anim = mGameObjects[atoi(node->first_attribute("animatorcomponentid")->value())]->GetComponent<SpriteAnimatorComponent>();

		RigidBodyComponent* rb;
		int rigidBodyComponentID = atoi(node->first_attribute("rigidbodycomponentid")->value());
		if (rigidBodyComponentID == -1)
			rb = go->GetComponent<RigidBodyComponent>();
		else
			rb = mGameObjects[atoi(node->first_attribute("rigidbodycomponentid")->value())]->GetComponent<RigidBodyComponent>();

		DamageableComponent* dmg;
		int dmgComponentID = atoi(node->first_attribute("damageablecomponentid")->value());
		if (dmgComponentID == -1)
			dmg = go->GetComponent<DamageableComponent>();
		else
			dmg = mGameObjects[atoi(node->first_attribute("damageablecomponentid")->value())]->GetComponent<DamageableComponent>();

		ProjectileManagerComponent* projectileManager;
		int projmanagerID = atoi(node->first_attribute("projectilemangercomponentid")->value());
		if (projmanagerID == -1)
			projectileManager = go->GetComponent<ProjectileManagerComponent>();
		else
			projectileManager = mGameObjects[atoi(node->first_attribute("projectilemangercomponentid")->value())]->GetComponent<ProjectileManagerComponent>();

		float patrolTime = (float)atof(node->first_attribute("patrolTime")->value());

		AIAgentPatrolDirection dir;
		if (std::string(node->first_attribute("startdirection")->value()) == "left")
			dir = AIAgentPatrolDirection::ePatrollingLeft;
		else if (std::string(node->first_attribute("startdirection")->value()) == "right")
			dir = AIAgentPatrolDirection::ePatrollingRight;

		float idleTime = (float)atof(node->first_attribute("idletime")->value());

		TransformComponent* targetTrans;
		transformComponentID = atoi(node->first_attribute("targettransformcomponentid")->value());
		if (transformComponentID == -1)
			targetTrans = go->GetComponent<TransformComponent>();
		else
			targetTrans = mGameObjects[atoi(node->first_attribute("targettransformcomponentid")->value())]->GetComponent<TransformComponent>();

		float viewRange = (float)atof(node->first_attribute("viewrange")->value());
		float shotInterval = (float)atof(node->first_attribute("shotintervals")->value());

		return ComponentFactory::MakeAIAgentComponent(trans, anim, rb, dmg, projectileManager, GameCamera::Instance().GetComponent<TransformComponent>(), patrolTime, dir, idleTime, targetTrans, viewRange, shotInterval);
	}
	else if (std::string(node->first_attribute("type")->value()) == "ProjectileManagerComponent")
	{
		int projectileCount = atoi(node->first_attribute("projectilecount")->value());
		std::string projectHitTag = std::string(node->first_attribute("projecthittag")->value());
		std::vector<GameObject*> projectiles;
		for (int i = 0; i < projectileCount; i++)
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
			ProjectileComponent* ballProjectile = ComponentFactory::MakeProjectileComponent(projectHitTag, 10, 10);
			ball->AddComponent(ballProjectile);

			projectiles.push_back(ball);
		}

		return ComponentFactory::MakeProjectileManagerComponent(projectiles);
	}
	else if (std::string(node->first_attribute("type")->value()) == "TriggerBoxComponent")
	{
		std::string triggerTag = std::string(node->first_attribute("triggertag")->value());
		return ComponentFactory::MakeTriggerBox(triggerTag);
	}

	throw;
	return nullptr;
}
