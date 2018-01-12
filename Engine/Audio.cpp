#include "Audio.h"

Audio::Audio()
{
	DirectX::AUDIO_ENGINE_FLAGS eflags = DirectX::AudioEngine_Default;
#ifdef _DEBUG
	eflags = eflags | DirectX::AudioEngine_Debug;
#endif

	mAudioEngine = std::make_unique<DirectX::AudioEngine>(eflags);
	mRetryAudio = false;

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

void Audio::CreateSoundEffects(std::string resourcesPath)
{
	for (auto s : AudioFilePaths)
	{
		std::string filePath = s.second;
		filePath = resourcesPath + filePath;

		std::wstring widestr = std::wstring(filePath.begin(), filePath.end());
		const wchar_t* szName = widestr.c_str();

		mAudioFiles.insert(std::make_pair(s.first, std::make_unique<DirectX::SoundEffect>(mAudioEngine.get(), szName)));
	}
}
