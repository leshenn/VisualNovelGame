#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <algorithm>
#include <array>
#include <set>
#include <random>
#include <iostream>
#include <stdexcept>
#include "WordGame.hpp" 
//#include <nlohmann/json.hpp>

using namespace std;

WordGame::WordGame() :
    MAX_SPAWN_INTERVAL(2.0f),
    spawnInterval(2.0f),
    minSpawnInterval(0.55f),
    spawnAcceleration(0.98f), //2% faster each time
    speed(spawnInterval),
    window(sf::VideoMode(600, 700), "Word Game"),
    gridCells{},
    targetStartChar('\0'),
    score(0),
    gameOver(false),
    errorGridIndex(-1),
    ERROR_DURATION(0.1f),
    endScreen(sf::seconds(5))
{
    gridCells.fill(false);

    if (!correctBuffer.loadFromFile("correct.wav") || !wrongBuffer.loadFromFile("wrong.wav")) {
        cout << ("Failed to load sound files!") << endl;
    }
    correctSound.setBuffer(correctBuffer);
    wrongSound.setBuffer(wrongBuffer);

    if (!font.loadFromFile("RhythmAssets/Font/roboto.ttf")) {
        throw std::runtime_error("Failed to load font");
    }
    window.setFramerateLimit(60);


    wordList = {
        "Zeus", "Hera", "Poseidon", "Demeter", "Athena", "Apollo", "Artemis", "Ares", "Hephaestus", "Aphrodite", "Hermes", "Dionysus", "Hestia", "Hades", "Persephone", "Cronus", "Rhea", "Oceanus",
        "Tethys", "Hyperion", "Theia", "Iapetus", "Mnemosyne", "Prometheus", "Epimetheus", "Atlas", "Gaia", "Uranus", "Chaos", "Nyx", "Tartarus", "Erebus", "Eros", "Aether", "Hemera", "Pontus", "Helios",
        "Selene", "Aeolus", "Nike", "Nemesis", "Tyche", "Hypnos", "Thanatos", "Iris", "Hecate", "Charon", "Cerberus", "Talos", "Minotaur", "Hydra", "Chimera", "Cyclops", "Gorgon", "Siren", "Harpy", "Satyr",
        "Centaur", "Nymph", "Dryad", "Nyx", "Scylla", "Sphinx", "Phoenix", "Griffin", "Pegasus", "Basilisk", "Orpheus", "Heracles", "Perseus", "Theseus", "Jason", "Achilles",
        "Odysseus", "Ajax", "Hector", "Paris", "Agamemnon", "Menelaus", "Cadmus", "Meleager", "Atalanta", "Antigone", "Oedipus", "Medea", "Pandora", "Tantalus", "Sisyphus", "Tiresias", "Penelope", "Strong",
       "Colosseum", "Pantheon", "Basilica", "Forum", "Aqueduct", "Temple", "Baths", "Arch", "Dome", "Vault", "Column", "Hypocaust", "Atrium", "Porticus", "Insula", "Domus",
       "Mosaic", "Fresco", "Stucco", "Tessera", "Sgraffito", "Coffering", "Lacunar", "Spolia", "Sima", "Mutule",
        "Obelisk", "Mausoleum", "Colosseum", "Thermae", "Cloaca", "Aqueduct", "Pons", "Xystus", "Groma", "Oculum", "Cellarium", "Umbilicus",
        "Cavum""Argus", "Circe", "Creon", "Ceres", "Doris", "Erato", "Helen", "Homer", "Lethe", "Midas", "Naiad", "Orion", "Priam", "Clio",
        "Fauns", "Muses", "Styx", "Doric", "Ionic", "Attic", "Sigma", "Theta", "Vault", "Niche", "Oecus", "Porta", "Ethos", "Grace", "Ichor",
        "Iliad", "Omega", "Oread", "Zeno", "Zeta", "Fauna", "Echid", "Aegis", "Eidos", "Lamia", "Ladon", "Eurus", "Zephy", "Notus", "Boreas",
        "Aegir", "Ephyra", "Lotos", "Paean", "Psyche", "Silen", "Satyr"
    };
}



string  WordGame::generateWord() {
    set<char> usedChars;
    for (const auto& word : activeWords)
        usedChars.insert(static_cast<char>(tolower(word.text[0])));

    vector<string> candidates;
    for (const auto& word : wordList) {
        char firstChar = static_cast<char>(tolower(word[0]));
        if (!usedChars.count(firstChar))
            candidates.push_back(word);
    }

    if (candidates.empty()) return "";
    //int randomIndex = rand() % candidates.size();
    static mt19937 rng(random_device{}());
    uniform_int_distribution<size_t> dist(0, candidates.size() - 1);
    return candidates[dist(rng)];
}

