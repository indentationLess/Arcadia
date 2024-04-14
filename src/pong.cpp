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
  }
}

} // namespace pong