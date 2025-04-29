#include "JsonManager.h"
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
    
    case GameState::CRETE:
        loadSprites.loadGameScreen("Backgrounds/DaedalusBackground.png", "Characters/Daedalus.png", "Acessories/Scroll.png");
        break;

    case GameState::NYX5:
        loadSprites.loadGameScreen("Backgrounds/NyxBackground.png", "Characters/Nyx.png", "Acessories/Scroll.png");
        break;

    case GameState::CYPRUS:
        loadSprites.loadGameScreen("Backgrounds/AphroditeBackground.png", "Characters/Aphrodite.png", "Acessories/Scroll.png");
        break;

    case GameState::LETHE:
        loadSprites.loadGameScreen("Backgrounds/HypnosBackground.png", "Characters/Hypnos.png", "Acessories/Scroll.png");
        break;

    case GameState::NYX6:
        loadSprites.loadGameScreen("Backgrounds/NyxBackground.png", "Characters/Nyx.png", "Acessories/Scroll.png");
        break;

    case GameState::OLYMPUS:
        loadSprites.loadGameScreen("Backgrounds/ZeusBackground.png", "Characters/Zeus.png", "Acessories/Scroll.png");
        break;

    case GameState::ARGOS:
        loadSprites.loadGameScreen("Backgrounds/HeraBackground.png", "Characters/Hera.png", "Acessories/Scroll.png");
        break;

    case GameState::NYX7:
        loadSprites.loadGameScreen("Backgrounds/NyxBackground.png", "Characters/Nyx.png", "Acessories/Scroll.png");
        break;

    case GameState::MOUNT_CYLLENE:
        loadSprites.loadGameScreen("Backgrounds/HermesBackground.png", "Characters/Hermes.png", "Acessories/Scroll.png");
        break;

    case GameState::NYX8:
        loadSprites.loadGameScreen("Backgrounds/NyxBackground.png", "Characters/Nyx.png", "Acessories/Scroll.png");
        break;


    default:
        break;
    }
}