void  WordGame::spawnWord() {
    vector<int> freeCells;
    for (int i = 0; i < 9; i++)
        if (!gridCells[i]) freeCells.push_back(i);

    if (!freeCells.empty()) {
        // static mt19937 rng(random_device{}());
        // uniform_int_distribution<size_t> dist(0, freeCells.size() - 1);
        int randomCell = rand() % freeCells.size();
        int cell = freeCells[randomCell];

        string newWord = generateWord();
        if (!newWord.empty()) {
            gridCells[cell] = true;
            activeWords.push_back({ newWord, cell });

            spawnInterval = max(minSpawnInterval, spawnInterval * spawnAcceleration);
            speed = spawnInterval;
        }
    }
}

void  WordGame::handleInput(char c) {
    c = static_cast<char>(tolower(c));

    if (currentInput.empty()) {
        bool foundWord = false;
        for (auto& word : activeWords) {
            if (tolower(word.text[0]) == c) {
                targetStartChar = c;
                currentInput += c;
                word.highlighted = true;
                foundWord = true;
                break;
            }
        }
        if (!foundWord) {
            wrongSound.play();  // Play when no matching word found
        }
    }
    else {

        auto it = activeWords.begin();
        for (; it != activeWords.end(); ++it) {
            // if the first letter matches, break out with 'it' pointing at it
            if (std::tolower(it->text.front()) == targetStartChar) {
                break;
            }
        }

        if (it != activeWords.end()) {
            Word& targetWord = *it;
            size_t pos = currentInput.size();

            if (pos < targetWord.text.size()) {
                if (tolower(targetWord.text[pos]) == c) {
                    currentInput += c;

                    if (currentInput.size() == targetWord.text.size()) {
                        gridCells[targetWord.gridIndex] = false;
                        activeWords.erase(it);
                        currentInput.clear();
                        targetStartChar = '\0';
                        score += 10;
                        correctSound.play();  // Correct completion
                    }
                }
                else {
                    errorGridIndex = targetWord.gridIndex;
                    errorTimer.restart();
                    wrongSound.play();  // Wrong character
                    wrongInput();
                    resetInput();
                }
            }
        }
        else {
            wrongSound.play();  // No target word found
            resetInput();
        }
    }
}

void  WordGame::resetInput() {
    currentInput.clear();
    targetStartChar = '\0';
    for (auto& word : activeWords)
        word.highlighted = false;
}

void  WordGame::wrongInput() {
    score -= 5;
}

void  WordGame::drawSpeedBar() {
    const float barWidth = 300.0f; // Total width of the speed bar
    const float barHeight = 20.0f;  // Height of the speed bar

    // Calculate the width based on current speed and maximum speed
    float speedRange = MAX_SPAWN_INTERVAL - minSpawnInterval; // Range of speed values
    float normalizedSpeed = speed - minSpawnInterval;        // Normalized current speed

    // Ensure we don't go below 0 or above the range
    normalizedSpeed = std::max(0.0f, std::min(normalizedSpeed, speedRange));

    // Calculate the fill width
    float fillWidth = (1.0f - (normalizedSpeed / speedRange)) * barWidth;


    // Background bar
    sf::RectangleShape backgroundBar(sf::Vector2f(barWidth, barHeight));
    backgroundBar.setPosition(10, 650); // Positioning the bar
    backgroundBar.setFillColor(sf::Color(150, 150, 150)); // Gray background
    window.draw(backgroundBar);

    // Fill bar
    sf::RectangleShape fillBar(sf::Vector2f(fillWidth, barHeight));
    fillBar.setPosition(10, 650); // Same position as background
    fillBar.setFillColor(sf::Color(30, 255, 0)); // Green color for fill
    window.draw(fillBar);
}

bool WordGame::getGameOver() {
    return gameOver;
}

void  WordGame::run() {
    sf::SoundBuffer s;
    if (!s.loadFromFile("easy_cheesy.ogg")) {
        cout << ("easy_cheesy.ogg sound failed to load") << endl;
    }
    sf::Sound mysound;
    mysound.setBuffer(s);
    mysound.setLoop(true); // Loop the sound
    mysound.setVolume(50);
    mysound.play();
    while (window.isOpen()) {
        handleEvents();
        update();
        render();
    }
}

int  WordGame::getFinalScore() {
    return score;
}

void  WordGame::handleEvents() {
    sf::Event event{};
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::TextEntered && !gameOver) {
            if (event.text.unicode < 128) {
                char c = static_cast<char>(event.text.unicode);
                if (isalpha(c)) handleInput(c);
            }
        }
    }
}

