#pragma once

#include <string>

class SceneManagement
{
public:
	void LoadScene(std::string sceneName)
	{
		NewSceneName = sceneName;
		LoadNewScene = true;
	}

	static SceneManagement& Instance()
	{
		static SceneManagement Instance;
		return Instance;
	}

	std::string NewSceneName;
	bool		LoadNewScene = false;
};

