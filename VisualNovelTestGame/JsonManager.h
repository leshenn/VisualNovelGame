#pragma once

#include <string>
#include "nlohmann/json.hpp"

// Manages loading and iterating through a dialogue JSON file
class JsonManager {
public:
    using json = nlohmann::json;
    JsonManager() = default;
    ~JsonManager() = default;

    // Load a new JSON file; resets internal state
    void LoadJson(const std::string& jsonPath) noexcept;

    // Load the next entry (line, sprites, audio) from the current JSON
    void LoadData() noexcept;

    // Check if a JSON file is currently loaded and valid
    bool IsLoaded() const noexcept;

    // Check if there is another entry to load
    bool HasNext() const noexcept;

    // Get the path of the currently loaded JSON file
    std::string GetCurrentPath() const noexcept;

    // Clear all loaded JSON and entry data
    void ClearAll() noexcept;

    // Public fields populated by LoadData()
    std::string line;
    std::string backgroundSprite;
    std::string leftSprite;
    std::string rightSprite;
    std::string audioPath;
    bool        audioLoop = false;

private:
    // Internal JSON representation and iteration state
    nlohmann::json jsonCurrent_;
    std::string    currentJsonPath_;
    size_t         currentIndex_ = 0;
    bool           hasNext_ = false;

    // Update hasNext_ based on currentIndex_ and jsonCurrent_.
    void UpdateHasNext() noexcept;
};