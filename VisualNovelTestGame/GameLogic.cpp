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


    case GameState::STAGE_ONE_MENU:
        loadSprites.loadMenuScreen("Backgrounds/MenuBackground00.png");
        break;

    case GameState::POSEIDON_CHOICE:
        loadSprites.loadGameScreen("Backgrounds/PoseidonBackground.jpg", "Characters/Poseidon.png", "Acessories/Scroll.png");
        break;

    case GameState::ATLANTIS_QUIZ:
        loadSprites.loadGameScreen("Backgrounds/HadesBackground.jpg", "Characters/Hades.png", "Acessories/Scroll.png");
        break;

    case GameState::SHRINE_QUIZ:
        loadSprites.loadGameScreen("Backgrounds/HadesBackground.jpg", "Characters/Hades.png", "Acessories/Scroll.png");
        break;

    case GameState::HADES_QUIZ:
        loadSprites.loadGameScreen("Backgrounds/HadesBackground.jpg", "Characters/Hades.png", "Acessories/Scroll.png");
        break;

    case GameState::DIONYSUS_CHOICE:
        loadSprites.loadGameScreen("Backgrounds/DionysusBackground.jpg", "Characters/Dionysus.png", "Acessories/Scroll.png");
        break;

    case GameState::KOMOS_SCENE:
        loadSprites.loadGameScreen("Backgrounds/HadesBackground.jpg", "Characters/Hades.png", "Acessories/Scroll.png");
        break;

    case GameState::FOREST_SCENE:
        loadSprites.loadGameScreen("Backgrounds/HadesBackground.jpg", "Characters/Hades.png", "Acessories/Scroll.png");
        break;


    case GameState::STAGE_TWO_MENU:
        loadSprites.loadMenuScreen("Backgrounds/MenuBackground00.png");
        break;

    case GameState::APOLLO_QUIZ:
        loadSprites.loadGameScreen("Backgrounds/ApolloBackground.png", "Characters/Apollo.png", "Acessories/Scroll.png");
        break;

    case GameState::HEPHAESTUS_QUIZ:
        loadSprites.loadGameScreen("Backgrounds/ApolloBackground.png", "Characters/Apollo.png", "Acessories/Scroll.png");
        break;

    case GameState::ATHENA_QUIZ:
        loadSprites.loadGameScreen("Backgrounds/AthenaBackground.png", "Characters/Athena.png", "Acessories/Scroll.png");
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

    case GameState::STAGE_ONE_MENU:
        window.clear();
        window.draw(loadSprites.menuBackgroundSprite);
        layout.loadStageOneButtons();


        //layout.loadStageTwoButtons();

        break;


    case GameState::POSEIDON_CHOICE:
        window.clear();
        window.draw(loadSprites.gameBackgroundSprite);
        layout.loadPoseidonChoiceButtons();

        break;

    case GameState::ATLANTIS_QUIZ:
        window.clear();
        window.draw(loadSprites.gameBackgroundSprite);
        window.draw(loadSprites.godSprite);
        window.draw(loadSprites.mainCharacterSprite);
        window.draw(loadSprites.gameScrollSprite);
        progressBar.draw();
        quiz.render();
        break;

    case GameState::SHRINE_QUIZ:
        window.clear();
        window.draw(loadSprites.gameBackgroundSprite);
        window.draw(loadSprites.godSprite);
        window.draw(loadSprites.mainCharacterSprite);
        window.draw(loadSprites.gameScrollSprite);
        progressBar.draw();
        quiz.render();
        break;

    case GameState::HADES_QUIZ:
        window.clear();
        window.draw(loadSprites.gameBackgroundSprite);
        window.draw(loadSprites.godSprite);
        window.draw(loadSprites.mainCharacterSprite);
        window.draw(loadSprites.gameScrollSprite);
        progressBar.draw();
        quiz.render();

        break;

    case GameState::DIONYSUS_CHOICE:
        window.clear();
        window.draw(loadSprites.gameBackgroundSprite);

        layout.loadDionysusChoiceButtons();

        break;

    case GameState::KOMOS_SCENE:
        window.clear();
        window.draw(loadSprites.gameBackgroundSprite);
        window.draw(loadSprites.godSprite);
        window.draw(loadSprites.mainCharacterSprite);
        window.draw(loadSprites.gameScrollSprite);
        progressBar.draw();
        quiz.render();
        break;

    case GameState::FOREST_SCENE:
        window.clear();
        window.draw(loadSprites.gameBackgroundSprite);
        window.draw(loadSprites.godSprite);
        window.draw(loadSprites.mainCharacterSprite);
        window.draw(loadSprites.gameScrollSprite);
        progressBar.draw();
        quiz.render();
        break;

    case GameState::STAGE_TWO_MENU:
        window.clear();
        window.draw(loadSprites.menuBackgroundSprite);

        layout.loadStageTwoButtons();

        break;

    case GameState::APOLLO_QUIZ:
        window.clear();
        window.draw(loadSprites.gameBackgroundSprite);
        window.draw(loadSprites.godSprite);
        window.draw(loadSprites.mainCharacterSprite);
        window.draw(loadSprites.gameScrollSprite);
        progressBar.draw();
        quiz.render();

        break;

    case GameState::HEPHAESTUS_QUIZ:
        window.clear();
        window.draw(loadSprites.gameBackgroundSprite);
        window.draw(loadSprites.godSprite);
        window.draw(loadSprites.mainCharacterSprite);
        window.draw(loadSprites.gameScrollSprite);
        progressBar.draw();
        quiz.render();
        break;


    case GameState::ATHENA_QUIZ:
        window.clear();
        window.draw(loadSprites.gameBackgroundSprite);
        window.draw(loadSprites.godSprite);
        window.draw(loadSprites.mainCharacterSprite);
        window.draw(loadSprites.gameScrollSprite);
        progressBar.draw();
        quiz.render();

        break;

    default:
        break;
    }

    window.display();  // Update the window with the newly drawn content
}

