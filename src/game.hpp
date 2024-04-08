#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

// for game engine
class Game {
private:
  // initializing variables

public:
  // constructors and destructors
  Game();
  virtual ~Game();

  // window
  sf::RenderWindow window;
  sf::Font font;
  sf::Text menuText;
  std::vector<sf::Text> menuOptions;
  int selectedOption;

  // private func
  void initVar();
  void initWindow();
  // functions
  void update();
  void render();
  void displayImage(sf::RenderWindow &window, const std::string &filename);
};