void renderGameScene(RenderWindow& window, GameState currentState, ButtonLayout& layout, LoadSprites& loadSprites, QuizUI& quiz, DialogManager& dialog, Audio& audio, ProgressBar& progressBar)
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
		progressBar.draw();
        quiz.render();

        break;

    case GameState::UNDERWORLD:
        window.clear();
        window.draw(loadSprites.gameBackgroundSprite);
        window.draw(loadSprites.godSprite);
        window.draw(loadSprites.mainCharacterSprite);
        window.draw(loadSprites.gameScrollSprite);
        progressBar.draw();
        quiz.render();

        break;

    case GameState::COUNTRY_SIDE:
        window.clear();
        window.draw(loadSprites.gameBackgroundSprite);
        window.draw(loadSprites.godSprite);
        window.draw(loadSprites.mainCharacterSprite);
        window.draw(loadSprites.gameScrollSprite);
        progressBar.draw();
        quiz.render();

        break;

    case GameState::NYX2:
        window.clear();
        window.draw(loadSprites.gameBackgroundSprite);
        window.draw(loadSprites.godSprite);
        window.draw(loadSprites.mainCharacterSprite);
        window.draw(loadSprites.gameScrollSprite);
        layout.loadNextButton();
        progressBar.draw();
        break;


    case GameState::ATHENS:
        window.clear();
        window.draw(loadSprites.gameBackgroundSprite);
        window.draw(loadSprites.godSprite);
        window.draw(loadSprites.mainCharacterSprite);
        window.draw(loadSprites.gameScrollSprite);
        progressBar.draw();
        quiz.render();

        break;

    case GameState::RHAMNOUS:
        window.clear();
        window.draw(loadSprites.gameBackgroundSprite);
        window.draw(loadSprites.godSprite);
        window.draw(loadSprites.mainCharacterSprite);
        window.draw(loadSprites.gameScrollSprite);
        progressBar.draw();
        quiz.render();
        
        break;

    case GameState::NYX3:
        window.clear();
        window.draw(loadSprites.gameBackgroundSprite);
        window.draw(loadSprites.godSprite);
        window.draw(loadSprites.mainCharacterSprite);
        window.draw(loadSprites.gameScrollSprite);
        layout.loadNextButton();
        progressBar.draw();
        break;

    case GameState::DELPHI:
        window.clear();
        window.draw(loadSprites.gameBackgroundSprite);
        window.draw(loadSprites.godSprite);
        window.draw(loadSprites.mainCharacterSprite);
        window.draw(loadSprites.gameScrollSprite);
        progressBar.draw();
        quiz.render();

        break;

    case GameState::THRACE:
        window.clear();
        window.draw(loadSprites.gameBackgroundSprite);
        window.draw(loadSprites.godSprite);
        window.draw(loadSprites.mainCharacterSprite);
        window.draw(loadSprites.gameScrollSprite);
        progressBar.draw();
        quiz.render();

        break;

    case GameState::NYX4:
        window.clear();
        window.draw(loadSprites.gameBackgroundSprite);
        window.draw(loadSprites.godSprite);
        window.draw(loadSprites.mainCharacterSprite);
        window.draw(loadSprites.gameScrollSprite);
        layout.loadNextButton();
		progressBar.draw();
        break;

    case GameState::CRETE:
        window.clear();
        window.draw(loadSprites.gameBackgroundSprite);
        window.draw(loadSprites.godSprite);
        window.draw(loadSprites.mainCharacterSprite);
        window.draw(loadSprites.gameScrollSprite);
        progressBar.draw();
        quiz.render();

        break;

    case GameState::NYX5:
        window.clear();
        window.draw(loadSprites.gameBackgroundSprite);
        window.draw(loadSprites.godSprite);
        window.draw(loadSprites.mainCharacterSprite);
        window.draw(loadSprites.gameScrollSprite);
        layout.loadNextButton();
        progressBar.draw();
        break;

    case GameState::CYPRUS:
        window.clear();
        window.draw(loadSprites.gameBackgroundSprite);
        window.draw(loadSprites.godSprite);
        window.draw(loadSprites.mainCharacterSprite);
        window.draw(loadSprites.gameScrollSprite);
        progressBar.draw();
        quiz.render();

        break;


    case GameState::LETHE:
        window.clear();
        window.draw(loadSprites.gameBackgroundSprite);
        window.draw(loadSprites.godSprite);
        window.draw(loadSprites.mainCharacterSprite);
        window.draw(loadSprites.gameScrollSprite);
        progressBar.draw();
        quiz.render();

        break;

    case GameState::NYX6:
        window.clear();
        window.draw(loadSprites.gameBackgroundSprite);
        window.draw(loadSprites.godSprite);
        window.draw(loadSprites.mainCharacterSprite);
        window.draw(loadSprites.gameScrollSprite);
        layout.loadNextButton();
        progressBar.draw();
        break;

    case GameState::OLYMPUS:
        window.clear();
        window.draw(loadSprites.gameBackgroundSprite);
        window.draw(loadSprites.godSprite);
        window.draw(loadSprites.mainCharacterSprite);
        window.draw(loadSprites.gameScrollSprite);
        progressBar.draw();
        quiz.render();

        break;

    case GameState::ARGOS:
        window.clear();
        window.draw(loadSprites.gameBackgroundSprite);
        window.draw(loadSprites.godSprite);
        window.draw(loadSprites.mainCharacterSprite);
        window.draw(loadSprites.gameScrollSprite);
        progressBar.draw();
        quiz.render();

        break;

    case GameState::NYX7:
        window.clear();
        window.draw(loadSprites.gameBackgroundSprite);
        window.draw(loadSprites.godSprite);
        window.draw(loadSprites.mainCharacterSprite);
        window.draw(loadSprites.gameScrollSprite);
        layout.loadNextButton();
        progressBar.draw();
        break;
    
    case GameState::MOUNT_CYLLENE:
        window.clear();
        window.draw(loadSprites.gameBackgroundSprite);
        window.draw(loadSprites.godSprite);
        window.draw(loadSprites.mainCharacterSprite);
        window.draw(loadSprites.gameScrollSprite);
        progressBar.draw();
        quiz.render();

        break;
    
    case GameState::NYX8:
        window.clear();
        window.draw(loadSprites.gameBackgroundSprite);
        window.draw(loadSprites.godSprite);
        window.draw(loadSprites.mainCharacterSprite);
        window.draw(loadSprites.gameScrollSprite);
        layout.loadNextButton();
        progressBar.draw();
        break;

	/*case GameState::NYXGREETING_SCENE:
        
        break;*/

    default:
        break;
    }

    window.display();  // Update the window with the newly drawn content
}

