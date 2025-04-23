#include "GameLogic.h"
#include "QuizUI.h"
#include "QuizManager.h"
#include <SFML/Window.hpp>
#include "Audio.h"

using namespace sf;

void loadGameAssets(GameState currentState, LoadSprites& loadSprites, DialogManager& dialog)
{
    switch (currentState) {
    case GameState::MENU:
        loadSprites.loadMenuScreen("Backgrounds/MenuBackground.png");
        break;

    case GameState::INTRO:
        loadSprites.loadInstructionScreen("Backgrounds/InstructionBackground.jpg", "Acessories/MenuScroll.png");
        break;


    case GameState::NYX1:
        loadSprites.loadGameScreen("Backgrounds/NyxBackground.png", "Characters/Nyx.png", "Acessories/Scroll.png");
        break;

    case GameState::STAGE_ONE_MENU:
        loadSprites.loadMenuScreen("Backgrounds/MenuBackground00.png");
        break;

    case GameState::SEAWORLD:
        loadSprites.loadGameScreen("Backgrounds/PoseidonBackground.jpg", "Characters/Poseidon.png", "Acessories/Scroll.png");
        break;

    case GameState::UNDERWORLD:
        loadSprites.loadGameScreen("Backgrounds/HadesBackground.jpg", "Characters/Hades.png", "Acessories/Scroll.png");
        break;

    case GameState::COUNTRY_SIDE:
        loadSprites.loadGameScreen("Backgrounds/DionysusBackground.jpg", "Characters/Dionysus.png", "Acessories/Scroll.png");
        break;

    case GameState::NYX2:
        loadSprites.loadGameScreen("Backgrounds/NyxBackground.png", "Characters/Nyx.png", "Acessories/Scroll.png");
        break;

    case GameState::STAGE_TWO_MENU:
        loadSprites.loadMenuScreen("Backgrounds/MenuBackground00.png");
        break;

    case GameState::ATHENS:
        loadSprites.loadGameScreen("Backgrounds/AthenaBackground.png", "Characters/Athena.png", "Acessories/Scroll.png");
        break;

    case GameState::DELPHI:
        loadSprites.loadGameScreen("Backgrounds/ApolloBackground.png", "Characters/Apollo.png", "Acessories/Scroll.png");
        break;

    default:
        break;
    }
}

void renderGameScene(RenderWindow& window, GameState currentState, ButtonLayout& layout, LoadSprites& loadSprites, QuizUI& quiz, DialogManager& dialog, Audio& audio)
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
        if (!audio.isIntroductionSoundPlaying()) {
            layout.loadNextButton();
        }
        
        dialog.draw(window);
        break;


    case GameState::NYX1:
        window.clear();
        window.draw(loadSprites.gameBackgroundSprite);
        window.draw(loadSprites.godSprite);
        window.draw(loadSprites.mainCharacterSprite);
        window.draw(loadSprites.gameScrollSprite);
        dialog.draw(window);
        // Only show Next button if dialog is complete
        if (dialog.isDialogFinished()) {
            layout.loadNextButton();
        }

        break;

    case GameState::STAGE_ONE_MENU:
        window.clear();
        window.draw(loadSprites.menuBackgroundSprite);
        layout.loadStageOneButtons();
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
        
        quiz.render();

        break;

    case GameState::COUNTRY_SIDE:
        window.clear();
        window.draw(loadSprites.gameBackgroundSprite);
        window.draw(loadSprites.godSprite);
        window.draw(loadSprites.mainCharacterSprite);
        window.draw(loadSprites.gameScrollSprite);
        
        quiz.render();

        break;

    case GameState::NYX2:
        window.clear();
        window.draw(loadSprites.gameBackgroundSprite);
        window.draw(loadSprites.godSprite);
        window.draw(loadSprites.mainCharacterSprite);
        window.draw(loadSprites.gameScrollSprite);
        layout.loadNextButton();

        break;

    case GameState::STAGE_TWO_MENU:
        window.clear();
        window.draw(loadSprites.menuBackgroundSprite);
        layout.loadStageTwoButtons();
        break;


    case GameState::ATHENS:
        window.clear();
        window.draw(loadSprites.gameBackgroundSprite);
        window.draw(loadSprites.godSprite);
        window.draw(loadSprites.mainCharacterSprite);
        window.draw(loadSprites.gameScrollSprite);

        quiz.render();

        break;

    case GameState::DELPHI:
        window.clear();
        window.draw(loadSprites.gameBackgroundSprite);
        window.draw(loadSprites.godSprite);
        window.draw(loadSprites.mainCharacterSprite);
        window.draw(loadSprites.gameScrollSprite);

        quiz.render();

        break;

    default:
        break;
    }

    window.display();  // Update the window with the newly drawn content
}

