#pragma once

// Enumeration of possible game states
enum class GameState {
    MENU,                   // Main menu screen
    INTRO,                  // Introduction screen (unused in current implementation)
    CUTSCENE,               // This is where the cutscene would be held
    NYX1,                   // Conversation with nyx
    STAGE_ONE_MENU,         // World selection screen
    SEAWORLD,               // Poesidon Stage
    UNDERWORLD,             // Hades stage
    COUNTRY_SIDE,           // Dionysus stage
    AMPHITRITE_STAGE,   
    NYX2,                   // Conversation with nyx
    STAGE_TWO_MENU,         // World selection screen
    ATHENS,                 // Athena stage
    THRACE,                 // Ares stage
    DELPHI,                 // Apollo stage
    RHAMNOUS,               // Nemisis stage
    CRETE,                  // Deadalus stage
    NYX3,
    STAGE_THREE_MENU,       // World selection screen
    CYPRUS,                 // Aphrodite stage
    OLYMPUS,                // Zeus stage
    LETHE,                  // Hypnos stage
    ARGOS,                  // Hera stage
    MOUNT_CYLLENE,          // Hermes stage
    NONE
};