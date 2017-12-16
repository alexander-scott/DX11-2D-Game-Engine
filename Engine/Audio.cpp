#include "Audio.h"

Audio::Audio()
{
	DirectX::AUDIO_ENGINE_FLAGS eflags = DirectX::AudioEngine_Default;
#ifdef _DEBUG
	eflags = eflags | DirectX::AudioEngine_Debug;
#endif

	m_audEngine = std::make_unique<DirectX::AudioEngine>(eflags);
	m_retryAudio = false;

	CreateSoundEffects();

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

void Audio::PlaySoundEffect(std::string name)
{
	m_audioFiles.at(name)->Play();
}

void Audio::CreateSoundEffects()
{
	for (auto s : AudioFilePaths)
	{
		std::wstring widestr = std::wstring(s.second.begin(), s.second.end());
		const wchar_t* szName = widestr.c_str();

		m_audioFiles.insert(std::make_pair(s.first, std::make_unique<DirectX::SoundEffect>(m_audEngine.get(), szName)));
	}
}
