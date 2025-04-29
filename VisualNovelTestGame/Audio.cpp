#include <SFML/Audio.hpp>
#include "Audio.h"
#include <iostream>

using namespace sf;
using namespace std;

void Audio::playBackgroundSound() {
	if (!backgroundBuffer.loadFromFile("Audio/Background.wav")) {
		cout << "Cannot find background audio";
	}

	backgroundSound.setBuffer(backgroundBuffer);
	backgroundSound.setLoop(true);
	backgroundSound.setVolume(20);
	backgroundSound.play();
}

//play any sound and decide if it should be looped
void Audio::playSound(const string& audioPath, bool loop) {
	loadedSound.setLoop(false);
	if (!audioPath.empty() && audioPath != "") {
		if (!loadedBuffer.loadFromFile(audioPath)) {
			cout << "Cannot find laoded audio";
		}

		loadedSound.setBuffer(loadedBuffer);
		loadedSound.setLoop(loop);
		loadedSound.setVolume(20);
		loadedSound.play();
	}
}


void Audio::playClickButtonSound() {
	if (!clickButtonBuffer.loadFromFile("Audio/Click.wav")) {
		cout << "Cannot find background audio";
		return;
	}

	clickButtonSound.setBuffer(clickButtonBuffer);
	clickButtonSound.play();
}


void Audio::playCorrectAnswerSound() {
	if (!correctAnswerBuffer.loadFromFile("Audio/Correct.wav")) {
		cout << "Cannot find background audio";
		return;
	}

	correctAnswerSound.setBuffer(correctAnswerBuffer);
	correctAnswerSound.play();
}


void Audio::playIncorrectAnswerSound() {
	if (!incorrectAnswerBuffer.loadFromFile("Audio/Incorrect.wav")) {
		cout << "Error: Cannot find Incorrect Answer audio" << endl;
		return;
	}

	incorrectAnswerSound.setBuffer(incorrectAnswerBuffer); // Use existing member
	incorrectAnswerSound.play();
}

void Audio::playIntroductionSound() {
	if (!introductionBuffer.loadFromFile("Audio/Instruction.mp3")) {
		cout << "Error: Cannot find Incorrect Answer audio" << endl;
		return;
	}

	introductionSound.setBuffer(introductionBuffer); // Use existing member
	introductionSound.play();
}

bool Audio::isIntroductionSoundPlaying() const {
	return (introductionSound.getStatus() == sf::Sound::Playing);
}