#pragma once

#include <SFML/Audio.hpp>
#include <string>               // <— add this

class Audio {
private:
    // sound buffers
    sf::SoundBuffer backgroundBuffer;
    sf::SoundBuffer clickButtonBuffer;
    sf::SoundBuffer correctAnswerBuffer;
    sf::SoundBuffer incorrectAnswerBuffer;
    sf::SoundBuffer introductionBuffer;
    sf::SoundBuffer loadedBuffer;

    // sounds
    sf::Sound backgroundSound;
    sf::Sound clickButtonSound;
    sf::Sound correctAnswerSound;
    sf::Sound incorrectAnswerSound;
    sf::Sound introductionSound;
    sf::Sound loadedSound;

public:
    void playBackgroundSound();

    // prefer passing bool by value rather than const-ref
    void playSound(const std::string& audioPath, bool loop);

    void playClickButtonSound();
    void playCorrectAnswerSound();
    void playIncorrectAnswerSound();
    void playIntroductionSound();

    bool isIntroductionSoundPlaying() const;
};
