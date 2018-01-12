#pragma once

#include "DirectXTK\Inc\Audio.h"

#include <map>

// WHY IS THIS HERE AND NOT IN CONSTS.H????
static std::map<std::string, std::string> AudioFilePaths =
{
	{ "Whoosh",			"C:\\Users\\s005973c\\Dropbox\\Unversity Year 4\\GAME ENGINE PROGRAMMING AND ARCHITECTURE\\DirectX2DFrameworkNew\\Engine\\Audio\\Whoosh.wav"  },
	{ "GunShot",		"C:\\Users\\s005973c\\Dropbox\\Unversity Year 4\\GAME ENGINE PROGRAMMING AND ARCHITECTURE\\DirectX2DFrameworkNew\\Engine\\Audio\\GunShot.wav" },	
	{ "Jump",			"C:\\Users\\s005973c\\Dropbox\\Unversity Year 4\\GAME ENGINE PROGRAMMING AND ARCHITECTURE\\DirectX2DFrameworkNew\\Engine\\Audio\\Jump.wav"	 },
	{ "Death",			"C:\\Users\\s005973c\\Dropbox\\Unversity Year 4\\GAME ENGINE PROGRAMMING AND ARCHITECTURE\\DirectX2DFrameworkNew\\Engine\\Audio\\Death.wav"   },
	{ "Win",			"C:\\Users\\s005973c\\Dropbox\\Unversity Year 4\\GAME ENGINE PROGRAMMING AND ARCHITECTURE\\DirectX2DFrameworkNew\\Engine\\Audio\\Win.wav"     },
	{ "Gameover",		"C:\\Users\\s005973c\\Dropbox\\Unversity Year 4\\GAME ENGINE PROGRAMMING AND ARCHITECTURE\\DirectX2DFrameworkNew\\Engine\\Audio\\Gameover.wav"},
	{ "Tap",			"C:\\Users\\s005973c\\Dropbox\\Unversity Year 4\\GAME ENGINE PROGRAMMING AND ARCHITECTURE\\DirectX2DFrameworkNew\\Engine\\Audio\\Tap.wav" },
	{ "Grunt",			"C:\\Users\\s005973c\\Dropbox\\Unversity Year 4\\GAME ENGINE PROGRAMMING AND ARCHITECTURE\\DirectX2DFrameworkNew\\Engine\\Audio\\Grunt.wav" },
};

class Audio 
{
	friend class MainWindow;

public:
	Audio();
	~Audio();

	void Update();
	void Suspend();
	void Resume();

	void PlaySoundEffect(std::string name);

	void OnNewAudioDevice() { mRetryAudio = true; }
	void CreateSoundEffects();

	static Audio& Instance()
	{
		static Audio Instance;
		return Instance;
	}

private:
	std::unique_ptr<DirectX::AudioEngine>							mAudioEngine;
	std::map<std::string, std::unique_ptr<DirectX::SoundEffect>>	mAudioFiles;
	bool															mRetryAudio;
};
