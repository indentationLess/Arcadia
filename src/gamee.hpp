#pragma once
#include "settings.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Game {
public:
  virtual ~Game() {}
  virtual void start() = 0;
  virtual void run(sf::Font &font, sf::Event &event);

protected:
  sf::RenderWindow window;
};

class TwentyFourtyEightGame : public Game {
public:
  TwentyFourtyEightGame(int w, int h);
  void start() override;
  void run(sf::Font &font, sf::Event &event) override;
  void OnEvent(sf::Event e);
  void Update();
  void Render(sf::RenderTarget &tgt);
  void Spawn();
  void Reset();
  void move(char dirX, char dirY);
  void applyMove(sf::Vector2i from, sf::Vector2i to, int dx, int dy);

private:
  int tileSize;
  char map[tw::FIELD_WIDTH][tw::FIELD_HEIGHT] = {0};
  char tempMap[tw::FIELD_WIDTH][tw::FIELD_HEIGHT] = {0};
  sf::Clock animClock;
  bool animState;
  sf::Vector2i fMargin;
  sf::Font font;

  std::vector<std::pair<std::pair<sf::Vector2i, sf::Vector2i>, char>> moves;

  sf::Color getTileColor(int tile);
  sf::Color getTextColor(int tile);
  std::string getText(int tile);
  int getTextSize(char tile);
};
class MenuGame : public Game {
public:
  MenuGame();
  void start() override;
  void run(sf::Font &font, sf::Event &event) override;
  sf::RenderWindow window;
  sf::Font font;
  sf::Text menuText;
  int selectedOption;
  std::vector<sf::Text> menuOptions;

private:
  void initVar();
  void initWindow();
  void update();
  void render();
  void displayImage(sf::RenderWindow &window, const std::string &filename);
};
