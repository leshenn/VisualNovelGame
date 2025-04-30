#pragma once

// Enumeration of possible game states
enum class GameState {



    // --- MENU ---
    MENU,                      // Main menu screen
    INTRO,                     // Introduction screen (unused in current implementation)

    // --- INTRODUCTION ---
    NYXGREETING_SCENE,         // Greeting from Nyx
    STAGE_ONE_CHOICE,          // Button choices for which god to visit

    // --- Stage 1 ---

    // Poseidon's Path (Seas of Greece)
    POSEIDON_OPENING_SCENE,
    POSEIDON_CHOICE,
    ATLANTIS_SCENE,             // Jump into Ocean
    ATLANTIS_WIN_SCENE,
    ATLANTIS_LOSE_SCENE,
    SHRINE_SCENE,               // Go to Shrine
    SHRINE_WIN_SCENE,
    SHRINE_LOSE_SCENE,
    POSEIDON_QUIZ,
    POSEIDON_ENCOUNTER_SCENE,    //Win Quiz + Call BUBBLE_GAME
    POSEIDON_WIN_SCENE,
    POSEIDON_LOSE_SCENE,
    POSEIDON_END_SCENE,         //Lose Quiz || End
    SHRINE_QUIZ,
    ATLANTIS_QUIZ,

    // Dionysus' Path (Plateaus of Greece)
    DIONYSUS_OPENING_SCENE,
    DIONYSUS_CHOICE,
    KOMOS_SCENE,                // Talk to Stranger
        KOMOS_QUIZ,
	    KOMOS_WIN_SCENE,
	    KOMOS_LOSE_SCENE,
    FOREST_SCENE,               // Run after Pegasus
        FOREST_QUIZ,
	    FOREST_WIN_SCENE,
	    FOREST_LOSE_SCENE,
    DIONYSUS_QUIZ,
	DIONYSUS_ENCOUNTER_SCENE,   //Win Quiz + Call WINE_GAME
    DIONYSUS_LOSE_SCENE,         
    DIONYSUS_WIN_SCENE,
    PEGASUS_CAUGHT_SCENE,        //Lose Quiz
	DIONYSUS_END_SCENE,         //End

    // After Stage 1, choose next stage
    ATHENS_SCENE,
    STAGE_TWO_CHOICE,           

    // --- Stage 2 ---

    // Apollo's Path (Music)
    APOLLO_OPENING_SCENE,
    APOLLO_QUIZ,
    APOLLO_DANCE_SCENE,         // Win Quiz
    APOLLO_WIN_SCENE,           // Win Minigame
    APOLLO_LOSE_SCENE,          // Lose Minigame
    APOLLO_WAITING_SCENE,     // Lose Quiz || Lose Minigame

    // Athena's Path (Signs)
    ATHENA_OPENING_SCENE,
    ATHENA_QUIZ,
    ATHENA_STUDY_SCENE,         // Win Quiz + Call TYPING_GAME
    ATHENA_WIN_SCENE,           // Win Minigame
    ATHENA_LOSE_SCENE,          // Lose Minigame
    ATHENA_WAITING_SCENE,       // Lose Quiz || Lose Minigame

    // Hephaestus' Path (Smoke)
    HEPHAESTUS_OPENING_SCENE,
    HEPHAESTUS_QUIZ,
    HEPHAESTUS_PRIVATE_FORGE_SCENE,     // Win Quiz + Call FORGE_GAME
    HEPHAESTUS_WIN_SCENE,       // Win Minigame
    HEPHAESTUS_LOSE_SCENE,      // Lose Minigame
    HEPHAESTUS_WAITING_SCENE,   // Lose Quiz || Lose Minigame

    // After Stage 2, transition to stage 3
    OLYMPUS_DOOR,

    // --- Stage 3 ---

    // Hades' Path (Underworld)
    HADES_OPENING_SCENE,
    HADES_QUIZ,
    HADES_ENCOUNTER_SCENE,      // Call BOSS_GAME
    HADES_FALSE_ENDING,         // Lose Game
    HADES_TRUE_ENDING,          // Win Game

    END_GAME,

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
    NONE
};
