#pragma once

#include "GameLevel.h"
#include "LevelBuilder.h"

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void LoadScene(std::string sceneName);

	void Update(float deltaTime);
	void Draw();

	static SceneManager& Instance()
	{
		static SceneManager Instance;
		return Instance;
	}

private:
	shared_ptr<GameLevel>			mGameLevel;
};

