#ifndef GAME_H  
#define GAME_H  

#include <SFML/Graphics.hpp>  
#include <vector>  
#include <iostream>  
#include <sstream>  
#include "WinePlayer.h"  
#include "SwagBall.h"  
#include <SFML/Audio.hpp>  

class WineGame  
{  
private:  
  // Rename the field to avoid conflict with the class name  
  sf::RenderWindow* window;  
  sf::VideoMode videoMode;  
  sf::Event sfmlEvent;  
  sf::Music bgMusic;  
  sf::SoundBuffer grapeSoundBuffer;  
  sf::Sound grapeSound;  
  sf::SoundBuffer harmfulSoundBuffer;  
  sf::Sound harmfulSound;  
  sf::Text winText;  
  sf::Text loseText;  

  // Game logic 
  bool GameWon;  
  bool GameOver;  
  bool gameLost;  
  bool musicPlaying;  
  bool endGame;  
  int spawnTimerMax;  
  float spawnTimer;  
  int maxSwagBalls;  
  int points;  
  int damagingItems;  

  // WinePlayer  
  WinePlayer WinePlayer;  

  sf::Clock gameClock;  
  float timeLimit = 60.f; // 60 seconds to win  
  sf::Text timerText;  

  // SwagBalls  
  std::vector<SwagBall> swagBalls;  

  // Fonts & Text  
  sf::Font font;  
  sf::Text guiText;  
  sf::Text endGameText;  

  // Private functions  
  void initVariables();  
  void initGame();  
  void initWindow();
  void initFonts();  
  void initText();  
  void pollEvents();  
  void spawnSwagBalls();  
  const int randBallType() const;  
  void updateWinePlayer();  
  void updateCollision();  
  void updateGui();  

public:  
  // Constructors & Destructors  
  WineGame();  
  virtual ~WineGame();  

  // Functions  
  bool getGameWin();
  void initSounds();  
  const bool& getEndGame() const;  
  const bool running() const;  
  void update();  
  void render();  
  void renderGui(sf::RenderTarget* target);  
};  

#endif
