// JsonManager.cpp
#include "JsonManager.h"
#include <fstream>
#include <iostream>

void JsonManager::LoadJson(const std::string& jsonPath) noexcept {
    ClearAll();
    currentJsonPath_ = jsonPath;

    std::ifstream ifs{ jsonPath };
    if (!ifs.is_open()) {
        std::cerr << "Error: Cannot open JSON file: " << jsonPath << "\n";
        currentJsonPath_.clear();
        return;
    }

    try {
        ifs >> jsonCurrent_;
    }
    catch (const json::parse_error& e) {
        std::cerr << "Error: JSON parse failed (" << e.what()
            << "), byte " << e.byte << " in " << jsonPath << "\n";
        jsonCurrent_.clear();
        currentJsonPath_.clear();
        return;
    }

    if (!jsonCurrent_.contains("data") || !jsonCurrent_["data"].is_array() || jsonCurrent_["data"].empty()) {
        std::cerr << "Error: Missing, invalid, or empty 'data' array in: " << jsonPath << "\n";
        jsonCurrent_.clear();
        currentJsonPath_.clear();
        return;
    }

    currentIndex_ = 0;
    UpdateHasNext();
    //std::cout << "JsonManager: Loaded JSON: " << jsonPath << std::endl;
}

void JsonManager::LoadData() noexcept {
    const auto& arr = jsonCurrent_["data"];
    if (currentIndex_ >= arr.size()) {
        hasNext_ = false;
        return;
    }

    const auto& e = arr[currentIndex_];
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

    //std::cout << "JsonManager: Loaded data idx=" << currentIndex_ << std::endl;
    ++currentIndex_;
    UpdateHasNext();
}

bool JsonManager::IsLoaded() const noexcept {
    return !jsonCurrent_.is_null() && !currentJsonPath_.empty();
}

bool JsonManager::HasNext() const noexcept {
    return hasNext_;
}

std::string JsonManager::GetCurrentPath() const noexcept {
    return currentJsonPath_;
}

void JsonManager::ClearAll() noexcept {
    jsonCurrent_.clear();
    currentIndex_ = 0;
    hasNext_ = false;
    currentJsonPath_.clear();
    line.clear();
    backgroundSprite.clear();
    leftSprite.clear();
    rightSprite.clear();
    audioPath.clear();
    audioLoop = false;
}

void JsonManager::Clear() noexcept {
    line.clear();
    backgroundSprite.clear();
    leftSprite.clear();
    rightSprite.clear();
    audioPath.clear();
    audioLoop = false;
}

void JsonManager::UpdateHasNext() noexcept {
    hasNext_ = jsonCurrent_.contains("data")
        && jsonCurrent_["data"].is_array()
        && (currentIndex_ < jsonCurrent_["data"].size());
}