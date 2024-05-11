#include "bat.hpp"

Bat::Bat(double x, double y) {
  batPosition.x = x;
  batPosition.y = y;
  BatObject.setSize(sf::Vector2f(150, 10));
  BatObject.setPosition(batPosition);
}

sf::Vector2f Bat::getBatPosition() { return batPosition; }

sf::RectangleShape Bat::getBatObject() { return BatObject; }

sf::FloatRect Bat::getBatFloatRect() { return BatObject.getGlobalBounds(); }

void Bat::moveBatLeft() { 
  if (batPosition.x > 0){
  batPosition.x -= batSpeed;} }

void Bat::moveBatRight() { 
  if (batPosition.x < 650)
  {batPosition.x += batSpeed;} }

void Bat::update() { BatObject.setPosition(batPosition); }