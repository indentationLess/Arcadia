#include "pong.hpp"
#include "aibat.hpp"
#include "ball.hpp"
#include "bat.hpp"
#include <SFML/Graphics.hpp>

namespace pong {

void runPongGame() {
  sf::RenderWindow window(sf::VideoMode(800, 600), "Pong Game");
  Bat bat(400, 500);
  AIBat aiBat(400, 100);
  Ball ball(400, 250);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    bat.update();
    aiBat.update();
    ball.update();

    window.clear();
    window.draw(bat.getBatObject());
    window.draw(aiBat.getAIBatObject());
    window.draw(ball.getBallObject());
    window.display();
    if (ball.getposition().left <= 0 || ball.getposition().left + ball.getposition().width >= 800){
      ball.reboundSides();
    }
    if (ball.getposition().top <= 0){
      ball.passTop();
    }
    if (ball.getposition().top + ball.getposition().height >= 600){
      ball.passBottom();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
      bat.moveBatLeft();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
      bat.moveBatRight();
    }
    if (ball.getBallFloatRect().intersects(bat.getBatFloatRect()) || ball.getBallFloatRect().intersects(aiBat.getAIBatFloatRect())){
      ball.reboundBatorAI();
    }
    if (ball.getcords().x - aiBat.getAIBatPosition().x > 35 && aiBat.getAIBatPosition().x + aiBat.getAIBatFloatRect().width < 800 ) 
    {
      aiBat.moveAIBatRight();
    }
    if (aiBat.getAIBatPosition().x - ball.getcords().x > 35 && aiBat.getAIBatPosition().x > 0)
    {
      aiBat.moveAIBatLeft();
    }
  }
}

} // namespace pong