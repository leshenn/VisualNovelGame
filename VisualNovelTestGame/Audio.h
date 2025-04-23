#pragma once
#include <SFML/Audio.hpp>

using namespace sf;


class Audio {
private:
	//Create the sound buffers to store the file
	SoundBuffer backgroundBuffer;
	SoundBuffer clickButtonBuffer;
	SoundBuffer correctAnswerBuffer;
	SoundBuffer incorrectAnswerBuffer;
	SoundBuffer introductionBuffer;

	//Create the sound to play the sound
	Sound backgroundSound;
	Sound clickButtonSound;
	Sound correctAnswerSound;
	Sound incorrectAnswerSound;
	Sound introductionSound;
public:
	//Create the functions for wach sound
	void playBackgroundSound();

	void playClickButtonSound();
	
	void playCorrectAnswerSound();
	
	void playIncorrectAnswerSound();

	void playIntroductionSound();

	bool isIntroductionSoundPlaying() const;

};