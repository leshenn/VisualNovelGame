#include "JsonManager.h"
#include <fstream>
#include <iostream>

void JsonManager::LoadJson(const std::string& jsonPath) noexcept
{
    ClearAll();

    std::ifstream ifs{ jsonPath };
    if (!ifs.is_open()) {
        std::cerr << "Error: Cannot open JSON file: " << jsonPath << "\n";
        return;
    }

    try {
        ifs >> jsonCurrent_;
    }
    catch (const json::parse_error& e) {
        std::cerr << "Error: JSON parse failed (" << e.what()
            << "), byte " << e.byte << "\n";
        return;
    }

    if (!jsonCurrent_.contains("data") || !jsonCurrent_["data"].is_array()) {
        std::cerr << "Error: Missing or invalid 'data' array in: "
            << jsonPath << "\n";
        jsonCurrent_.clear();
        return;
    }

    UpdateHasNext();
}

void JsonManager::LoadData() noexcept
{
    if (!hasNext_)
        return;

    const auto& arr = jsonCurrent_["data"];
    if (currentIndex_ >= arr.size()) {
        hasNext_ = false;
        return;
    }

    const auto& e = arr[currentIndex_++];
    line = e.value("line", "");
    backgroundSprite = e.value("background_sprite", "");
    leftSprite = e.value("left_sprite", "");
    rightSprite = e.value("right_sprite", "");

    if (e.contains("audio") && e["audio"].is_object()) {
        audioPath = e["audio"].value("path", "");
        audioLoop = e["audio"].value("loop", false);
    }
    else {
        audioPath.clear();
        audioLoop = false;
    }

    UpdateHasNext();
}

bool JsonManager::IsLoaded() const noexcept
{
    return !jsonCurrent_.is_null()
        && jsonCurrent_.contains("data")
        && jsonCurrent_["data"].is_array();
}

//Clear the asset variables
void JsonManager::ClearLoads() noexcept
{
    line.clear();
    backgroundSprite.clear();
    leftSprite.clear();
    rightSprite.clear();
    audioPath.clear();
    audioLoop = false;
}

//clear the json and asset variables
void JsonManager::ClearAll() noexcept
{
    jsonCurrent_.clear();
    currentIndex_ = 0;
    hasNext_ = false;

    line.clear();
    backgroundSprite.clear();
    leftSprite.clear();
    rightSprite.clear();
    audioPath.clear();
    audioLoop = false;
}

void JsonManager::UpdateHasNext() noexcept
{
    hasNext_ = jsonCurrent_.contains("data")
        && jsonCurrent_["data"].is_array()
        && (currentIndex_ < jsonCurrent_["data"].size());
}