void  WordGame::update() {
    /* if (gameOver) {
         if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
             restartGame();

             return;
         }
     }*/

     // Spawn new words based on time
    if (spawnClock.getElapsedTime().asSeconds() > spawnInterval) {
        spawnWord();
        spawnClock.restart();
    }

    // Check game over condition
    if (all_of(gridCells.begin(), gridCells.end(), [](bool b) { return b; })) {
        gameOver = true;
    }
    // Clear error state after duration
    if (errorTimer.getElapsedTime().asSeconds() > ERROR_DURATION) {
        errorGridIndex = -1;
    }

    if (gameOver && endScreen.asSeconds() > 0) {
        endScreen -= sf::seconds(0.05);
    }


}

void  WordGame::render() {
    window.clear(sf::Color(0, 0, 0));

    // Draw grid
    const float cellSize = 200.0f;
    for (int i = 0; i < 9; i++) {
        int row = i / 3;
        int col = i % 3;

        sf::RectangleShape cell(sf::Vector2f(cellSize - 4, cellSize - 4));
        cell.setPosition(col * cellSize + 2, row * cellSize + 2);
        cell.setFillColor(sf::Color::White);
        cell.setOutlineThickness(2);
        cell.setOutlineColor(sf::Color::Black);
        window.draw(cell);


        drawSpeedBar();

        if (i == errorGridIndex && errorTimer.getElapsedTime().asSeconds() < ERROR_DURATION) {
            sf::RectangleShape errorHighlight(sf::Vector2f(cellSize - 4, cellSize - 4));
            errorHighlight.setPosition(col * cellSize + 2, row * cellSize + 2);
            errorHighlight.setFillColor(sf::Color(255, 0, 0, 150));
            window.draw(errorHighlight);
        }

    }

    // Draw words
    for (const auto& word : activeWords) {
        int row = word.gridIndex / 3;
        int col = word.gridIndex % 3;
        float x = col * cellSize + cellSize / 2;
        float y = row * cellSize + cellSize / 2;

        if (word.highlighted) {
            sf::RectangleShape highlight(sf::Vector2f(cellSize - 4, cellSize - 4));
            highlight.setPosition(col * cellSize + 2, row * cellSize + 2);
            highlight.setFillColor(sf::Color(70, 255, 0, 128));
            window.draw(highlight);
        }


        sf::Text text(word.text, font, 32);
        text.setFillColor(sf::Color::Black);
        sf::FloatRect bounds = text.getLocalBounds();
        text.setOrigin(bounds.width / 2, bounds.height / 2);
        text.setPosition(x, y);
        window.draw(text);
    }

    // Draw current input
    sf::Text inputText("Input: " + currentInput, font, 32);
    inputText.setPosition(10, 610);
    inputText.setFillColor(sf::Color::White);
    window.draw(inputText);

    // Draw score
    sf::Text scoreText("Score: " + std::to_string(score), font, 32);
    scoreText.setPosition(400, 610);
    scoreText.setFillColor(sf::Color::White);
    window.draw(scoreText);

    // Draw speed
    sf::Text speedText("Speed: " + std::to_string(speed) + "s", font, 12);
    speedText.setPosition(20, 652);
    speedText.setFillColor(sf::Color::White);
    window.draw(speedText);

    if (gameOver) {
        /* sf::Text gameOverText("Game Over! Press R to restart", font, 37);
         gameOverText.setPosition(40, 300);
         gameOverText.setFillColor(sf::Color::Red);
         gameOverText.setStyle(sf::Text::Bold);*/

        sf::Text gameOverText("Game Over!", font, 37);
        gameOverText.setPosition(200, 300);
        gameOverText.setFillColor(sf::Color::Red);
        gameOverText.setStyle(sf::Text::Bold);

        sf::FloatRect textBounds = gameOverText.getLocalBounds();
        sf::RectangleShape backgroundRect;
        backgroundRect.setSize(sf::Vector2f(textBounds.width + 20, textBounds.height + 20)); // Add padding
        backgroundRect.setOrigin(textBounds.width / 2, textBounds.height / 2); // Center the rectangle
        backgroundRect.setPosition(gameOverText.getPosition().x + 95, gameOverText.getPosition().y + 15); // Position rectangle slightly offset
        backgroundRect.setFillColor(sf::Color::Black); // Set the color of the rectangle

        // Draw the background rectangle first
        window.draw(backgroundRect);
        window.draw(gameOverText);
        if (endScreen.asSeconds() <= 0) {
            window.close();
        }
    }

    window.display();
}

