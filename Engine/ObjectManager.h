#pragma once

#include <vector>
#include <fstream>

#include "GameObject.h"
#include "GameComponentFactory.h"
#include "ICameraGameObject.h"

#include "Consts.h"

#include "rapidxml.hpp"

using namespace rapidxml;
using namespace std;

class ObjectManager
{
public:
	ObjectManager();

	shared_ptr<GameObject> CreateObject(xml_node<>* node, ICameraGameObject* cam);
	shared_ptr<GameObject> GetCreatedObject(int instanceID);

private:
	IComponent* CreateComponent(shared_ptr<GameObject> go, xml_node<>* node, ICameraGameObject* cam);

	TransformComponent* ParseTransformComponent(shared_ptr<GameObject> go, xml_node<>* node, ICameraGameObject* cam);
	SpriteRendererComponent* ParseSpriteRendererComponent(shared_ptr<GameObject> go, xml_node<>* node, ICameraGameObject* cam);
	SpriteAnimatorComponent* ParseSpriteAnimatorComponent(shared_ptr<GameObject> go, xml_node<>* node, ICameraGameObject* cam);
	RigidBodyComponent* ParseRigidBodyComponent(shared_ptr<GameObject> go, xml_node<>* node, ICameraGameObject* cam);
	TextRendererComponent* ParseTextRendererComponent(shared_ptr<GameObject> go, xml_node<>* node, ICameraGameObject* cam);
	CircleColliderComponent* ParseCircleColliderComponent(shared_ptr<GameObject> go, xml_node<>* node, ICameraGameObject* cam);
	BoxColliderComponent* ParseBoxColliderComponent(shared_ptr<GameObject> go, xml_node<>* node, ICameraGameObject* cam);
	TiledBGRenderer* ParseTiledBGRenderer(shared_ptr<GameObject> go, xml_node<>* node, ICameraGameObject* cam);
	PlayerComponent* ParsePlayerComponent(shared_ptr<GameObject> go, xml_node<>* node, ICameraGameObject* cam);
	DamageableComponent* ParseDamageableComponent(shared_ptr<GameObject> go, xml_node<>* node, ICameraGameObject* cam);
	ProjectileComponent* ParseProjectileComponent(shared_ptr<GameObject> go, xml_node<>* node, ICameraGameObject* cam);
	AIAgentComponent* ParseAIAgentComponent(shared_ptr<GameObject> go, xml_node<>* node, ICameraGameObject* cam);
	ProjectileManagerComponent* ParseProjectileManagerComponent(shared_ptr<GameObject> go, xml_node<>* node, ICameraGameObject* cam);
	TriggerBoxComponent* ParseTriggerBoxComponent(shared_ptr<GameObject> go, xml_node<>* node, ICameraGameObject* cam);
	GameCameraComponent* ParseGameCameraComponent(shared_ptr<GameObject> go, xml_node<>* node, ICameraGameObject* cam);
	GUITextComponent* ParseGUITextComponent(shared_ptr<GameObject> go, xml_node<>* node, ICameraGameObject* cam);
	GUITextValueComponent* ParseGUITextValueComponent(shared_ptr<GameObject> go, xml_node<>* node, ICameraGameObject* cam);
	GUITextDamageComponent* ParseGUITextDamageComponent(shared_ptr<GameObject> go, xml_node<>* node, ICameraGameObject* cam);
	GUIButtonComponent* ParseGUIButtonComponent(shared_ptr<GameObject> go, xml_node<>* node, ICameraGameObject* cam);
	GUISpriteRendererComponent* ParseGUISpriteRendererComponent(shared_ptr<GameObject> go, xml_node<>* node, ICameraGameObject* cam);
	GameManagerComponent* ParseGameManagerComponent(shared_ptr<GameObject> go, xml_node<>* node, ICameraGameObject* cam);
	
	int GenerateNewID();

	map<int, shared_ptr<GameObject>>		mGameObjects;
};

