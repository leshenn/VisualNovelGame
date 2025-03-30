#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include "Button.h"
#include "PoseidonConvoState.h"
#include "HadesConvoState.h"
#include "DionysusConvoState.h"
//#include "EndState.h"
#include "StateManager.h"

using json = nlohmann::json;
using namespace sf;
using namespace std;
const int WIN_WIDTH = 890;
const int WIN_HEIGHT = 448;

int main() {
    sf::RenderWindow window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "Visual Novel");
    sf::Vector2u windowSize = window.getSize();

    StateManager stateManager;
    stateManager.pushState(std::make_unique<PoseidonConvoState>(windowSize));
    stateManager.getCurrentState()->load();

    // Next Button
    sf::Font font;
    font.loadFromFile("Robot_Font.otf");
    Button nextButton("Next", sf::Vector2f{ 50, 25 }, 15, sf::Color::White, sf::Color::Black);
    nextButton.setPosition({ 800, 400 });
    nextButton.setFont(font);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && nextButton.isMouseOver(window)) {
                // Transition to next state
                if (dynamic_cast<PoseidonConvoState*>(stateManager.getCurrentState())) {
                    stateManager.popState();
                    stateManager.pushState(std::make_unique<HadesConvoState>(windowSize));
                }
                else if (dynamic_cast<HadesConvoState*>(stateManager.getCurrentState())) {
                    stateManager.popState();
                    stateManager.pushState(std::make_unique<DionysusConvoState>(windowSize));
                } // ... and so on
                stateManager.getCurrentState()->load();
            }
        }

        window.clear();
        stateManager.getCurrentState()->draw(window);
        nextButton.drawTo(window);
        window.display();
    }
    return 0;
}