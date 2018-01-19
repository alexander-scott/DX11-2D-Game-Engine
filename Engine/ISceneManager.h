#pragma once

#include <string>

class ISceneManager
{
public:
	ISceneManager();
	~ISceneManager();

	void LoadScene(std::string sceneName)
	{
		NewSceneName = sceneName;
		LoadNewScene = true;
	}

	static ISceneManager& Instance()
	{
		static ISceneManager Instance;
		return Instance;
	}

	std::string NewSceneName;
	bool		LoadNewScene = false;
};

