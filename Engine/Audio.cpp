#include "Audio.h"

Audio::Audio()
{
	DirectX::AUDIO_ENGINE_FLAGS eflags = DirectX::AudioEngine_Default;
#ifdef _DEBUG
	eflags = eflags | DirectX::AudioEngine_Debug;
#endif

	mAudioEngine = std::make_unique<DirectX::AudioEngine>(eflags);
	mRetryAudio = false;

	CreateSoundEffects();

	if (!mAudioEngine->IsAudioDevicePresent())
	{
		// we are in 'silent mode'. 
	}
}

Audio::~Audio()
{
	if (mAudioEngine)
	{
		mAudioEngine->Suspend();
	}
}

void Audio::Update()
{
	if (mRetryAudio)
	{
		mRetryAudio = false;
		if (mAudioEngine->Reset())
		{
			// TODO: restart any looped sounds here
		}
	}
	else if (!mAudioEngine->Update())
	{
		if (mAudioEngine->IsCriticalError())
		{
			// We lost the audio device!
			mRetryAudio = true;
		}
	}
}

void Audio::Suspend()
{
	mAudioEngine->Suspend();
}

void Audio::Resume()
{
	mAudioEngine->Resume();
}

void Audio::PlaySoundEffect(std::string name)
{
	mAudioFiles.at(name)->Play();
}

void Audio::CreateSoundEffects()
{
	for (auto s : AudioFilePaths)
	{
		std::wstring widestr = std::wstring(s.second.begin(), s.second.end());
		const wchar_t* szName = widestr.c_str();

		mAudioFiles.insert(std::make_pair(s.first, std::make_unique<DirectX::SoundEffect>(mAudioEngine.get(), szName)));
	}
}
