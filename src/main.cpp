#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>

int main() {
  sf::RenderWindow window(sf::VideoMode(800, 600), "My Game");

  sf::Font font;
  if (!font.loadFromFile("includes/Arial.ttf"))
    return -1;

  sf::Text menuText;
  menuText.setFont(font);
  menuText.setString("Choose a game to play:");
  menuText.setPosition(100, 100);

  std::vector<sf::Text> menuOptions;
  menuOptions.push_back(sf::Text("Game 1", font));
  menuOptions.push_back(sf::Text("Game 2", font));
  menuOptions.push_back(sf::Text("Game 3", font));

  for (int i = 0; i < menuOptions.size(); i++) {
    menuOptions[i].setFont(font);
    menuOptions[i].setString("Game " + std::to_string(i + 1));
    menuOptions[i].setPosition(150, 150 + i * 50);
  }

  // Set the selected option to 0 (the first option)
  int selectedOption = 0;

  // Game loop
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();

      // Handle input for menu navigation
      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
          selectedOption--;
          if (selectedOption < 0)
            selectedOption = menuOptions.size() - 1;
        } else if (event.key.code == sf::Keyboard::Down) {
          selectedOption++;
          if (selectedOption >= menuOptions.size())
            selectedOption = 0;
        } else if (event.key.code == sf::Keyboard::Return) {
          // Launch the selected game here
          std::cout << "Game " << selectedOption + 1 << " selected!"
                    << std::endl;
        }
      }
    }

    // Draw the menu
    window.clear();
    window.draw(menuText);
    for (int i = 0; i < menuOptions.size(); i++)
      window.draw(menuOptions[i]);
    window.display();
  }

  return 0;
}