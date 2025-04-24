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

    case GameState::RHAMNOUS:
        loadSprites.loadGameScreen("Backgrounds/NemesisBackground.png", "Characters/Nemesis.png", "Acessories/Scroll.png");
        break;

    case GameState::NYX3:
        loadSprites.loadGameScreen("Backgrounds/NyxBackground.png", "Characters/Nyx.png", "Acessories/Scroll.png");
        break;

    case GameState::DELPHI:
        loadSprites.loadGameScreen("Backgrounds/ApolloBackground.png", "Characters/Apollo.png", "Acessories/Scroll.png");
        break;

    case GameState::THRACE:
        loadSprites.loadGameScreen("Backgrounds/AresBackground.png", "Characters/Ares.png", "Acessories/Scroll.png");
        break;

    case GameState::NYX4:
        loadSprites.loadGameScreen("Backgrounds/NyxBackground.png", "Characters/Nyx.png", "Acessories/Scroll.png");
        break;
    
    case GameState::CYPRUS:
        loadSprites.loadGameScreen("Backgrounds/AphroditeBackground.png", "Characters/AphroditePlaceHolder.png", "Acessories/Scroll.png"); 
        break;
    
    case GameState::OLYMPUS:
        loadSprites.loadGameScreen("Backgrounds/ZeusBackground.png", "Characters/Zeus.png", "Acessories/Scroll.png");    
        break;
    case GameState:: LETHE: 
        loadSprites.loadGameScreen("Backgrounds/HypnosBackground.png", "Characters/Hypnos.png", "Acessories/Scroll.png");
        break;
    case GameState::MOUNT_CYLLENE:
        loadSprites.loadGameScreen("Backgrounds/HermesBackground.jpg", "Characters/Hermes.png", "Acessories/Scroll.png");
        break;
    case GameState::ARGOS:
        loadSprites.loadGameScreen("Backgrounds/HeraBackground.png", "Characters/Hera.png", "Acessories/Scroll.png");
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

    case GameState::RHAMNOUS:
        window.clear();
        window.draw(loadSprites.gameBackgroundSprite);
        window.draw(loadSprites.godSprite);
        window.draw(loadSprites.mainCharacterSprite);
        window.draw(loadSprites.gameScrollSprite);

        quiz.render();
        
        break;

    case GameState::NYX3:
        window.clear();
        window.draw(loadSprites.gameBackgroundSprite);
        window.draw(loadSprites.godSprite);
        window.draw(loadSprites.mainCharacterSprite);
        window.draw(loadSprites.gameScrollSprite);
        layout.loadNextButton();

        break;

    case GameState::DELPHI:
        window.clear();
        window.draw(loadSprites.gameBackgroundSprite);
        window.draw(loadSprites.godSprite);
        window.draw(loadSprites.mainCharacterSprite);
        window.draw(loadSprites.gameScrollSprite);

        quiz.render();

        break;

    case GameState::THRACE:
        window.clear();
        window.draw(loadSprites.gameBackgroundSprite);
        window.draw(loadSprites.godSprite);
        window.draw(loadSprites.mainCharacterSprite);
        window.draw(loadSprites.gameScrollSprite);

        quiz.render();

        break;

    case GameState::NYX4:
        window.clear();
        window.draw(loadSprites.gameBackgroundSprite);
        window.draw(loadSprites.godSprite);
        window.draw(loadSprites.mainCharacterSprite);
        window.draw(loadSprites.gameScrollSprite);
        layout.loadNextButton();

        break;
    
    case GameState::CYPRUS:
        window.clear();
        window.draw(loadSprites.gameBackgroundSprite);
        window.draw(loadSprites.godSprite);
        window.draw(loadSprites.mainCharacterSprite);
        window.draw(loadSprites.gameScrollSprite);

       quiz.render();

        break;

    case GameState::OLYMPUS:
        window.clear();
        window.draw(loadSprites.gameBackgroundSprite);
        window.draw(loadSprites.godSprite);
        window.draw(loadSprites.mainCharacterSprite);
        window.draw(loadSprites.gameScrollSprite);

       quiz.render();

        break;
    case GameState::LETHE:
        window.clear();
        window.draw(loadSprites.gameBackgroundSprite);
        window.draw(loadSprites.godSprite);
        window.draw(loadSprites.mainCharacterSprite);
        window.draw(loadSprites.gameScrollSprite);

        quiz.render();

        break;
    case GameState::MOUNT_CYLLENE:
        window.clear();
        window.draw(loadSprites.gameBackgroundSprite);
        window.draw(loadSprites.godSprite);
        window.draw(loadSprites.mainCharacterSprite);
        window.draw(loadSprites.gameScrollSprite);

        quiz.render();

        break;
    case GameState::ARGOS:
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
           // audio.playIntroductionSound();
            isDialogLoaded = true;  // Mark dialog as loaded
        }

        
       
        if (dialog.hasMoreLines()) {
            dialog.introNextLine();
        }
        else if (event.type == Event::MouseButtonPressed && !audio.isIntroductionSoundPlaying()) {
            if (layout.nextButtonClicked(window)) {
                dialog.clearText();
                isDialogLoaded = false;
                audio.playClickButtonSound();
                currentState = GameState::CYPRUS;
                quiz.initQuiz(GameState::CYPRUS);///////////////////////////////////////////////////////////////FOR TESTING IF CODE WORKS DELETE LATER
            }
        }
        
        loadGameAssets(currentState, loadSprites, dialog);
        renderGameScene(window, currentState, layout, loadSprites, quiz, dialog, audio);
        break;

    case GameState::NYX1:
        if (!isDialogLoaded) {
            dialog.reset();  // Clear old dialog first
            if (dialog.loadDialog("nyx1_dialog.json", "nyx_intro")) {
                isDialogLoaded = true;
            }
        }
        if (event.type == Event::KeyReleased && event.key.code == Keyboard::F) {
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
                                
                if(currentScore < 4)
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
                currentState = GameState::NYX3;
            }
        }

        renderGameScene(window, currentState, layout, loadSprites, quiz, dialog, audio);
        break;

    case GameState::NYX3:
        if (event.type == Event::MouseButtonPressed) {
            if (layout.nextButtonClicked(window)) {
                audio.playClickButtonSound();
                int currentScore = quiz.getScore();
                quiz.resetQuiz();  // Reset the quiz state before moving to stage

                if (currentScore < 5)
                {
                    currentState = GameState::THRACE;
                    quiz.initQuiz(currentState);
                }
                else
                {
                    currentState = GameState::RHAMNOUS;
                    quiz.initQuiz(currentState);
                }
            }
        }
        loadGameAssets(currentState, loadSprites, dialog);
        renderGameScene(window, currentState, layout, loadSprites, quiz, dialog, audio);
        break;

    
    case GameState::THRACE:
    case GameState::RHAMNOUS:
        loadGameAssets(currentState, loadSprites, dialog);

        // Handle quiz events
        if (event.type == Event::MouseButtonPressed) {
            if (!quiz.isQuizComplete()) {
                quiz.handleEvent(); // Normal quiz handling
            }
            else if (quiz.isScoreShown() && layout.nextButtonClicked(window)) {
                // Only proceed if quiz is complete AND Next is clicked
                audio.playClickButtonSound();
                currentState = GameState::NYX4;
            }
        }

        renderGameScene(window, currentState, layout, loadSprites, quiz, dialog, audio);
        break;


    case GameState::NYX4:
        if (event.type == Event::MouseButtonPressed) {
            if (layout.nextButtonClicked(window)) {
                audio.playClickButtonSound();
                currentState = GameState::CRETE;
                quiz.resetQuiz();  // Reset the quiz state before moving to stage
            }
        }
        loadGameAssets(currentState, loadSprites, dialog);
        renderGameScene(window, currentState, layout, loadSprites, quiz, dialog, audio);
        break;

    case GameState::CYPRUS:
    case GameState::LETHE:
        loadGameAssets(currentState, loadSprites, dialog);
        
        // Handle quiz events
        if (event.type == Event::MouseButtonPressed) {
            if (!quiz.isQuizComplete()) {
                quiz.handleEvent(); // Normal quiz handling
            }
            else if (quiz.isScoreShown() && layout.nextButtonClicked(window)) {
                // Only proceed if quiz is complete AND Next is clicked
                audio.playClickButtonSound();

                int currentScore = quiz.getScore();
                quiz.resetQuiz();  // Reset the quiz state before moving to stage
                if (currentScore < 6)
                {
                    currentState = GameState::ARGOS;
                    quiz.initQuiz(currentState);
                }
                else
                {
                    currentState = GameState::OLYMPUS;
                    quiz.initQuiz(currentState);
                }
            }
        }

        renderGameScene(window, currentState, layout, loadSprites, quiz, dialog, audio);
        break;
    
    case GameState::ARGOS:
    case GameState::OLYMPUS:
        loadGameAssets(currentState, loadSprites, dialog);

        // Handle quiz events
        if (event.type == Event::MouseButtonPressed) {
            if (!quiz.isQuizComplete()) {
                quiz.handleEvent(); // Normal quiz handling
            }
            else if (quiz.isScoreShown() && layout.nextButtonClicked(window)) {
                // Only proceed if quiz is complete AND Next is clicked
                audio.playClickButtonSound();
                currentState = GameState::MOUNT_CYLLENE;
                quiz.resetQuiz();
                quiz.initQuiz(GameState::MOUNT_CYLLENE);
            }
        }

        renderGameScene(window, currentState, layout, loadSprites, quiz, dialog, audio);
        break;

    case GameState::MOUNT_CYLLENE:
        loadGameAssets(currentState, loadSprites, dialog);

        // Handle quiz events
        if (event.type == Event::MouseButtonPressed) {
            if (!quiz.isQuizComplete()) {
                quiz.handleEvent(); // Normal quiz handling
            }
            else if (quiz.isScoreShown() && layout.nextButtonClicked(window)) {
                // Only proceed if quiz is complete AND Next is clicked
                audio.playClickButtonSound();
                currentState = GameState::NYX1;
            }
        }

        renderGameScene(window, currentState, layout, loadSprites, quiz, dialog, audio);
        break;

    default:
        break;
    }
}
