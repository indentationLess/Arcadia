#include "game.hpp"
#include <iostream>

int main() {
  Game game;
  // Game loop
  while (game.window.isOpen()) {
    sf::Event event;
    while (game.window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        game.window.close();

      // Handle input for menu navigation
      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
          game.selectedOption--;
          if (game.selectedOption < 0)
            game.selectedOption = game.menuOptions.size() - 1;
        } else if (event.key.code == sf::Keyboard::Down) {
          game.selectedOption++;
          if (game.selectedOption >= game.menuOptions.size())
            game.selectedOption = 0;
        } else if (event.key.code == sf::Keyboard::Return) {
          // Launch the selected game here
          std::cout << "Game " << game.selectedOption + 1 << " selected!"
                    << std::endl;
        }
      }
    }

    // Draw the menu
    game.window.clear();
    game.window.draw(game.menuText);
    for (int i = 0; i < game.menuOptions.size(); i++)
      game.window.draw(game.menuOptions[i]);
    game.window.display();
  }

  return 0;
}