void handleGameLogic(RenderWindow& window, GameState& currentState, ButtonLayout& layout, LoadSprites& loadSprites, Event& event, Audio& audio, QuizUI& quiz, DialogManager& dialog)
{   
    static bool isDialogLoaded = false;  // static to persist across frames
    switch (currentState) {
    case GameState::MENU:
        if (event.type == Event::MouseButtonPressed) {
            if (layout.playButtonClicked(window)) {
                audio.playClickButtonSound();
                currentState = GameState::INTRO; // Change state when Play button is clicked
            }
        }
        loadGameAssets(currentState, loadSprites, dialog);
        renderGameScene(window, currentState, layout, loadSprites, quiz, dialog, audio);
        break;

    case GameState::INTRO:
        if (!isDialogLoaded) {
            dialog.loadIntroDialog("nyx1_dialog.json", "instruction_screen");
            audio.playIntroductionSound();
            isDialogLoaded = true;  // Mark dialog as loaded
        }

        
       
        if (dialog.hasMoreLines()) {
            dialog.nextLine();
        }
        else if (event.type == Event::MouseButtonPressed && !audio.isIntroductionSoundPlaying()) {
            if (layout.nextButtonClicked(window)) {
                dialog.clearText();
                audio.playClickButtonSound();
                currentState = GameState::NYX1;
            }
        }
        
        loadGameAssets(currentState, loadSprites, dialog);
        renderGameScene(window, currentState, layout, loadSprites, quiz, dialog, audio);
        break;

    case GameState::NYX1:
        isDialogLoaded = false;
        dialog.reset();
        if (!isDialogLoaded) {
            dialog.loadDialog("nyx1_dialog.json", "nyx_intro");
            isDialogLoaded = true;  // Mark dialog as loaded
        }
        if (event.type == Event::KeyPressed && event.key.code == Keyboard::F)
        {
            if (dialog.hasMoreLines()) {
                dialog.nextLine();
            }
            else if (layout.nextButtonClicked(window)) {
                audio.playClickButtonSound();
                currentState = GameState::STAGE_ONE_MENU;
            }
        }
        if (event.type == Event::MouseButtonPressed) {
            // Only allow clicking Next if dialog is complete
            if (dialog.isDialogFinished() && layout.nextButtonClicked(window)) {
                audio.playClickButtonSound();
                currentState = GameState::STAGE_ONE_MENU;
            }
        }
        loadGameAssets(currentState, loadSprites, dialog);
        renderGameScene(window, currentState, layout, loadSprites, quiz, dialog, audio);
        break;
   

    case GameState::STAGE_ONE_MENU:
        isDialogLoaded = false;
        dialog.reset();
        if (event.type == Event::MouseButtonPressed) {
            audio.playClickButtonSound();
            Vector2i mousePos = Mouse::getPosition(window);
            GameState newState = layout.loadStageOneButtonClicked(mousePos);

            if (newState == GameState::SEAWORLD ||
                newState == GameState::UNDERWORLD ||
                newState == GameState::COUNTRY_SIDE) {
                quiz.initQuiz(newState); // Initialize with the selected world
            }
            currentState = newState;
            
        }
        loadGameAssets(currentState, loadSprites, dialog);
        renderGameScene(window, currentState, layout, loadSprites, quiz, dialog, audio);
        break;

    case GameState::SEAWORLD:
    case GameState::UNDERWORLD:
    case GameState::COUNTRY_SIDE:
        loadGameAssets(currentState, loadSprites, dialog);

        // Handle quiz events
        if (event.type == Event::MouseButtonPressed) {
            if (!quiz.isQuizComplete()) {
                quiz.handleEvent(); // Normal quiz handling
            }
            else if (quiz.isScoreShown() && layout.nextButtonClicked(window)) {
                // Only proceed if quiz is complete AND Next is clicked
                audio.playClickButtonSound();
                currentState = GameState::NYX2;
            }
        }

        renderGameScene(window, currentState, layout, loadSprites, quiz, dialog, audio);
        break;

    case GameState::NYX2:
        if (event.type == Event::MouseButtonPressed) {
            if (layout.nextButtonClicked(window)) {
                audio.playClickButtonSound();

                int currentScore = quiz.getScore();
                quiz.resetQuiz();  // Reset the quiz state before moving to stage
                totalScore = 5;

                

                if(totalScore != 5)
                {
                    
                    currentState = GameState::DELPHI;
                    quiz.initQuiz(currentState);

                }
                else
                {
                    currentState = GameState::ATHENS;
                    quiz.initQuiz(currentState);
                }
                

              
            }
        }
        loadGameAssets(currentState, loadSprites, dialog);
        renderGameScene(window, currentState, layout, loadSprites, quiz, dialog, audio);
        break;


    case GameState::STAGE_TWO_MENU:
        if (event.type == Event::MouseButtonPressed) {
            audio.playClickButtonSound();
            Vector2i mousePos = Mouse::getPosition(window);
            GameState newState = layout.loadStageTwoButtonClicked(mousePos);

            if (newState == GameState::ATHENS ||
                newState == GameState::DELPHI) {
                quiz.resetQuiz();  // Ensure quiz is reset before initialization
                quiz.initQuiz(newState); // Initialize with the selected world
            }
            currentState = newState;

        }
        loadGameAssets(currentState, loadSprites, dialog);
        renderGameScene(window, currentState, layout, loadSprites, quiz, dialog, audio);
        break;

    case GameState::ATHENS:
    case GameState::DELPHI:
        loadGameAssets(currentState, loadSprites, dialog);

        // Handle quiz events
        if (event.type == Event::MouseButtonPressed) {
            if (!quiz.isQuizComplete()) {
                quiz.handleEvent(); // Normal quiz handling
            }
            else if (quiz.isScoreShown() && layout.nextButtonClicked(window)) {
                // Only proceed if quiz is complete AND Next is clicked
                audio.playClickButtonSound();
                currentState = GameState::NYX2;
            }
        }

        renderGameScene(window, currentState, layout, loadSprites, quiz, dialog, audio);
        break;

    default:
        break;
    }
}
