#include "../includes/SoundManager.h"
#include <iostream>

SoundManager::SoundManager() {
    if (!soundBuffers[SoundType::SHOOT].loadFromFile("../assets/shoot.wav")) {
        std::cerr << "Error loading shoot.wav" << std::endl;
    }
    if (!soundBuffers[SoundType::ASTEROID_EXPLOSION].loadFromFile("../assets/explosion.wav")) {
        std::cerr << "Error loading explosion.wav" << std::endl;
    }
    if (!soundBuffers[SoundType::PLAYER_DEATH].loadFromFile("../assets/death.wav")) {
        std::cerr << "Error loading death.wav" << std::endl;
    }
}

void SoundManager::play(SoundType type) {
    if (soundBuffers.count(type)) {
        sound.setBuffer(soundBuffers[type]);
        sound.play();
    }
}
