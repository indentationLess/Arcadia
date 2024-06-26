#include "pong.hpp"
#include "../audio.hpp"
#include "aibat.hpp"
#include "ball.hpp"
#include "bat.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
namespace pong {

void runPongGame() {
  sf::RenderWindow window(sf::VideoMode(800, 600), "Pong Game");
  Bat bat(300, 500);
  AIBat aiBat(300, 100);
  Ball ball(400, 250);
  int player_score = 0;
  int ai_score = 0;
  sf::Font font;
  font.loadFromFile("includes/ClearSans.ttf");
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

    sf::Text playerScoreText("Player: " + std::to_string(player_score), font,
                             20);
    playerScoreText.setPosition(20.f, 20.f);
    window.draw(playerScoreText);

    sf::Text aiScoreText("AI: " + std::to_string(ai_score), font, 20);
    aiScoreText.setPosition(
        window.getSize().x - aiScoreText.getGlobalBounds().width - 20.f, 20.f);
    window.draw(aiScoreText);

    window.display();

    if (ball.getposition().left <= 0 ||
        ball.getposition().left + ball.getposition().width >= 800) {
      ball.reboundSides();
    }
    if (ball.getposition().top <= 0) {
      ball.passTop();
      player_score += 1;
    }
    if (ball.getposition().top + ball.getposition().height >= 600) {
      ball.passBottom();
      ai_score += 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
      bat.moveBatLeft();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
      bat.moveBatRight();
    }
    if (ball.getBallFloatRect().intersects(bat.getBatFloatRect()) ||
        ball.getBallFloatRect().intersects(aiBat.getAIBatFloatRect())) {
      ball.reboundBatorAI();
      static std::unique_ptr<SoundEffect> moveSound =
          std::make_unique<SoundEffect>(
              "includes/sfx/jixaw-metal-pipe-falling-sound.mp3");
      moveSound->play();
    }
    if (ball.getcords().x > aiBat.getAIBatPosition().x &&
        aiBat.getAIBatPosition().x + aiBat.getAIBatFloatRect().width < 800) {
      aiBat.moveAIBatRight();
    }
    if (ball.getcords().x < aiBat.getAIBatPosition().x &&
        aiBat.getAIBatPosition().x > 0) {
      aiBat.moveAIBatLeft();
      if (player_score == 15) {
        ball.stop();
        sf::Text Win_Screen("YOU WIN!!!!!", font, 100);
        Win_Screen.setPosition(400 - Win_Screen.getGlobalBounds().width / 2,
                               300);
        Win_Screen.setFillColor(sf::Color::Green);
        window.draw(Win_Screen);
        window.display();
      }
      if (ai_score == 15) {
        ball.stop();
        sf::Text Lose_Screen("YOU LOSE!!", font, 100);
        Lose_Screen.setPosition(400 - Lose_Screen.getGlobalBounds().width / 2,
                                300);
        Lose_Screen.setFillColor(sf::Color::Red);
        window.draw(Lose_Screen);
        window.display();
      }
    }
  }
}

} // namespace pong