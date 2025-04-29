#pragma once
#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>
#include <fstream>

class DialogManager {
private:
    nlohmann::json dialogData;
    std::vector<std::string> currentLines;
    std::size_t currentIndex = 0;
    sf::Font font;
    sf::Text dialogText;
    bool isDialogComplete = false;

public:
    DialogManager();
    bool loadDialog(const std::string& filename, const std::string& dialogId);
    bool loadIntroDialog(const std::string& filename, const std::string& dialogId);
    void nextLine();
    void introNextLine();
    bool hasMoreLines() const;
    void draw(sf::RenderWindow& window);
    void reset();
    bool isDialogFinished() const;
    void clearText();
    void SetDialogueText(const std::string& newText);
};
