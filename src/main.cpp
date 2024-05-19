#include "TwentyFourtyEight/2048.hpp"
#include "audio.hpp"
#include "minesweeper/minesweeper.hpp"
#include "pong/pong.hpp"
#include "snake/snake.hpp"
#include <SFML/Graphics.hpp>
#include <chrono>
#include <functional>
#include <iostream>
#include <memory>
#include <vector>
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
  std::chrono::time_point<std::chrono::steady_clock> previous_time;
  sf::Font font;
  if (!font.loadFromFile("includes/ClearSans.ttf")) {
    std::cout << "Failed to load font!" << std::endl;
    return 1;
  }

  // Load the logo texture
  sf::Texture logoTexture;
  if (!logoTexture.loadFromFile("includes/logo.png")) {
    return -1; // Error loading logo
  }
  sf::Sprite logoSprite;
  logoSprite.setTexture(logoTexture);

  // Scale the logo to fit nicely within the window
  float desiredLogoWidth = 800.0f; // Adjust this value as needed
  float scale = desiredLogoWidth / logoTexture.getSize().x;
  logoSprite.setScale(scale, scale);
  logoSprite.setPosition(
      (window.getSize().x - logoSprite.getGlobalBounds().width) / 2.0f, 20.0f);

  // Define the menu items
  std::vector<MenuItem> menuItems;

  menuItems.emplace_back(MenuItem("Start 2048 Game", font, [&font, &event] {
    tw::Game::run2048Game(font, event);
  }));
  menuItems.emplace_back(MenuItem("Start Snake Game", font, [&]() {
    snakeGame game;
    game.run();
  }));
  menuItems.emplace_back(MenuItem("Start Pong Game", font, pong::runPongGame));
  menuItems.emplace_back(MenuItem("Minesweeper", font, [] {
    std::cout << "Starting Minesweeper Game..." << std::endl;
    minesweeper::runMinesweeperGame();
  }));
  menuItems.emplace_back(
      MenuItem("Exit", font, [&window]() { window.close(); }));

  // Calculate the total height of the menu items
  float totalMenuHeight = menuItems.size() * 50.0f;
  float startY = window.getSize().y - totalMenuHeight -
                 50.0f; // Adjust 50.0f as needed for padding from the bottom
  for (size_t i = 0; i < menuItems.size(); ++i) {
    sf::FloatRect textRect = menuItems[i].text.getLocalBounds();
    menuItems[i].text.setOrigin(textRect.left + textRect.width / 2.0f,
                                textRect.top + textRect.height / 2.0f);
    menuItems[i].text.setPosition(
        sf::Vector2f(window.getSize().x / 2.0f,
                     startY + i * 50.0f + textRect.height / 2.0f));
  }
  std::unique_ptr<SoundEffect> hover =
      std::make_unique<SoundEffect>("includes/sfx/hover.wav");
  static std::unique_ptr<SoundEffect> choose =
      std::make_unique<SoundEffect>("includes/sfx/selected.wav");
  // Game loop
  while (window.isOpen()) {
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
          selectedOption--;
          hover->play();
          if (selectedOption < 0)
            selectedOption = menuItems.size() - 1;
        } else if (event.key.code == sf::Keyboard::Down) {
          selectedOption++;
          hover->play();
          if (selectedOption >= menuItems.size())
            selectedOption = 0;
        } else if (event.key.code == sf::Keyboard::Return) {
          choose->play();
          menuItems[selectedOption].action();
        }
      }
    }

    // Clear the window
    window.clear();
    window.draw(logoSprite);
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
