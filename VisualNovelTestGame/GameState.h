#pragma once

// Enumeration of possible game states
enum class GameState {
    MENU,                   // Main menu screen
    INTRO,                  // Introduction screen (unused in current implementation)
    CHOOSE_CHARACTER,       // Choose gender of character
    CUTSCENE,               // This is where the cutscene would be held
    NYX1,                   // Conversation with nyx
    STAGE_ONE_MENU,         // World selection screen
    SEAWORLD,               // Poesidon Stage
    UNDERWORLD,             // Hades stage
    COUNTRY_SIDE,           // Dionysus stage
    NYX2,                   // Conversation with nyx
    //STAGE_TWO_MENU,         // World selection screen
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
    BOSS_GAME,
    TYPING_GAME,
    NONE
};