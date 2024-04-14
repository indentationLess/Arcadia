#include "ball.hpp"

Ball::Ball(double x, double y) {
  ballPosition.x = x;
  ballPosition.y = y;
  BallObject.setSize(sf::Vector2f(10, 10));
  BallObject.setPosition(ballPosition);
  BallObject.setFillColor(sf::Color::White);
}

sf::RectangleShape Ball::getBallObject() { return BallObject; }
sf::FloatRect Ball::getBallFloatRect() { return BallObject.getGlobalBounds(); }

void Ball::reboundSides() { ballVelocityX = -ballVelocityX; }

void Ball::passTop() { ballVelocityY = -ballVelocityY; }

void Ball::passBottom() { ballVelocityY = -ballVelocityY; }

void Ball::intersectBat() { ballVelocityY = -ballVelocityY; }

void Ball::intersectAIBat() { ballVelocityY = -ballVelocityY; }

void Ball::reboundBatorAI() { ballVelocityX = -ballVelocityX; }

void Ball::update() {
  ballPosition.x += ballVelocityX;
  ballPosition.y += ballVelocityY;
  BallObject.setPosition(ballPosition);
}

void Ball::stop() {
  ballVelocityX = 0;
  ballVelocityY = 0;
}

void Ball::go() {
  ballVelocityX = 0.5f;
  ballVelocityY = 0.5f;
}