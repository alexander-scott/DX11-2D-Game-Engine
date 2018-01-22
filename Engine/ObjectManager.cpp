#include "ObjectManager.h"

ObjectManager::ObjectManager()
{

}

shared_ptr<GameObject> ObjectManager::GetCreatedObject(int instanceID)
{
	return mGameObjects[instanceID];
}

shared_ptr<GameObject> ObjectManager::CreateObject(xml_node<>* node, ICameraGameObject* cam)
{
	int instanceID = atoi(node->first_attribute("instanceid")->value());
		
	if (instanceID == -1)
	{
		// Generate a random int
		instanceID = GenerateNewID();
	}

	// Create the GameObject
	auto gameObj = GameObject::MakeGameObject(node->first_attribute("tag")->value(), instanceID);
	mGameObjects.insert(make_pair(instanceID, gameObj));

	// Create this gameobjects components
	xml_node<>* component = node->first_node("Component");
	while (component)
	{
		IComponent* newComponent = CreateComponent(gameObj, component, cam);

		if (component->first_attribute("componentinactive") != nullptr)
			newComponent->SetActive(false);

		gameObj->AddComponent(newComponent);
		component = component->next_sibling("Component");
	}

	return gameObj;
}

IComponent* ObjectManager::CreateComponent(shared_ptr<GameObject> go, xml_node<>* node, ICameraGameObject* cam)
{
	if (string(node->first_attribute("type")->value()) == "TransformComponent")
	{
		float xPos = (float)atof(node->first_attribute("xpos")->value());
		float yPos = -(float)atof(node->first_attribute("ypos")->value());
		float rot = (float)atof(node->first_attribute("rotation")->value());
		float scale = (float)atof(node->first_attribute("scale")->value());

		return ComponentFactory::MakeTransform(Vec2(xPos, yPos), rot, scale);
	}
	else if (string(node->first_attribute("type")->value()) == "SpriteRendererComponent")
	{
		string fileName = string(node->first_attribute("filename")->value());

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

		int renderLayer = atoi(node->first_attribute("renderLayer")->value());

		return ComponentFactory::MakeSpriteRenderer(fileName, renderLayer, trans, width, height, Vec2(xOffset, yOffset));
	}
	else if (string(node->first_attribute("type")->value()) == "SpriteAnimatorComponent")
	{
		string fileName = string(node->first_attribute("filename")->value());

		TransformComponent* trans;
		int transformComponentID = atoi(node->first_attribute("transformcomponentid")->value());
		if (transformComponentID == -1)
			trans = go->GetComponent<TransformComponent>();
		else
			trans = mGameObjects[atoi(node->first_attribute("transformcomponentid")->value())]->GetComponent<TransformComponent>();

		float width = (float)atof(node->first_attribute("width")->value());
		float height = (float)atof(node->first_attribute("height")->value());

		vector<AnimationDesc> animDescriptions;
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
		int renderLayer = atoi(node->first_attribute("renderLayer")->value());

		return ComponentFactory::MakeSpriteAnimator(fileName, renderLayer, trans, width, height, animDescriptions, currentAnim);
	}
	else if (string(node->first_attribute("type")->value()) == "RigidBodyComponent")
	{
		float staticF = (float)atof(node->first_attribute("staticfriction")->value());
		float dynamicF = (float)atof(node->first_attribute("dynamicfriction")->value());
		float restitution = (float)atof(node->first_attribute("restitution")->value());

		bool isStatic = false;
		if (string(node->first_attribute("static")->value()) == "true")
			isStatic = true;

		bool lockRotation = false;
		if (string(node->first_attribute("lockrotation")->value()) == "true")
			lockRotation = true;

		return ComponentFactory::MakeRigidbody(staticF, dynamicF, restitution, isStatic, lockRotation);
	}
	else if (string(node->first_attribute("type")->value()) == "TextRendererComponent")
	{
		string text = string(node->first_attribute("text")->value());

		TransformComponent* trans;
		int transformComponentID = atoi(node->first_attribute("transformcomponentid")->value());
		if (transformComponentID == -1)
			trans = go->GetComponent<TransformComponent>();
		else
			trans = mGameObjects[atoi(node->first_attribute("transformcomponentid")->value())]->GetComponent<TransformComponent>();

		return ComponentFactory::MakeTextRenderer(text, DirectX::Colors::Yellow, trans); // TODO: Remove default yellow colour
	}
	else if (string(node->first_attribute("type")->value()) == "CircleColliderComponent")
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
	else if (string(node->first_attribute("type")->value()) == "PolygonColliderComponent")
	{
		throw exception("WRONG");
	}
	else if (string(node->first_attribute("type")->value()) == "BoxColliderComponent")
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
	else if (string(node->first_attribute("type")->value()) == "ColliderRendererComponent")
	{
		throw;
	}
	else if (string(node->first_attribute("type")->value()) == "TiledBGRenderer")
	{
		string spriteName = string(node->first_attribute("spritename")->value());
		float width = (float)atof(node->first_attribute("spritewidth")->value());
		float height = (float)atof(node->first_attribute("spriteheight")->value());
		float moveRate = (float)atof(node->first_attribute("moverate")->value());

		TiledBGDirection dir;
		if (string(node->first_attribute("direction")->value()) == "horizontal")
			dir = TiledBGDirection::eHorizontal;
		else if (string(node->first_attribute("direction")->value()) == "vertical")
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

		int renderLayer = atoi(node->first_attribute("renderLayer")->value());

		return ComponentFactory::MakeTiledBGRenderer(spriteName, renderLayer, width, height, moveRate, dir, trans, focusTrans);
	}
	else if (string(node->first_attribute("type")->value()) == "PlayerComponent")
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

		return ComponentFactory::MakePlayerComponent(trans, anim, rb, dmg, projectileManager, cam->GetComponent<TransformComponent>());
	}
	else if (string(node->first_attribute("type")->value()) == "DamageableComponent")
	{
		float startHealth = (float)atof(node->first_attribute("starthealth")->value());
		string hitNoise = string(node->first_attribute("hitnoise")->value());

		return ComponentFactory::MakeDamageableComponent(startHealth, hitNoise);
	}
	else if (string(node->first_attribute("type")->value()) == "ProjectileComponent")
	{
		string affectedTag = string(node->first_attribute("affectedTag")->value());
		float lifeSpan = (float)atof(node->first_attribute("lifespan")->value());
		float damage = (float)atof(node->first_attribute("damage")->value());

		return ComponentFactory::MakeProjectileComponent(affectedTag, lifeSpan, damage);
	}
	else if (string(node->first_attribute("type")->value()) == "AIAgentComponent")
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
		if (string(node->first_attribute("startdirection")->value()) == "left")
			dir = AIAgentPatrolDirection::ePatrollingLeft;
		else if (string(node->first_attribute("startdirection")->value()) == "right")
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

		return ComponentFactory::MakeAIAgentComponent(trans, anim, rb, dmg, projectileManager, cam->GetComponent<TransformComponent>(), patrolTime, dir, idleTime, targetTrans, viewRange, shotInterval);
	}
	else if (string(node->first_attribute("type")->value()) == "ProjectileManagerComponent")
	{
		int projectileCount = atoi(node->first_attribute("projectilecount")->value());
		string projectHitTag = string(node->first_attribute("projecthittag")->value());
		vector<shared_ptr<GameObject>> projectiles;
		for (int i = 0; i < projectileCount; i++)
		{
			int instanceID = GenerateNewID();
			auto ballGO = GameObject::MakeGameObject("Ball", GenerateNewID());
			mGameObjects.insert(make_pair(instanceID, ballGO));

			TransformComponent* ballTrans = ComponentFactory::MakeTransform(Vec2(0, 0), 0, 0.2f);
			ballGO->AddComponent(ballTrans);
			RigidBodyComponent* ballRb = ComponentFactory::MakeRigidbody(1, 0.3f, 0.5f, false, false); // Cache the rigidbody
			ballGO->AddComponent(ballRb);
			CircleColliderComponent* ballCollider = ComponentFactory::MakeCircleCollider(64, ballTrans, ballRb);
			ballGO->AddComponent(ballCollider);
			SpriteRendererComponent* ballRenderer = ComponentFactory::MakeSpriteRenderer("Ball", 1, ballTrans, 128, 128, Vec2(0, 0));
			ballGO->AddComponent(ballRenderer);
			ProjectileComponent* ballProjectile = ComponentFactory::MakeProjectileComponent(projectHitTag, 10, 10);
			ballGO->AddComponent(ballProjectile);

			projectiles.push_back(ballGO);
		}

		return ComponentFactory::MakeProjectileManagerComponent(projectiles);
	}
	else if (string(node->first_attribute("type")->value()) == "TriggerBoxComponent")
	{
		string triggerTag = string(node->first_attribute("triggertag")->value());
		return ComponentFactory::MakeTriggerBox(triggerTag);
	}
	else if (string(node->first_attribute("type")->value()) == "GameCameraComponent")
	{
		TransformComponent* trans;
		int transformComponentID = atoi(node->first_attribute("focusTransID")->value());
		if (transformComponentID == -1)
			trans = go->GetComponent<TransformComponent>();
		else
			trans = mGameObjects[transformComponentID]->GetComponent<TransformComponent>();

		float leftBound = (float)atof(node->first_attribute("leftBound")->value());
		float rightBound = (float)atof(node->first_attribute("rightBound")->value());
		float bottomBound = (float)atof(node->first_attribute("bottomBound")->value());
		float topBound = (float)atof(node->first_attribute("topBound")->value());

		float focusHeight = (float)atof(node->first_attribute("focusHeight")->value());
		float focusWidth = (float)atof(node->first_attribute("focusWidth")->value());

		return ComponentFactory::MakeGameCameraComponent(cam->GetComponent<TransformComponent>(), trans,
			focusWidth, focusHeight, leftBound, rightBound, topBound, bottomBound);
	}
	else if (string(node->first_attribute("type")->value()) == "GUITextComponent")
	{
		string text = string(node->first_attribute("text")->value());

		TransformComponent* trans;
		int transformComponentID = atoi(node->first_attribute("transformcomponentid")->value());
		if (transformComponentID == -1)
			trans = go->GetComponent<TransformComponent>();
		else
			trans = mGameObjects[transformComponentID]->GetComponent<TransformComponent>();

		float r = (float)atof(node->first_attribute("r")->value());
		float g = (float)atof(node->first_attribute("g")->value());
		float b = (float)atof(node->first_attribute("b")->value());

		float xOffSet = (float)atof(node->first_attribute("xoffset")->value());
		float yOffSet = (float)atof(node->first_attribute("yoffset")->value());

		int renderLayer = atoi(node->first_attribute("renderLayer")->value());

		return ComponentFactory::MakeGUIText(text, renderLayer, r, g, b, trans, Vec2(xOffSet, yOffSet));
	}
	else if (string(node->first_attribute("type")->value()) == "GUITextValueComponent")
	{
		string text = string(node->first_attribute("text")->value());
		string valueName = string(node->first_attribute("valueName")->value());

		TransformComponent* trans;
		int transformComponentID = atoi(node->first_attribute("transformcomponentid")->value());
		if (transformComponentID == -1)
			trans = go->GetComponent<TransformComponent>();
		else
			trans = mGameObjects[transformComponentID]->GetComponent<TransformComponent>();

		float r = (float)atof(node->first_attribute("r")->value());
		float g = (float)atof(node->first_attribute("g")->value());
		float b = (float)atof(node->first_attribute("b")->value());

		float xOffSet = (float)atof(node->first_attribute("xoffset")->value());
		float yOffSet = (float)atof(node->first_attribute("yoffset")->value());

		int renderLayer = atoi(node->first_attribute("renderLayer")->value());

		return ComponentFactory::MakeGUITextValueComponent(valueName, renderLayer, text, r, g, b, trans, Vec2(xOffSet, yOffSet));
	}
	else if (string(node->first_attribute("type")->value()) == "GUITextDamageComponent")
	{
		string text = string(node->first_attribute("text")->value());

		TransformComponent* trans;
		int transformComponentID = atoi(node->first_attribute("transformcomponentid")->value());
		if (transformComponentID == -1)
			trans = go->GetComponent<TransformComponent>();
		else
			trans = mGameObjects[transformComponentID]->GetComponent<TransformComponent>();

		DamageableComponent* dmg;
		int damageComponentID = atoi(node->first_attribute("damagecomponentid")->value());
		if (damageComponentID == -1)
			dmg = go->GetComponent<DamageableComponent>();
		else
			dmg = mGameObjects[damageComponentID]->GetComponent<DamageableComponent>();

		float r = (float)atof(node->first_attribute("r")->value());
		float g = (float)atof(node->first_attribute("g")->value());
		float b = (float)atof(node->first_attribute("b")->value());

		float xOffSet = (float)atof(node->first_attribute("xoffset")->value());
		float yOffSet = (float)atof(node->first_attribute("yoffset")->value());

		int renderLayer = atoi(node->first_attribute("renderLayer")->value());

		return ComponentFactory::MakeGUITextDamageComponent(dmg, renderLayer, text, r, g, b, trans, Vec2(xOffSet, yOffSet));
	}
	else if (string(node->first_attribute("type")->value()) == "GUIButtonComponent")
	{
		TransformComponent* trans;
		int transformComponentID = atoi(node->first_attribute("transformcomponentid")->value());
		if (transformComponentID == -1)
			trans = go->GetComponent<TransformComponent>();
		else
			trans = mGameObjects[transformComponentID]->GetComponent<TransformComponent>();

		float width = (float)atof(node->first_attribute("width")->value());
		float height = (float)atof(node->first_attribute("height")->value());

		return ComponentFactory::MakeGUIButton(trans, width, height);
	}
	else if (string(node->first_attribute("type")->value()) == "GUISpriteRendererComponent")
	{
		string fileName = string(node->first_attribute("filename")->value());

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

		int renderLayer = atoi(node->first_attribute("renderLayer")->value());

		return ComponentFactory::MakeGUISpriteRenderer(fileName, renderLayer, trans, width, height, Vec2(xOffset, yOffset));
	}
	else if (string(node->first_attribute("type")->value()) == "GameManagerComponent")
	{
		GUIButtonComponent* button;
		int buttonComponentID = atoi(node->first_attribute("guibuttonid")->value());
		if (buttonComponentID == -1)
			button = go->GetComponent<GUIButtonComponent>();
		else
			button = mGameObjects[buttonComponentID]->GetComponent<GUIButtonComponent>();

		GUITextComponent* text;
		int textComponentID = atoi(node->first_attribute("guitextid")->value());
		if (textComponentID == -1)
			text = go->GetComponent<GUITextComponent>();
		else
			text = mGameObjects[textComponentID]->GetComponent<GUITextComponent>();

		GUISpriteRendererComponent* sprite;
		int spriteComponentID = atoi(node->first_attribute("guispriteid")->value());
		if (spriteComponentID == -1)
			sprite = go->GetComponent<GUISpriteRendererComponent>();
		else
			sprite = mGameObjects[spriteComponentID]->GetComponent<GUISpriteRendererComponent>();

		TriggerBoxComponent* triggerbox;
		int triggerComponentID = atoi(node->first_attribute("triggerboxid")->value());
		if (triggerComponentID == -1)
			triggerbox = go->GetComponent<TriggerBoxComponent>();
		else
			triggerbox = mGameObjects[triggerComponentID]->GetComponent<TriggerBoxComponent>();

		DamageableComponent* damage;
		int damageComponentID = atoi(node->first_attribute("damageid")->value());
		if (damageComponentID == -1)
			damage = go->GetComponent<DamageableComponent>();
		else
			damage = mGameObjects[damageComponentID]->GetComponent<DamageableComponent>();

		return ComponentFactory::MakeGameManagerComponent(button, text, sprite, triggerbox, damage);
	}

	throw;
	return nullptr;
}

int ObjectManager::GenerateNewID()
{
	// Generate a random int
	int instanceID = std::rand();
	auto it = mGameObjects.find(instanceID);
	while (it != mGameObjects.end()) // Make sure it doesn't already exist in the map
	{
		instanceID = std::rand();
		it = mGameObjects.find(instanceID);
	}
	return instanceID;
}
