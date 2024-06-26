#pragma once
#include "../settings.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>

using namespace sf;

namespace tw {
class Game {
public:
  Game(int w, int h);
  void OnEvent(sf::Event e);
  void Update();
  void Render(sf::RenderTarget &tgt);

  void Spawn();
  void Reset();
  static void run2048Game(sf::Font &font, sf::Event &event);

private:
  int tileSize;
  char map[FIELD_WIDTH][FIELD_HEIGHT] = {0};
  char tempMap[FIELD_WIDTH][FIELD_HEIGHT] = {0};
  sf::Clock animClock;
  bool animState;

  sf::Font font;

  std::vector<std::pair<std::pair<sf::Vector2i, sf::Vector2i>, char>> moves;

  sf::Color getTileColor(int tile);
  sf::Color getTextColor(int tile);
  std::string getText(int tile);
  int getTextSize(char tile);
  void move(char dirX, char dirY);
  void applyMove(sf::Vector2i from, sf::Vector2i to, int dx, int dy);
};

class TileUtils {
public:
  static sf::Color getTileColor(int tile);
  static sf::Color getTextColor(int tile);
  static std::string getText(int tile);
  static int getTextSize(char tile);
};
} // namespace tw