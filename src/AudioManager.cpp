#include "AudioManager.h"
#include <iostream>
#include <unordered_map>

std::unordered_map<std::string, Mix_Chunk*> soundMap;

AudioManager::AudioManager()
	: soundEffect(nullptr), music(nullptr)
{
}

AudioManager::~AudioManager()
{
	Shutdown();
}

bool AudioManager::Initialize()
{
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return false;
    }
    return true;
}

void AudioManager::Shutdown()
{
    for (auto& sound : soundMap) {
        Mix_FreeChunk(sound.second);
    }
    soundMap.clear();

    if (music) {
        Mix_FreeMusic(music);
        music = nullptr;
    }

    Mix_Quit();
}

bool AudioManager::LoadSound(const std::string& filePath, const std::string& soundID)
{
    soundEffect = Mix_LoadWAV(filePath.c_str());
    if (soundEffect == nullptr) {
        std::cerr << "Failed to load sound effect! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return false;
    }
    soundMap[soundID] = soundEffect;
    return true;
}

void AudioManager::PlaySound(const std::string& soundID)
{
    Mix_PlayChannel(-1, soundMap[soundID], 0);
}

void AudioManager::LoadMusic(const std::string& filePath)
{
    music = Mix_LoadMUS(filePath.c_str());
    if (music == nullptr) {
        std::cerr << "Failed to load music! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }
}

void AudioManager::PlayMusic()
{
    Mix_PlayMusic(music, -1);
}
