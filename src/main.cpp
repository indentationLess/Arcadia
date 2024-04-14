#include "2048.hpp"
#include "game.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
  Game game;
  sf::RenderWindow window(sf::VideoMode(800, 600), "Menu");
  sf::Event event;
  int selectedOption = 0;

  // Create menu options
  std::vector<sf::Text> menuOptions;
  sf::Font font;
  if (!font.loadFromFile("includes/arial.ttf")) {
    std::cout << "Failed to load font!" << std::endl;
    return 1;
  }

  sf::Text option1("Start 2048 Game", font, 24);
  sf::Text option2("Exit", font, 24);
  menuOptions.push_back(option1);
  menuOptions.push_back(option2);

  // Position the menu options
  for (size_t i = 0; i < menuOptions.size(); i++) {
    sf::FloatRect textRect = menuOptions[i].getLocalBounds();
    menuOptions[i].setOrigin(textRect.left + textRect.width / 2,
                             textRect.top + textRect.height / 2);
    menuOptions[i].setPosition(
        sf::Vector2f(window.getSize().x / 2.0f, (i + 1) * 100.0f));
  }

  // Game loop
  while (window.isOpen()) {
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();

      // Handle input for menu navigation
      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
          selectedOption--;
          std::cout << "user pressed the up key" << std::endl;
          if (selectedOption < 0)
            selectedOption = menuOptions.size() - 1;
        } else if (event.key.code == sf::Keyboard::Down) {
          selectedOption++;
          std::cout << "user pressed the down key" << std::endl;
          if (selectedOption >= static_cast<int>(menuOptions.size()))
            selectedOption = 0;
        } else if (event.key.code == sf::Keyboard::Return) {
          // Launch the selected game here
          if (selectedOption == 0) {
            sf::RenderWindow gameWindow(sf::VideoMode(600, 600), "2048",
                                        sf::Style::Titlebar | sf::Style::Close);
            sf::Event e;
            gameWindow.setKeyRepeatEnabled(false);

            tw::Game game(gameWindow.getSize().x, gameWindow.getSize().y);

            while (gameWindow.isOpen()) {
              while (gameWindow.pollEvent(e)) {
                if (e.type == sf::Event::Closed)
                  gameWindow.close();
                game.OnEvent(e);
              }

              game.Update();

              gameWindow.clear(sf::Color(187, 173, 160));
              game.Render(gameWindow);
              gameWindow.display();
            }
          } else if (selectedOption == 1) {
            window.close(); // Exit the menu
          }
        }
      }
    }

    // Draw the menu
    window.clear();
    for (size_t i = 0; i < menuOptions.size(); i++)
      window.draw(menuOptions[i]);
    window.display();
  }

  return 0;
}