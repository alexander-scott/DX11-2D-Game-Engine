#include "Audio.h"

Audio::Audio()
{
	DirectX::AUDIO_ENGINE_FLAGS eflags = DirectX::AudioEngine_Default;
#ifdef _DEBUG
	eflags = eflags | DirectX::AudioEngine_Debug;
#endif

	m_audEngine = std::make_unique<DirectX::AudioEngine>(eflags);
	m_retryAudio = false;

	if (!m_audEngine->IsAudioDevicePresent())
	{
		// we are in 'silent mode'. 
	}
}

Audio::~Audio()
{
	if (m_audEngine)
	{
		m_audEngine->Suspend();
	}
}

void Audio::Update()
{
	if (m_retryAudio)
	{
		m_retryAudio = false;
		if (m_audEngine->Reset())
		{
			// TODO: restart any looped sounds here
		}
	}
	else if (!m_audEngine->Update())
	{
		if (m_audEngine->IsCriticalError())
		{
			// We lost the audio device!
			m_retryAudio = true;
		}
	}
}

void Audio::Suspend()
{
	m_audEngine->Suspend();
}

void Audio::Resume()
{
	m_audEngine->Resume();
}
