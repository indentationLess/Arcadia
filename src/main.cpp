#include <SFML/Graphics.hpp>
#include <iostream>

#include "2048.hpp"
#include "pong.hpp"

int main() {
  sf::RenderWindow window(sf::VideoMode(800, 600), "Menu");
  sf::Event event;
  int selectedOption = 0;

  // Create menu options
  sf::Font font;
  if (!font.loadFromFile("includes/arial.ttf")) {
    std::cout << "Failed to load font!" << std::endl;
    return 1;
  }

  sf::Text option1("Start 2048 Game", font, 24);
  sf::Text option2("Start Pong Game", font, 24);
  sf::Text option3("Minesweeper", font, 24);
  sf::Text option4("Exit", font, 24);

  // Position the menu options
  option1.setPosition(sf::Vector2f(window.getSize().x / 2.0f, 200.0f));
  option2.setPosition(sf::Vector2f(window.getSize().x / 2.0f, 300.0f));
  option3.setPosition(sf::Vector2f(window.getSize().x / 2.0f, 400.0f));
  option4.setPosition(sf::Vector2f(window.getSize().x / 2.0f, 500.0f));

  // Game loop
  while (window.isOpen()) {
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();

      // Handle input for menu navigation
      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
          selectedOption--;
          if (selectedOption < 0)
            selectedOption = 3;
        } else if (event.key.code == sf::Keyboard::Down) {
          selectedOption++;
          if (selectedOption > 3)
            selectedOption = 0;
        } else if (event.key.code == sf::Keyboard::Return) {
          // Launch the selected game here
          if (selectedOption == 0) {
            std::cout << "Starting 2048 Game..." << std::endl;
            sf::RenderWindow gameWindow(sf::VideoMode(500, 600), "2048 Game");
            tw::Game game(gameWindow.getSize().x, gameWindow.getSize().y);

            while (gameWindow.isOpen()) {
              while (gameWindow.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                  gameWindow.close();
                game.OnEvent(event);
              }

              game.Update();

              gameWindow.clear(sf::Color(187, 173, 160));
              game.Render(gameWindow);
              gameWindow.display();
            }
          } else if (selectedOption == 1) {
            std::cout << "Starting Pong Game..." << std::endl;
            pong::runPongGame();
          } 
            else if (selectedOption == 2) {
             std::cout << "Starting Minesweeper Game..." << std::endl;

          }            
            else if (selectedOption == 3) {
            std::cout << "Exiting..." << std::endl;
            window.close();
          }
        }
      }
    }

    // Clear the window
    window.clear();

    // Highlight the selected option
    if (selectedOption == 0) {
      option1.setFillColor(sf::Color::Red);
      option2.setFillColor(sf::Color::White);
      option3.setFillColor(sf::Color::White);
      option4.setFillColor(sf::Color::White);
    } else if (selectedOption == 1) {
      option1.setFillColor(sf::Color::White);
      option2.setFillColor(sf::Color::Red);
      option3.setFillColor(sf::Color::White);
      option4.setFillColor(sf::Color::White);
    } else if (selectedOption == 2) {
      option1.setFillColor(sf::Color::White);
      option2.setFillColor(sf::Color::White);
      option3.setFillColor(sf::Color::Red);
      option4.setFillColor(sf::Color::White);
    }
      else {
      option1.setFillColor(sf::Color::White);
      option2.setFillColor(sf::Color::White);
      option3.setFillColor(sf::Color::White);
      option4.setFillColor(sf::Color::Red);
    }

    // Draw the menu options
    window.draw(option1);
    window.draw(option2);
    window.draw(option3);
    window.draw(option4);

    // Display the window
    window.display();
  }

  return 0;
}