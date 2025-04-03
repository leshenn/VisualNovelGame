#pragma once

// Enumeration of possible game states
enum class GameState {
    MENU,          // Main menu screen
    INTRO,         // Introduction screen (unused in current implementation)
    START_GAME,    // World selection screen
    AMPHITRITE_STAGE,      // Poesidon stage
    UNDERWORLD,    // Hades stage
    COUNTRY_SIDE,  // Dionysus stage
    NONE
};