void handleGameLogic(RenderWindow& window, GameState& currentState, ButtonLayout& layout, LoadSprites& loadSprites, Event& event, Audio& audio, QuizUI& quiz, DialogManager& dialog, ProgressBar& progressBar, JsonManager& jm)
{
    static bool isDialogLoaded = false;  // static to persist across frames

    switch (currentState) {

    case GameState::POSEIDON_CHOICE:
        if (event.type == Event::MouseButtonPressed) {
            audio.playClickButtonSound();
            Vector2i mousePos = Mouse::getPosition(window);
            GameState newState = layout.loadPoseidonChoiceButtonClicked(mousePos);
            if (newState != GameState::NONE) {
                currentState = newState; // Should be ATLANTIS_SCENE or SHRINE_SCENE
            }
        }
        loadGameAssets(currentState, loadSprites, dialog);
        renderGameScene(window, currentState, layout, loadSprites, quiz, dialog, audio, progressBar);
        break;

    case GameState::DIONYSUS_CHOICE:
        if (event.type == Event::MouseButtonPressed) {
            audio.playClickButtonSound();
            Vector2i mousePos = Mouse::getPosition(window);
            GameState newState = layout.loadDionysusChoiceButtonClicked(mousePos);
            if (newState != GameState::NONE) {
                currentState = newState; // Should be ATLANTIS_SCENE or SHRINE_SCENE
            }
        }
        loadGameAssets(currentState, loadSprites, dialog);
        renderGameScene(window, currentState, layout, loadSprites, quiz, dialog, audio, progressBar);
        break;

    case GameState::MENU:
        if (event.type == Event::MouseButtonPressed) {
            if (layout.playButtonClicked(window)) {
                audio.playClickButtonSound();
                currentState = GameState::INTRO; // Change state when Play button is clicked

                //load the dialoguesprite once at the start of the gameasda
                loadSprites.loadGameScroll("Acessories/Scroll.png");
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

    case GameState::STAGE_ONE_MENU:
        if (event.type == Event::MouseButtonPressed) {
            audio.playClickButtonSound();
            Vector2i mousePos = Mouse::getPosition(window);
            GameState newState = layout.loadStageOneButtonClicked(mousePos);
            currentState = newState;


        }

        loadGameAssets(currentState, loadSprites, dialog);
        renderGameScene(window, currentState, layout, loadSprites, quiz, dialog, audio, progressBar);

        break;

    case GameState::ATLANTIS_QUIZ:
    case GameState::SHRINE_QUIZ:
        loadGameAssets(currentState, loadSprites, dialog);

        // Handle quiz events
        if (event.type == Event::MouseButtonPressed) {
            if (!quiz.isQuizComplete()) {
                quiz.handleEvent(); // Normal quiz handling
            }
            else if (quiz.isScoreShown() && layout.nextButtonClicked(window)) {
                // Only proceed if quiz is complete AND Next is clicked
                progressBar.update();
                audio.playClickButtonSound();
                int currentScore = quiz.getScore();
                if (currentScore > 5) {
                    currentState = GameState::ATLANTIS_WIN_SCENE;
                }
                else {
                    currentState = GameState::ATLANTIS_LOSE_SCENE;  //TESTING STATES
                }

            }
        }

        renderGameScene(window, currentState, layout, loadSprites, quiz, dialog, audio, progressBar);
        break;


    case GameState::HEPHAESTUS_QUIZ:
    case GameState::ATHENA_QUIZ:
    case GameState::APOLLO_QUIZ:
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

    case GameState::HADES_QUIZ:
        break;


        //---------------------------------------------------------- GAMES + BEGIN GAME ------------------------------------------------------------------------------
    case GameState::BOSS_GAME:
        window.setVisible(false);
        break;

    case GameState::TYPING_GAME:
        window.setVisible(false);
        break;
    case GameState::RHYTHM_GAME:
        window.setVisible(false);
        break;

    case GameState::FORGE_GAME:
        window.setVisible(false);
        break;
    case GameState::BUBBLE_GAME:
        window.setVisible(false);
        break;

    case GameState::WINE_GAME:
        window.setVisible(false);
        break;



        // --------------------------------------------------- INTRODUCTION -------------------------------------------------
    case GameState::NYXGREETING_SCENE:
        updateGameState(window, currentState, layout, loadSprites, event, audio, quiz, dialog, progressBar, jm, "Jsons/Intro/Introduction.json", GameState::STAGE_ONE_MENU);
        break;

    case GameState::STAGE_ONE_CHOICE:
        //Choose blue door -> GameState::POSEIDON_OPENING_SCENE;
        //Choose green door -> GameState::DIONYSUS_OPENING_SCENE;
        break;

        //------------------------------------------------- Stage 1 ------------------------------------------------------------------------

        // Poseidon's Path (Seas of Greece)
    case GameState::POSEIDON_OPENING_SCENE:
        updateGameState(window, currentState, layout, loadSprites, event, audio, quiz, dialog, progressBar, jm, "Jsons/StageOne/Poseidon/POSEIDON_ENCOUNTER_SCENE.json", GameState::POSEIDON_CHOICE);
        break;

        /*
    case GameState::POSEIDON_CHOICE:
        // Jump in the water     ->  GameState::ATLANTIS_SCENE;
        // Sail to Shrine        ->  GameState::SHRINE_SCENE;
        break;
   */
   /*
   case GameState::POSEIDON_QUIZ:
       // if (win && poseidon choice==ATLANTIS_SCENE) -> GameState::ATLANTIS_WIN_SCENE
       // if (win && poseidon choice==SHRINE_SCENE) -> GameState::SHRINE_WIN_SCENE
       // if (lose && poseidon choice==ATLANTIS_SCENE) -> GameState::ATLANTIS_LOSE_SCENE
       // if (lose && poseidon choice==SHRINE_SCENE) -> GameState::SHRINE_LOSE_SCENE
       break;
   */

    case GameState::ATLANTIS_SCENE:
        updateGameState(window, currentState, layout, loadSprites, event, audio, quiz, dialog, progressBar, jm, "Jsons/StageOne/Poseidon/ATLANTIS_SCENE.json", GameState::ATLANTIS_QUIZ);
        if (currentState == GameState::ATLANTIS_QUIZ) {
            quiz.initQuiz(currentState);
        }
        break;

    case GameState::ATLANTIS_WIN_SCENE:
        updateGameState(window, currentState, layout, loadSprites, event, audio, quiz, dialog, progressBar, jm, "Jsons/StageOne/Poseidon/ATLANTIS_WIN_SCENE.json", GameState::POSEIDON_ENCOUNTER_SCENE);
        break;

    case GameState::ATLANTIS_LOSE_SCENE:
        updateGameState(window, currentState, layout, loadSprites, event, audio, quiz, dialog, progressBar, jm, "Jsons/StageOne/Poseidon/ATLANTIS_LOSE_SCENE.json", GameState::POSEIDON_END_SCENE);
        break;

    case GameState::SHRINE_SCENE:
        updateGameState(window, currentState, layout, loadSprites, event, audio, quiz, dialog, progressBar, jm, "Jsons/StageOne/Poseidon/SHRINE_SCENE.json", GameState::SHRINE_QUIZ);
        break;

    case GameState::SHRINE_WIN_SCENE:
        updateGameState(window, currentState, layout, loadSprites, event, audio, quiz, dialog, progressBar, jm, "Jsons/StageOne/Poseidon/SHRINE_WIN_SCENE.json", GameState::POSEIDON_ENCOUNTER_SCENE);
        break;

    case GameState::SHRINE_LOSE_SCENE:
        updateGameState(window, currentState, layout, loadSprites, event, audio, quiz, dialog, progressBar, jm, "Jsons/StageOne/Poseidon/SHRINE_LOSE_SCENE.json", GameState::POSEIDON_END_SCENE);
        break;

    case GameState::POSEIDON_ENCOUNTER_SCENE:
        updateGameState(window, currentState, layout, loadSprites, event, audio, quiz, dialog, progressBar, jm, "Jsons/StageOne/Poseidon/POSEIDON_ENCOUNTER_SCENE.json", GameState::BUBBLE_GAME);
        break;

    case GameState::POSEIDON_WIN_SCENE:
        updateGameState(window, currentState, layout, loadSprites, event, audio, quiz, dialog, progressBar, jm, "Jsons/StageOne/Poseidon/POSEIDON_WIN_SCENE.json", GameState::POSEIDON_END_SCENE);
        break;

    case GameState::POSEIDON_LOSE_SCENE:
        updateGameState(window, currentState, layout, loadSprites, event, audio, quiz, dialog, progressBar, jm, "Jsons/StageOne/Poseidon/POSEIDON_LOSE_SCENE.json", GameState::POSEIDON_END_SCENE);
        break;

        // Dionysus' Path (Plateaus of Greece)
    case GameState::DIONYSUS_OPENING_SCENE:
        updateGameState(window, currentState, layout, loadSprites, event, audio, quiz, dialog, progressBar, jm, "Jsons/StageOne/Dionysus/DIONYSUS_OPENING_SCENE.json", GameState::DIONYSUS_CHOICE);
        break;

        /*
    case GameState::DIONYSUS_CHOICE:
        // Talk to stranger     ->  GameState::KOMOS_SCENE;
        // Run after pegasus    ->  GameState::FOREST_SCENE;
        break;
        */
        /*
        case GameState::DIONYSUS_QUIZ:
            // if ( win && Dionysus_Choice==KOMOS_SCENE )    -> GameState::KOMOS_WIN_SCENE
            // if ( lose && Dionysus_Choice==KOMOS_SCENE )   -> GameState::KOMOS_LOSE_SCENE
            // if ( win && Dionysus_Choice==FOREST_SCENE )   -> GameState::FOREST_WIN_SCENE
            // if ( lose && Dionysus_Choice==FOREST_SCENE )  -> GameState::FOREST_LOSE_SCENE
            break;
        */
    case GameState::KOMOS_SCENE:
        updateGameState(window, currentState, layout, loadSprites, event, audio, quiz, dialog, progressBar, jm, "Jsons/StageOne/Dionysus/KOMOS_SCENE.json", GameState::DIONYSUS_QUIZ);
        break;

    case GameState::KOMOS_WIN_SCENE:
        updateGameState(window, currentState, layout, loadSprites, event, audio, quiz, dialog, progressBar, jm, "Jsons/StageOne/Dionysus/KOMOS_WIN_SCENE.json", GameState::DIONYSUS_ENCOUNTER_SCENE);
        break;

    case GameState::KOMOS_LOSE_SCENE:
        updateGameState(window, currentState, layout, loadSprites, event, audio, quiz, dialog, progressBar, jm, "Jsons/StageOne/Dionysus/KOMOS_LOSE_SCENE.json", GameState::PEGASUS_CAUGHT_SCENE);
        break;

    case GameState::FOREST_SCENE:
        updateGameState(window, currentState, layout, loadSprites, event, audio, quiz, dialog, progressBar, jm, "Jsons/StageOne/Dionysus/FOREST_SCENE.json", GameState::DIONYSUS_QUIZ);
        break;

    case GameState::FOREST_WIN_SCENE:
        updateGameState(window, currentState, layout, loadSprites, event, audio, quiz, dialog, progressBar, jm, "Jsons/StageOne/Dionysus/FOREST_WIN_SCENE.json", GameState::DIONYSUS_ENCOUNTER_SCENE);
        break;

    case GameState::FOREST_LOSE_SCENE:
        updateGameState(window, currentState, layout, loadSprites, event, audio, quiz, dialog, progressBar, jm, "Jsons/StageOne/Dionysus/FOREST_LOSE_SCENE.json", GameState::PEGASUS_CAUGHT_SCENE);
        break;

    case GameState::DIONYSUS_ENCOUNTER_SCENE:
        updateGameState(window, currentState, layout, loadSprites, event, audio, quiz, dialog, progressBar, jm, "Jsons/StageOne/Dionysus/DIONYSUS_ENCOUNTER_SCENE.json", GameState::WINE_GAME);
        break;

    case GameState::DIONYSUS_WIN_SCENE:
        updateGameState(window, currentState, layout, loadSprites, event, audio, quiz, dialog, progressBar, jm, "Jsons/StageOne/Dionysus/DIONYSUS_WIN_SCENE.json", GameState::DIONYSUS_END_SCENE);
        break;

    case GameState::DIONYSUS_LOSE_SCENE:
        updateGameState(window, currentState, layout, loadSprites, event, audio, quiz, dialog, progressBar, jm, "Jsons/StageOne/Dionysus/DIONYSUS_LOSE_SCENE.json", GameState::DIONYSUS_END_SCENE);
        break;

    case GameState::DIONYSUS_END_SCENE:
        updateGameState(window, currentState, layout, loadSprites, event, audio, quiz, dialog, progressBar, jm, "Jsons/StageOne/Dionysus/DIONYSUS_END_SCENE.json", GameState::ATHENS_SCENE);
        break;

    case GameState::PEGASUS_CAUGHT_SCENE:
        updateGameState(window, currentState, layout, loadSprites, event, audio, quiz, dialog, progressBar, jm, "Jsons/StageOne/Dionysus/PEGASUS_CAUGHT_SCENE.json", GameState::ATHENS_SCENE);
        break;

    case GameState::ATHENS_SCENE:
        updateGameState(window, currentState, layout, loadSprites, event, audio, quiz, dialog, progressBar, jm, "Jsons/StageOne/Athens.json", GameState::STAGE_TWO_CHOICE);
        break;

    case GameState::STAGE_TWO_CHOICE:
        // Follow Smoke     ->  GameState::HEPHAESTUS_OPENING_SCENE;
        // Follow Music    ->  GameState::APOLLO_OPENING_SCENE;
        // Follow Signs    ->  GameState::ATHENA_OPENING_SCENE;
        break;

        // ------------------------------------------------------ Stage 2 ---------------------------------------------------------------

        // Hephaestus' Path (Smoke)
    case GameState::HEPHAESTUS_OPENING_SCENE:
        updateGameState(window, currentState, layout, loadSprites, event, audio, quiz, dialog, progressBar, jm, "Jsons/StageTwo/Hephaestus/HEPHAESTUS_OPENING_SCENE.json", GameState::HEPHAESTUS_QUIZ);
        break;
        /*
        case GameState::HEPHAESTUS_QUIZ:
            // if ( win  )   -> GameState::HEPHAESTUS_PRIVATE_FORGE_SCENE
            // if ( lose )   -> GameState::HEPHAESTUS_WAITING_SCENE
            break;
            */
    case GameState::HEPHAESTUS_PRIVATE_FORGE_SCENE:
        updateGameState(window, currentState, layout, loadSprites, event, audio, quiz, dialog, progressBar, jm, "Jsons/StageTwo/Hephaestus/HEPHAESTUS_PRIVATE_FORGE_SCENE.json", GameState::FORGE_GAME);
        break;

    case GameState::HEPHAESTUS_WIN_SCENE:
        updateGameState(window, currentState, layout, loadSprites, event, audio, quiz, dialog, progressBar, jm, "Jsons/StageTwo/Hephaestus/HEPHAESTUS_WIN_SCENE.json", GameState::OLYMPUS_DOOR);
        break;

    case GameState::HEPHAESTUS_LOSE_SCENE:
        updateGameState(window, currentState, layout, loadSprites, event, audio, quiz, dialog, progressBar, jm, "Jsons/StageTwo/Hephaestus/HEPHAESTUS_LOSE_SCENE.json", GameState::HEPHAESTUS_WAITING_SCENE);
        break;

    case GameState::HEPHAESTUS_WAITING_SCENE:
        updateGameState(window, currentState, layout, loadSprites, event, audio, quiz, dialog, progressBar, jm, "Jsons/StageTwo/Hephaestus/HEPHAESTUS_WAITING_SCENE.json", GameState::OLYMPUS_DOOR);
        break;



        // Athena's Path (Signs)
    case GameState::ATHENA_OPENING_SCENE:
        updateGameState(window, currentState, layout, loadSprites, event, audio, quiz, dialog, progressBar, jm, "Jsons/StageTwo/Athena/ATHENA_OPENING_SCENE.json", GameState::ATHENA_QUIZ);
        break;

        /*
    case GameState::ATHENA_QUIZ:
        // if ( win  )   -> GameState::HEPHAESTUS_PRIVATE_FORGE_SCENE
        // if ( lose )   -> GameState::HEPHAESTUS_WAITING_SCENE
        break;
    */
    case GameState::ATHENA_STUDY_SCENE:
        updateGameState(window, currentState, layout, loadSprites, event, audio, quiz, dialog, progressBar, jm, "Jsons/StageTwo/Athena/ATHENA_STUDY_SCENE.json", GameState::TYPING_GAME);
        break;

    case GameState::ATHENA_WIN_SCENE:
        updateGameState(window, currentState, layout, loadSprites, event, audio, quiz, dialog, progressBar, jm, "Jsons/StageTwo/Athena/ATHENA_WIN_SCENE.json", GameState::OLYMPUS_DOOR);
        break;

    case GameState::ATHENA_LOSE_SCENE:
        updateGameState(window, currentState, layout, loadSprites, event, audio, quiz, dialog, progressBar, jm, "Jsons/StageTwo/Athena/ATHENA_LOSE_SCENE.json", GameState::ATHENA_WAITING_SCENE);
        break;

    case GameState::ATHENA_WAITING_SCENE:
        updateGameState(window, currentState, layout, loadSprites, event, audio, quiz, dialog, progressBar, jm, "Jsons/StageTwo/Athena/ATHENA_WAITING_SCENE.json", GameState::OLYMPUS_DOOR);
        break;



        // Apollo's Path (Music)
    case GameState::APOLLO_OPENING_SCENE:
        updateGameState(window, currentState, layout, loadSprites, event, audio, quiz, dialog, progressBar, jm, "Jsons/StageTwo/Apollo/APOLLO_OPENING_SCENE.json", GameState::APOLLO_QUIZ);
        break;

        /*
        case GameState::APOLLO_QUIZ:
            // if ( win  )   -> GameState::HEPHAESTUS_PRIVATE_FORGE_SCENE
            // if ( lose )   -> GameState::HEPHAESTUS_WAITING_SCENE
            break;
        */
    case GameState::APOLLO_DANCE_SCENE:
        updateGameState(window, currentState, layout, loadSprites, event, audio, quiz, dialog, progressBar, jm, "Jsons/StageTwo/Apollo/APOLLO_DANCE_SCENE.json", GameState::RHYTHM_GAME);
        break;

    case GameState::APOLLO_WIN_SCENE:
        updateGameState(window, currentState, layout, loadSprites, event, audio, quiz, dialog, progressBar, jm, "Jsons/StageTwo/Apollo/APOLLO_WIN_SCENE.json", GameState::OLYMPUS_DOOR);
        break;

    case GameState::APOLLO_LOSE_SCENE:
        updateGameState(window, currentState, layout, loadSprites, event, audio, quiz, dialog, progressBar, jm, "Jsons/StageTwo/Apollo/APOLLO_LOSE_SCENE.json", GameState::APOLLO_WAITING_SCENE);
        break;

    case GameState::APOLLO_WAITING_SCENE:
        updateGameState(window, currentState, layout, loadSprites, event, audio, quiz, dialog, progressBar, jm, "Jsons/StageTwo/Apollo/APOLLO_WAITING_SCENE.json", GameState::OLYMPUS_DOOR);
        break;



        // TRANSITION from stage 2 to 3
    case GameState::OLYMPUS_DOOR:
        updateGameState(window, currentState, layout, loadSprites, event, audio, quiz, dialog, progressBar, jm, "Jsons/StageTwo/OLYMPUS_DOOR.json", GameState::HADES_OPENING_SCENE);
        break;


        // ------------------------------------------------------ Stage 3 ---------------------------------------------------------------
    case GameState::HADES_OPENING_SCENE:
        updateGameState(window, currentState, layout, loadSprites, event, audio, quiz, dialog, progressBar, jm, "Jsons/StageThree/HADES_OPENING_SCENE.json", GameState::HADES_QUIZ);
        break;

        /*
        case GameState::HADES_QUIZ:
            // GameState::HADES_ENCOUNTER_SCENE
            break;
        */
    case GameState::HADES_ENCOUNTER_SCENE:
        updateGameState(window, currentState, layout, loadSprites, event, audio, quiz, dialog, progressBar, jm, "Jsons/StageThree/HADES_ENCOUNTER_SCENE.json", GameState::BOSS_GAME);
        break;

    case GameState::HADES_TRUE_ENDING:
        updateGameState(window, currentState, layout, loadSprites, event, audio, quiz, dialog, progressBar, jm, "Jsons/StageThree/HADES_TRUE_ENDING.json", GameState::END_GAME);
        break;

    case GameState::HADES_FALSE_ENDING:
        updateGameState(window, currentState, layout, loadSprites, event, audio, quiz, dialog, progressBar, jm, "Jsons/StageThreeHADES_FALSE_ENDING.json", GameState::END_GAME);
        break;

    case GameState::END_GAME:
        std::cout << "GAME OVER" << endl;
        currentState = GameState::MENU;
        break;


    default:
        break;
    }


}

//func
void updateGameState(RenderWindow& window, GameState& currentState, ButtonLayout& layout, LoadSprites& loadSprites, Event& event, Audio& audio, QuizUI& quiz, DialogManager& dialog, ProgressBar& progressBar, JsonManager& jm, const string& jsonPath, GameState nextState) {

    // --- 1. JSON Initialization ---
    if (!jm.IsLoaded() || jm.GetCurrentPath() != jsonPath) {
        // cout << "updateGameState: Loading JSON '" << jsonPath << "' (Current: '" << jm.GetCurrentPath() << "')." << endl;
        jm.ClearAll();
        jm.LoadJson(jsonPath);

        if (jm.IsLoaded()) {
            jm.LoadData();
            dialog.SetDialogueText(jm.line);
        }
        else {
            // cerr << "updateGameState: ERROR - Failed to load JSON. Transitioning to ERROR_STATE." << endl;
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
            //cout << "updateGameState: Cannot advance. HasNext=" << boolalpha << jm.HasNext()
                //<< ", DialogFinished=" << boolalpha << dialog.isDialogFinished() << endl;
        }
    }

    // Transition to next state on "Next" button click
    bool canTransition = !jm.HasNext() && dialog.isDialogFinished();

    if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left && canTransition && layout.nextButtonClicked(window)) {
        // cout << "updateGameState: Next button clicked. Transitioning state." << endl;
        audio.playClickButtonSound();
        jm.ClearAll();
        currentState = nextState;
        stateChanged = true;
        return;

    }

    // --- 3. Drawing ---
    if (!stateChanged) {
        // cout << "drawn" << endl;
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