void handleGameLogic(RenderWindow& window, GameState& currentState, ButtonLayout& layout, LoadSprites& loadSprites, Event& event, Audio& audio, QuizUI& quiz, DialogManager& dialog, ProgressBar& progressBar, JsonManager& jm)
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
        renderGameScene(window, currentState, layout, loadSprites, quiz, dialog, audio, progressBar);
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
                currentState = GameState::NYXGREETING_SCENE;
            }
        }

        loadGameAssets(currentState, loadSprites, dialog);
        renderGameScene(window, currentState, layout, loadSprites, quiz, dialog, audio, progressBar);
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
        cout << "nyx1 ran" << endl;
        loadGameAssets(currentState, loadSprites, dialog);
        renderGameScene(window, currentState, layout, loadSprites, quiz, dialog, audio, progressBar);
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

        renderGameScene(window, currentState, layout, loadSprites, quiz, dialog, audio, progressBar);

        break;

    case GameState::SEAWORLD:
    case GameState::UNDERWORLD:
    case GameState::COUNTRY_SIDE:
        loadGameAssets(currentState, loadSprites, dialog);

        // Handle quiz events
        if (event.type == Event::MouseButtonPressed) {
            if (!quiz.isQuizComplete()) {
                progressBar.update();
                quiz.handleEvent(); // Normal quiz handling
            }
            else if (quiz.isScoreShown() && layout.nextButtonClicked(window)) {
                // Only proceed if quiz is complete AND Next is clicked
                //progressBar.update();
                audio.playClickButtonSound();
                //currentState = GameState::NYX2;
                currentState = GameState::TYPING_GAME;  //TESTING STATES
            }
        }

        renderGameScene(window, currentState, layout, loadSprites, quiz, dialog, audio, progressBar);
        break;

    case GameState::NYX2:
        if (event.type == Event::MouseButtonPressed) {
            if (layout.nextButtonClicked(window)) {
                audio.playClickButtonSound();

                int currentScore = quiz.getScore();
                quiz.resetQuiz();  // Reset the quiz state before moving to stage

                if (currentScore < 4)
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
        renderGameScene(window, currentState, layout, loadSprites, quiz, dialog, audio, progressBar);
        break;

    case GameState::ATHENS:
    case GameState::DELPHI:
        loadGameAssets(currentState, loadSprites, dialog);

        // Handle quiz events
        if (event.type == Event::MouseButtonPressed) {
            if (!quiz.isQuizComplete()) {
                progressBar.update();
                quiz.handleEvent(); // Normal quiz handling
            }
            else if (quiz.isScoreShown() && layout.nextButtonClicked(window)) {
                // Only proceed if quiz is complete AND Next is clicked
                progressBar.update();
                audio.playClickButtonSound();
                currentState = GameState::NYX3;
            }
        }

        renderGameScene(window, currentState, layout, loadSprites, quiz, dialog, audio, progressBar);
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
        progressBar.draw();
        loadGameAssets(currentState, loadSprites, dialog);
        renderGameScene(window, currentState, layout, loadSprites, quiz, dialog, audio, progressBar);
        break;


    case GameState::THRACE:
    case GameState::RHAMNOUS:
        loadGameAssets(currentState, loadSprites, dialog);

        // Handle quiz events
        if (event.type == Event::MouseButtonPressed) {
            if (!quiz.isQuizComplete()) {
                progressBar.update();
                quiz.handleEvent(); // Normal quiz handling
            }
            else if (quiz.isScoreShown() && layout.nextButtonClicked(window)) {
                // Only proceed if quiz is complete AND Next is clicked
                progressBar.draw();
                audio.playClickButtonSound();
                currentState = GameState::NYX4;
            }
        }

        renderGameScene(window, currentState, layout, loadSprites, quiz, dialog, audio, progressBar);
        break;


    case GameState::NYX4:
        if (event.type == Event::MouseButtonPressed) {
            if (layout.nextButtonClicked(window)) {
                audio.playClickButtonSound();
                quiz.resetQuiz();  // Reset the quiz state before moving to stage
                currentState = GameState::CRETE;
                quiz.initQuiz(currentState);
            }
        }
        progressBar.draw();
        loadGameAssets(currentState, loadSprites, dialog);
        renderGameScene(window, currentState, layout, loadSprites, quiz, dialog, audio, progressBar);
        break;

    case GameState::CRETE:
        loadGameAssets(currentState, loadSprites, dialog);

        // Handle quiz events
        if (event.type == Event::MouseButtonPressed) {
            if (!quiz.isQuizComplete()) {
                progressBar.update();
                quiz.handleEvent(); // Normal quiz handling
            }
            else if (quiz.isScoreShown() && layout.nextButtonClicked(window)) {
                // Only proceed if quiz is complete AND Next is clicked
                audio.playClickButtonSound();
                currentState = GameState::NYX5;
            }
        }
        renderGameScene(window, currentState, layout, loadSprites, quiz, dialog, audio, progressBar);
        break;


    case GameState::NYX5:
        if (event.type == Event::MouseButtonPressed) {
            if (layout.nextButtonClicked(window)) {
                audio.playClickButtonSound();
                int currentScore = quiz.getScore();
                quiz.resetQuiz();  // Reset the quiz state before moving to stage

                if (currentScore < 6)
                {
                    currentState = GameState::LETHE;
                    quiz.initQuiz(currentState);
                }
                else
                {
                    currentState = GameState::CYPRUS;
                    quiz.initQuiz(currentState);
                }
            }
        }
        loadGameAssets(currentState, loadSprites, dialog);
        renderGameScene(window, currentState, layout, loadSprites, quiz, dialog, audio, progressBar);
        break;

    case GameState::CYPRUS:
    case GameState::LETHE:
        loadGameAssets(currentState, loadSprites, dialog);

        // Handle quiz events
        if (event.type == Event::MouseButtonPressed) {
            if (!quiz.isQuizComplete()) {
                progressBar.update();
                quiz.handleEvent(); // Normal quiz handling
            }
            else if (quiz.isScoreShown() && layout.nextButtonClicked(window)) {
                // Only proceed if quiz is complete AND Next is clicked
                audio.playClickButtonSound();
                currentState = GameState::NYX6;
            }
        }
        renderGameScene(window, currentState, layout, loadSprites, quiz, dialog, audio, progressBar);
        break;


    case GameState::NYX6:
        if (event.type == Event::MouseButtonPressed) {
            if (layout.nextButtonClicked(window)) {
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
        loadGameAssets(currentState, loadSprites, dialog);
        renderGameScene(window, currentState, layout, loadSprites, quiz, dialog, audio, progressBar);
        break;

    case GameState::ARGOS:
    case GameState::OLYMPUS:
        loadGameAssets(currentState, loadSprites, dialog);

        // Handle quiz events
        if (event.type == Event::MouseButtonPressed) {
            if (!quiz.isQuizComplete()) {
                progressBar.update();
                quiz.handleEvent(); // Normal quiz handling
            }
            else if (quiz.isScoreShown() && layout.nextButtonClicked(window)) {
                // Only proceed if quiz is complete AND Next is clicked
                audio.playClickButtonSound();
                currentState = GameState::NYX7;
            }
        }

        renderGameScene(window, currentState, layout, loadSprites, quiz, dialog, audio, progressBar);
        break;

    case GameState::NYX7:
        if (event.type == Event::MouseButtonPressed) {
            if (layout.nextButtonClicked(window)) {
                audio.playClickButtonSound();
                quiz.resetQuiz();  // Reset the quiz state before moving to stage
                currentState = GameState::MOUNT_CYLLENE;
                quiz.initQuiz(currentState);

            }
        }
        loadGameAssets(currentState, loadSprites, dialog);
        renderGameScene(window, currentState, layout, loadSprites, quiz, dialog, audio, progressBar);
        break;


    case GameState::MOUNT_CYLLENE:
        loadGameAssets(currentState, loadSprites, dialog);

        // Handle quiz events
        if (event.type == Event::MouseButtonPressed) {
            if (!quiz.isQuizComplete()) {
                progressBar.update();
                quiz.handleEvent(); // Normal quiz handling
            }
            else if (quiz.isScoreShown() && layout.nextButtonClicked(window)) {
                // Only proceed if quiz is complete AND Next is clicked
                audio.playClickButtonSound();
                currentState = GameState::NYX8;
            }
        }

        renderGameScene(window, currentState, layout, loadSprites, quiz, dialog, audio, progressBar);
        break;

    case GameState::NYX8:
        if (event.type == Event::MouseButtonPressed) {
            if (layout.nextButtonClicked(window)) {
                audio.playClickButtonSound();
                quiz.resetQuiz();  // Reset the quiz state before moving to stage
                currentState = GameState::MOUNT_CYLLENE;
                quiz.initQuiz(currentState);
            }
        }
        loadGameAssets(currentState, loadSprites, dialog);
        renderGameScene(window, currentState, layout, loadSprites, quiz, dialog, audio, progressBar);
        break;


    case GameState::BOSS_GAME:

        break;

	case GameState::TYPING_GAME:
        window.setVisible(false);


    case GameState::NYXGREETING_SCENE:
        updateGameState(window, currentState, layout, loadSprites, event, audio, quiz, dialog, progressBar, jm, "Jsons/Intro/Introduction.json", GameState::NYX1);
        break;


    default:
        break;
    }


}

//func
void updateGameState(RenderWindow& window, GameState& currentState, ButtonLayout& layout, LoadSprites& loadSprites, Event& event, Audio& audio, QuizUI& quiz, DialogManager& dialog, ProgressBar& progressBar, JsonManager& jm, const string& jsonPath, GameState nextState) {

        // --- 1. JSON Initialization ---
        if (!jm.IsLoaded() || jm.GetCurrentPath() != jsonPath) {
            cout << "updateGameState: Loading JSON '" << jsonPath << "' (Current: '" << jm.GetCurrentPath() << "')." << endl;
            jm.ClearAll();
            jm.LoadJson(jsonPath);

            if (jm.IsLoaded()) {
                jm.LoadData();
                dialog.SetDialogueText(jm.line);
            }
            else {
                cerr << "updateGameState: ERROR - Failed to load JSON. Transitioning to ERROR_STATE." << endl;
                currentState = GameState::MENU;
                return;
            }
        }

        if (!jm.IsLoaded()) {
            return; // Early exit if JSON still not loaded.
        }

        // --- 2. Handle Events ---
        bool stateChanged = false;

        // Advance dialogue on 'F' key
        if (event.type == Event::KeyReleased && event.key.code == Keyboard::F) {
            if (jm.HasNext() && dialog.isDialogFinished()) {
                jm.Clear();
                jm.LoadData();
                dialog.SetDialogueText(jm.line);
            }
            else {
                cout << "updateGameState: Cannot advance. HasNext=" << boolalpha << jm.HasNext()
                    << ", DialogFinished=" << boolalpha << dialog.isDialogFinished() << endl;
            }
        }

        // Transition to next state on "Next" button click
        bool canTransition = !jm.HasNext() && dialog.isDialogFinished();

        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left && canTransition && layout.nextButtonClicked(window)) {
                cout << "updateGameState: Next button clicked. Transitioning state." << endl;
                audio.playClickButtonSound();
                jm.ClearAll();
                currentState = nextState;
                stateChanged = true;
                return;
            
        }

        // --- 3. Drawing ---
        if (!stateChanged) {
            cout << "drawn" << endl;
            loadSprites.loadDialogueScreen(jm.backgroundSprite, jm.rightSprite, jm.leftSprite);
            audio.playSound(jm.audioPath, jm.audioLoop);

            window.clear(Color::Black);
            window.draw(loadSprites.gameBackgroundSprite);
            window.draw(loadSprites.godSprite);
            window.draw(loadSprites.mainCharacterSprite);
            window.draw(loadSprites.gameScrollSprite);
            dialog.draw(window);

            if (canTransition) {
                layout.loadNextButton();
            }

            window.display();
        }
    

}