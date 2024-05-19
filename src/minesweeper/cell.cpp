#include "cell.hpp"

Cell::Cell() {
  this->texture.loadFromFile("includes/minesweeper_cells.png");
  this->sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
  this->sprite.setTexture(texture);
}

void Cell::change(int8_t index) {
  this->sprite.setTextureRect(sf::IntRect(16 * index, 0, 16, 16));
}

void Cell::draw(sf::RenderWindow &window, sf::Vector2i position,
                sf::Vector2i offset) {
  this->sprite.setPosition(position.x * 32 + offset.x,
                           position.y * 32 + offset.y);
  this->sprite.setScale(2, 2);
  window.draw(this->sprite);
}