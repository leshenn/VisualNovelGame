#pragma once

// Enumeration of possible game states
enum class GameState {
   


    // --- MENU + INTRODUCTION ---
    MENU,                      // Main menu screen
    INTRO,                     // Introduction screen (unused in current implementation)
    NYXGREETING_SCENE,          // Greeting from Nyx
    STAGE_ONE_CHOICE,           // Button choices for which god to visit

    // --- Stage 1 ---

    // Poseidon's Path (Seas of Greece)
    POSEIDON_OPENING_SCENE,
    POESEIDON_CHOICE,
    ATLANTIS_SCENE,             // Jump into Ocean
    ATLANTIS_WIN_SCENE,
    ATLANTIS_LOSE_SCENE,
    SHRINE_SCENE,               // Go to Shrine
    SHRINE_WIN_SCENE,
    SHRINE_LOSE_SCENE,
    POSEIDON_QUIZ,
	POEIDON_ENCOUNTER_SCENE,    //Win Quiz + Call BUBBLE_GAME
    POSEIDON_WIN_SCENE,
    POSEIDON_LOSE_SCENE,
    POSEIDON_END_SCENE,         //Lose Quiz || End

    // Dionysus' Path (Plateaus of Greece)
    DIONYSUS_OPENING_SCENE,
    DIONYSUS_CHOICE,
    KOMOS_SCENE,                // Talk to Stranger
	KOMOS_WIN_SCENE,
	KOMOS_LOSE_SCENE,
    FOREST_SCENE,               // Run after Pegasus
	FOREST_WIN_SCENE,
	FOREST_LOSE_SCENE,
    DIONYSUS_QUIZ,
	DIONYSUS_ENCOUNTER_SCENE,   //Win Quiz + Call WINE_GAME
    DIONYSUS_LOSE_SCENE,         
    DIONYSUS_WIN_SCENE,
    PEGASUS_CATCH_SCENE,        //Lose Quiz
	DIONYSUS_END_SCENE,         //End


    ATHENS_SCENE,
    STAGE_TWO_CHOICE,           // After Stage 1, choose next stage

    // --- Stage 2 ---

    // Apollo's Path (Music)
    APOLLO_OPENING_SCENE,
    APOLLO_QUIZ,
    APOLLO_DANCE_SCENE,         // Win Quiz
    APOLLO_BACKSTAGE_SCENE,     // Lose Quiz + Call RHYTHM_GAME

    // Athena's Path (Smoke)
    ATHENA_OPENING_SCENE,
    ATHENA_QUIZ,
    ATHENA_WAITING_SCENE,       // Lose Quiz
    ATHENA_REJECTION_SCENE,     // Win Quiz + Win BUBBLE_GAME
    ATHENA_STUDY_SCENE,         // Win Quiz + Call TYPING_GAME

    // Hephaestus' Path (Forge)
    HEPHAESTUS_OPENING_SCENE,
    HEPHAESTUS_QUIZ,
    HEPHAESTUS_WAITING_SCENE,   // Lose Quiz
    HEPHAESTUS_FORGE_SCENE,     // Win Quiz + Call _

    // --- Stage 3 ---

    // Hera's Path (Palace)
	HERA_OPENING_SCENE,
    HERA_QUIZ,
	HERA_REJECTION_SCENE,
    HERA_END_SCENE,


    // Aphrodite's Path (Bedchamber)
	APHRODITE_OPENING_SCENE,
	APHRODITE_QUIZ,
	APHRODITE_REJECTION_SCENE,
	APHRODITE_END_SCENE,

    // Hades' Path (Underworld)
    HADES_ENCOUNTER_SCENE,      //Call BOSS_GAME

    HADES_FALSE_ENDING,         // Lose Game
    HADES_TRUE_ENDING,          // Win Game

    // --- Mini-Games ---
    BOSS_GAME,
    TYPING_GAME,
    BUBBLE_GAME,
    RHYTHM_GAME,
    WINE_GAME,
    FORGE_GAME,

    // --- OLD STATES ---
    CHOOSE_CHARACTER,       // Choose gender of character
    CUTSCENE,               // This is where the cutscene would be held
    NYX1,                   // Conversation with nyx
    STAGE_ONE_MENU,         // World selection screen
    SEAWORLD,               // Poesidon Stage
    UNDERWORLD,             // Hades stage
    COUNTRY_SIDE,           // Dionysus stage
    NYX2,                   // Conversation with nyx
    STAGE_TWO_MENU,         // World selection screen
    ATHENS,                 // Athena stage
    DELPHI,                 // Apollo stage
    NYX3,
    THRACE,                 // Ares stage
    RHAMNOUS,               // Nemisis stage
    NYX4,
    CRETE,                  // Deadalus stage
    NYX5,
    CYPRUS,                 // Aphrodite stage
    LETHE,                  // Hypnos stage
    NYX6,
    OLYMPUS,                // Zeus stage
    ARGOS,                  // Hera stage
    NYX7,
    MOUNT_CYLLENE,          // Hermes stage
    NYX8,

};
