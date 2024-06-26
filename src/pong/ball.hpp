#include <SFML/Graphics.hpp>

class Ball {
private:
  sf::RectangleShape BallObject;
  sf::Vector2f ballPosition;
  double ballVelocityX = 0.15f;
  double ballVelocityY = 0.1f;

public:
  Ball(double x, double y);
  sf::RectangleShape getBallObject();
  sf::FloatRect getBallFloatRect();
  void reboundSides();
  void passTop();
  void passBottom();
  void intersectBat();
  void intersectAIBat();
  void reboundBatorAI();
  void update();
  void stop();
  void go();
  sf::FloatRect getposition();
  sf::Vector2f getcords();
};