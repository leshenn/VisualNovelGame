#include "DialogManager.h"
#include <iostream>

DialogManager::DialogManager() {
    font.loadFromFile("Fonts/norse/Norsebold.otf");
    dialogText.setFont(font);
    dialogText.setCharacterSize(26);
    dialogText.setFillColor(sf::Color::Black);
    dialogText.setPosition(150, 500);
}

bool DialogManager::loadDialog(const std::string& filename, const std::string& dialogId) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return false;
    }

    try {
        file >> dialogData;
    }
    catch (const nlohmann::json::parse_error& e) {
        std::cerr << "JSON parse error at byte " << e.byte << ": " << e.what() << std::endl;
        return false;
    }

    if (!dialogData.contains(dialogId)) {
        std::cerr << "Error: Dialog ID '" << dialogId << "' not found in file " << filename << std::endl;
        std::cerr << "Available keys: ";
        for (auto& el : dialogData.items()) {
            std::cerr << el.key() << " ";
        }
        std::cerr << std::endl;
        return false;
    }

    try {
        currentLines = dialogData[dialogId].get<std::vector<std::string>>();
        currentIndex = 0;
        dialogText.setString(currentLines[currentIndex]);
        return true;
    }
    catch (const nlohmann::json::exception& e) {
        std::cerr << "Error processing dialog lines: " << e.what() << std::endl;
        return false;
    }
}

void DialogManager::nextLine() {
    if (hasMoreLines()) {
        currentIndex++;
        dialogText.setString(currentLines[currentIndex]);
    }
    if(!hasMoreLines()) {
        isDialogComplete = true;  // Mark as complete when no more lines
        
    }
}

bool DialogManager::isDialogFinished() const {
    return isDialogComplete || !hasMoreLines();
}

bool DialogManager::hasMoreLines() const {
    return currentIndex + 1 < currentLines.size();
}

void DialogManager::draw(sf::RenderWindow& window) {
    window.draw(dialogText);
}

void DialogManager::reset() {
    currentLines.clear();
    currentIndex = 0;
    isDialogComplete = false;
}
