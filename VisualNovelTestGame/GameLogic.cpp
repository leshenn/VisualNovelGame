#include "GameLogic.h"
#include "QuizUI.h"
#include "QuizManager.h"
#include <SFML/Window.hpp>
#include "Audio.h"

using namespace sf;

void handleGameLogic(RenderWindow& window, GameState& currentState, ButtonLayout& layout, LoadSprites& loadSprites, Event& event, Audio& audio)
{   
    switch (currentState) {
    case GameState::MENU:
        if (event.type == Event::MouseButtonPressed) {
            audio.playClickButtonSound();
            if (layout.playButtonClicked(window)) {
                currentState = GameState::INTRO; // Change state when Play button is clicked

            }
        }

        // Show the necessary sprites and buttons
        window.clear();

        // load in necessary sprites
        loadSprites.loadMenuScreen("Backgrounds/MenuBackground.png");

        window.draw(loadSprites.menuBackgroundSprite);
        layout.loadPlayButton();
        break;

    case GameState::INTRO:
        if (event.type == Event::MouseButtonPressed) {
            audio.playClickButtonSound();
            if (layout.nextButtonClicked(window)) {
                currentState = GameState::STAGE_ONE_MENU;
            }
        }

        // Show the necessary sprites and buttons
        window.clear();

        // load ncecessary sprites
        loadSprites.loadInstructionScreen("Backgrounds/InstructionBackground.jpg", "Acessories/MenuScroll.png");

        window.draw(loadSprites.instructionBackgroundSprite);
        window.draw(loadSprites.menuScrollSprite);
        layout.loadNextButton();
        break;

    case GameState::STAGE_ONE_MENU:
        audio.playClickButtonSound();
        if (event.type == Event::MouseButtonPressed) {
            Vector2i mousePos = Mouse::getPosition(window);
            currentState = layout.loadButtonClicked(mousePos);
        }

        window.clear();
        loadSprites.loadMenuScreen("Backgrounds/MenuBackground00.png");
        window.draw(loadSprites.menuBackgroundSprite);
        layout.loadWorldButtons();
        break;

    case GameState::SEAWORLD:
        window.clear();
        loadSprites.loadGameScreen("Backgrounds/PoseidonBackground.jpg", "Characters/Poseidon.png", "Characters/MainCharacter.png", "Acessories/Scroll.png");
        window.draw(loadSprites.gameBackgroundSprite);
        window.draw(loadSprites.godSprite);
        window.draw(loadSprites.mainCharacterSprite);
        window.draw(loadSprites.gameScrollSprite);


        break;

    case GameState::UNDERWORLD:
        window.clear();
        loadSprites.loadGameScreen("Backgrounds/HadesBackground.jpg", "Characters/Hades.png", "Characters/MainCharacter.png", "Acessories/Scroll.png");
        window.draw(loadSprites.gameBackgroundSprite);
        window.draw(loadSprites.godSprite);
        window.draw(loadSprites.mainCharacterSprite);
        window.draw(loadSprites.gameScrollSprite);
        break;

    case GameState::COUNTRY_SIDE:
        window.clear();
        loadSprites.loadGameScreen("Backgrounds/DionysusBackground.jpg", "Characters/Dionysus.png", "Characters/MainCharacter.png", "Acessories/Scroll.png");
        window.draw(loadSprites.gameBackgroundSprite);
        window.draw(loadSprites.godSprite);
        window.draw(loadSprites.mainCharacterSprite);
        window.draw(loadSprites.gameScrollSprite);
        break;

    default:
        break;
    }

    window.display();  // Update the window with the newly drawn content
}