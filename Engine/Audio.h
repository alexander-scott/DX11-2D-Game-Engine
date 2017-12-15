#pragma once

#include "DirectXTK\Inc\Audio.h"

class Audio 
{
	friend class MainWindow;

public:
	Audio();
	~Audio();

	void Update();
	void Suspend();
	void Resume();

	void OnNewAudioDevice() { m_retryAudio = true; }

	static Audio& Instance()
	{
		static Audio Instance;
		return Instance;
	}

private:
	std::unique_ptr<DirectX::AudioEngine> m_audEngine;
	bool m_retryAudio;
};
