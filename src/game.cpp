#include "game.hpp"
#include <iostream>

// public func
Game::Game() { initVar(); }

Game::~Game() {}

// private func
void Game::initVar() {
  // initialize variables here
  selectedOption = 0;
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
