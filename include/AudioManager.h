#pragma once

#include <SDL_mixer.h>
#include <string>

class AudioManager {
public:
    AudioManager();
    ~AudioManager();

    bool Initialize();
    void Shutdown();
    bool LoadSound(const std::string& filePath, const std::string& soundID);
    void PlaySound(const std::string& soundID);
    void LoadMusic(const std::string& filePath);
    void PlayMusic();

private:
    Mix_Chunk* soundEffect;
    Mix_Music* music;
};