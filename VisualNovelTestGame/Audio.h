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

	//Create the sound to play the sound
	Sound backgroundSound;
	Sound clickButtonSound;
	Sound correctAnswerSound;
	Sound incorrectAnswerSound;
public:
	void playBackgroundSound();
	void playclickButtonSound();
	void correctAnswerSound();
	void incorrectAnswerSound();

};