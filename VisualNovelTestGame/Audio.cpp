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