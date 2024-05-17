#include "aibat.hpp"

AIBat::AIBat(double x, double y) {
  aiBatPosition.x = x;
  aiBatPosition.y = y;
  aiBatObject.setSize(sf::Vector2f(150, 10));
  aiBatObject.setPosition(aiBatPosition);
}

sf::Vector2f AIBat::getAIBatPosition() { return aiBatPosition; }

sf::RectangleShape AIBat::getAIBatObject() { return aiBatObject; }

sf::FloatRect AIBat::getAIBatFloatRect() {
  return aiBatObject.getGlobalBounds();
}

void AIBat::moveAIBatLeft() { aiBatPosition.x -= aiBatSpeed; }

void AIBat::moveAIBatRight() { aiBatPosition.x += aiBatSpeed; }

void AIBat::update() { aiBatObject.setPosition(aiBatPosition); }

void AIBat::AIBatSpeedReverse() { aiBatSpeed *= -1; }