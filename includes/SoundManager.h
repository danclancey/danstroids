#pragma once
#include <SFML/Audio.hpp>
#include <map>

enum class SoundType {
    SHOOT,
    ASTEROID_EXPLOSION,
    PLAYER_DEATH
};

class SoundManager {
public:
    SoundManager();

    void play(SoundType type);
private:
    std::map<SoundType, sf::SoundBuffer> soundBuffers;

    sf::Sound sound;
};
