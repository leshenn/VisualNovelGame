#include "GameLogic.h"
#include "QuizUI.h"
#include "QuizManager.h"
#include <SFML/Window.hpp>
#include "Audio.h"

using namespace sf;

void loadGameAssets(GameState currentState, LoadSprites& loadSprites)
{
    switch (currentState) {
    case GameState::MENU:
        loadSprites.loadMenuScreen("Backgrounds/MenuBackground.png");
        break;

    case GameState::INTRO:
        loadSprites.loadInstructionScreen("Backgrounds/InstructionBackground.jpg", "Acessories/MenuScroll.png");
        break;

    case GameState::STAGE_ONE_MENU:
        loadSprites.loadMenuScreen("Backgrounds/MenuBackground00.png");
        break;

    case GameState::SEAWORLD:
        loadSprites.loadGameScreen("Backgrounds/PoseidonBackground.jpg", "Characters/Poseidon.png", "Characters/MainCharacter.png", "Acessories/Scroll.png");
        break;

    case GameState::UNDERWORLD:
        loadSprites.loadGameScreen("Backgrounds/HadesBackground.jpg", "Characters/Hades.png", "Characters/MainCharacter.png", "Acessories/Scroll.png");
        break;

    case GameState::COUNTRY_SIDE:
        loadSprites.loadGameScreen("Backgrounds/DionysusBackground.jpg", "Characters/Dionysus.png", "Characters/MainCharacter.png", "Acessories/Scroll.png");
        break;

    default:
        break;
    }
}

void renderGameScene(RenderWindow& window, GameState currentState, ButtonLayout& layout, LoadSprites& loadSprites, QuizUI& quiz)
{
    switch (currentState) {
    case GameState::MENU:
        window.clear();
        window.draw(loadSprites.menuBackgroundSprite);
        layout.loadPlayButton();
        break;

    case GameState::INTRO:
        window.clear();
        window.draw(loadSprites.instructionBackgroundSprite);
        window.draw(loadSprites.menuScrollSprite);
        layout.loadNextButton();
        break;

    case GameState::STAGE_ONE_MENU:
        window.clear();
        window.draw(loadSprites.menuBackgroundSprite);
        layout.loadWorldButtons();
        break;

    case GameState::SEAWORLD:
        window.clear();
        window.draw(loadSprites.gameBackgroundSprite);
        window.draw(loadSprites.godSprite);
        window.draw(loadSprites.mainCharacterSprite);
        window.draw(loadSprites.gameScrollSprite);
      
        quiz.render();

        break;

    case GameState::UNDERWORLD:
        window.clear();
        window.draw(loadSprites.gameBackgroundSprite);
        window.draw(loadSprites.godSprite);
        window.draw(loadSprites.mainCharacterSprite);
        window.draw(loadSprites.gameScrollSprite);
        break;

    case GameState::COUNTRY_SIDE:
        window.clear();
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

void handleGameLogic(RenderWindow& window, GameState& currentState, ButtonLayout& layout, LoadSprites& loadSprites, Event& event, Audio& audio, QuizUI& quiz)
{
    switch (currentState) {
    case GameState::MENU:
        if (event.type == Event::MouseButtonPressed) {
            audio.playClickButtonSound();
            if (layout.playButtonClicked(window)) {
                currentState = GameState::INTRO; // Change state when Play button is clicked
            }
        }
        loadGameAssets(currentState, loadSprites);
        renderGameScene(window, currentState, layout, loadSprites, quiz);
        break;

    case GameState::INTRO:
        if (event.type == Event::MouseButtonPressed) {
            audio.playClickButtonSound();
            if (layout.nextButtonClicked(window)) {
                currentState = GameState::STAGE_ONE_MENU;
            }
        }
        loadGameAssets(currentState, loadSprites);
        renderGameScene(window, currentState, layout, loadSprites, quiz);
        break;

    case GameState::STAGE_ONE_MENU:
        audio.playClickButtonSound();
        if (event.type == Event::MouseButtonPressed) {
            Vector2i mousePos = Mouse::getPosition(window);
            currentState = layout.loadButtonClicked(mousePos);

            quiz.loadQuiz();

        }
        loadGameAssets(currentState, loadSprites);
        renderGameScene(window, currentState, layout, loadSprites, quiz);
        break;

    case GameState::SEAWORLD:
    case GameState::UNDERWORLD:
    case GameState::COUNTRY_SIDE:
        loadGameAssets(currentState, loadSprites);

        // Handle quiz event
        if (event.type == Event::MouseButtonPressed)
        {
            quiz.handleEvent();
        }

        renderGameScene(window, currentState, layout, loadSprites, quiz);
        break;

    default:
        break;
    }
}
