#pragma once

#include "ObjectManager.h"

using namespace std;

class Scene
{
public:
	Scene();
	~Scene();

	virtual void Draw();

protected:
	vector<shared_ptr<GameObject>>						mRenderLayer0;
	vector<shared_ptr<GameObject>>						mRenderLayer1;
	vector<shared_ptr<GameObject>>						mRenderLayer2;

	vector<shared_ptr<GameObject>>						mGameObjects;
};

