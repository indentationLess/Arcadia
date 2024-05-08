#include <SFML/Graphics.hpp>
#include <functional>
#include <iostream>
#include <vector>

#include "2048.hpp"


struct MenuItem {
  sf::Text text;
  std::function<void()> action;

  MenuItem(const std::string &text, const sf::Font &font,
           std::function<void()> action)
      : text(text, font, 24) {
    this->text.setCharacterSize(24);
    this->action = action;
  }
};

int main() {
  sf::RenderWindow window(sf::VideoMode(800, 600), "Menu");
  sf::Event event;
  int selectedOption = 0;

  sf::Font font;
  if (!font.loadFromFile("includes/arial.ttf")) {
    std::cout << "Failed to load font!" << std::endl;
    return 1;
  }

  std::vector<MenuItem> menuItems;

  menuItems.emplace_back(MenuItem("Start 2048 Game", font,
                                  [&font, &event] { tw::Game::run2048Game(font,event); }));

 // menuItems.emplace_back(MenuItem("Start Pong Game", font, pong::runPongGame));

  menuItems.emplace_back(MenuItem("Minesweeper", font, [] {
    std::cout << "Starting Minesweeper Game..." << std::endl;
  }));
  menuItems.emplace_back(
      MenuItem("Exit", font, [&window]() { window.close(); }));

  for (size_t i = 0; i < menuItems.size(); ++i) {
    menuItems[i].text.setPosition(
        sf::Vector2f(window.getSize().x / 2.0f, 200.0f + i * 100.0f));
  }

  // Game loop
  while (window.isOpen()) {
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();

      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
          selectedOption--;
          if (selectedOption < 0)
            selectedOption = menuItems.size() - 1;
        } else if (event.key.code == sf::Keyboard::Down) {
          selectedOption++;
          if (selectedOption >= menuItems.size())
            selectedOption = 0;
        } else if (event.key.code == sf::Keyboard::Return) {
          menuItems[selectedOption].action();
        }
      }
    }

    // Clear the window
    window.clear();

    // Highlight the selected option
    for (size_t i = 0; i < menuItems.size(); ++i) {
      menuItems[i].text.setFillColor(i == selectedOption ? sf::Color::Red
                                                         : sf::Color::White);
    }

    // Draw the menu options
    for (const auto &item : menuItems) {
      window.draw(item.text);
    }

    // Display the window
    window.display();
  }

  return 0;
}