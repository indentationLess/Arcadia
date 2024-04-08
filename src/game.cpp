#include "game.hpp"
#include <iostream>

// public func
Game::Game() {
  initVar();
  initWindow();
}

Game::~Game() {}

// private func
void Game::initVar() {
  // initialize variables here
  selectedOption = 0;
}

void Game::initWindow() {
  // create the window
  window.create(sf::VideoMode(800, 600), "My Game");

  // set the framerate limit
  window.setFramerateLimit(60);

  // load the font
  font.loadFromFile("includes/Arial.ttf");

  // set the menu text
  menuText.setFont(font);
  menuText.setString("Choose a game to play:");
  menuText.setPosition(100, 100);

  // initialize the menu options
  menuOptions.clear();
  menuOptions.push_back(sf::Text("Game 1", font));
  menuOptions.push_back(sf::Text("Game 2", font));
  menuOptions.push_back(sf::Text("Game 3", font));
  for (size_t i = 0; i < menuOptions.size(); i++) {
    menuOptions[i].setFont(font);
    menuOptions[i].setString("Game " + std::to_string(i + 1));
    menuOptions[i].setPosition(150, 150 + i * 50);
  }
}

void Game::update() {}

void Game::render() {
  // Draw the menu
  window.clear();
  window.draw(menuText);
  for (size_t i = 0; i < menuOptions.size(); i++) {
    window.draw(menuOptions[i]);
  }
  window.display();
}

void Game::displayImage(sf::RenderWindow &window, const std::string &filename) {
  sf::Texture texture;
  if (!texture.loadFromFile(filename)) {
    std::cerr << "Failed to load image!" << std::endl;
    return;
  }

  sf::Vector2f imageSize(texture.getSize());
  sf::Sprite sprite(texture);
  sf::Vector2f windowSize(window.getSize());
  sf::Vector2f center((windowSize.x - imageSize.x) / 2,
                      (windowSize.y - imageSize.y) / 2);

  sprite.setPosition(center);
  window.clear();
  window.draw(sprite);
  window.display();

  sf::sleep(sf::seconds(1.0f));

  window.clear();
}