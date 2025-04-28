#include "DialogManager.h"
#include <iostream>

DialogManager::DialogManager() {
    font.loadFromFile("Fonts/norse/Norsebold.otf");
    dialogText.setFont(font);
    dialogText.setFillColor(sf::Color::Black);
    
}

bool DialogManager::loadDialog(const std::string& filename, const std::string& dialogId) {
    dialogText.setPosition(150, 500);
    dialogText.setCharacterSize(26);
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

bool DialogManager::loadIntroDialog(const std::string& filename, const std::string& dialogId) {
    dialogText.setPosition(350, 170);
    dialogText.setCharacterSize(23);
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
        // Get all lines as a vector
        std::vector<std::string> lines = dialogData[dialogId].get<std::vector<std::string>>();

        // Combine all lines into a single paragraph with spaces between them
        std::string fullParagraph;
        for (const auto& line : lines) {
            fullParagraph += line + " ";
        }

        // Remove trailing space if there is one
        if (!fullParagraph.empty()) {
            fullParagraph.pop_back();
        }

        // Set the complete paragraph
        currentLines = { fullParagraph }; // Store as single-element vector
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
    if (!hasMoreLines()) {
        isDialogComplete = true;  // Mark as complete when no more lines

    }
}

void DialogManager::introNextLine() {
    if (!hasMoreLines()) {
        isDialogComplete = true;  // Mark complete FIRST
        dialogText.setString("");  // Clear text immediately
        return;
    }
    currentIndex++;
    dialogText.setString(currentLines[currentIndex]);
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

void DialogManager::clearText() {
    dialogText.setString("");
    isDialogComplete = true;
}

//Sets the text 
void DialogManager::SetDialogueText(const std::string& newText)
{
    dialogText.setPosition(140,500);
    dialogText.setCharacterSize(23);
    dialogText.setString(newText);
}

