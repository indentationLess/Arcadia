#include "../settings.h"
#include "cell.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>

std::vector<std::vector<int8_t>>
    CELLS_DATA(minesweeper::CELLS_SIZE,
               std::vector<int8_t>(minesweeper::CELLS_SIZE, 0));
std::vector<std::vector<int8_t>>
    CELLS_SDATA(minesweeper::CELLS_SIZE,
                std::vector<int8_t>(minesweeper::CELLS_SIZE, 0));

namespace minesweeper {

void initializeBombs() {
  srand(static_cast<unsigned>(time(0)));
  int bombsPlaced = 0;
  while (bombsPlaced < minesweeper::CELLS_BOMBS) {
    int x = rand() % minesweeper::CELLS_SIZE;
    int y = rand() % minesweeper::CELLS_SIZE;
    if (CELLS_DATA[x][y] == 9)
      continue;
    CELLS_DATA[x][y] = 9;
    bombsPlaced++;
  }
}

void initializeNumbers() {
  for (int x = 0; x < minesweeper::CELLS_SIZE; ++x) {
    for (int y = 0; y < minesweeper::CELLS_SIZE; ++y) {
      if (CELLS_DATA[x][y] == 9)
        continue;
      int count = 0;
      for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
          if (x + dx >= 0 && x + dx < minesweeper::CELLS_SIZE && y + dy >= 0 &&
              y + dy < minesweeper::CELLS_SIZE &&
              CELLS_DATA[x + dx][y + dy] == 9) {
            count++;
          }
        }
      }
      CELLS_DATA[x][y] = count;
    }
  }
}

sf::Vector2i getCellPosition(const sf::RenderWindow &window) {
  auto [mouseX, mouseY] = sf::Mouse::getPosition(window);
  int x = static_cast<int>(
      std::floor((mouseX - minesweeper::CELLS_OFFSET.x) / 32.0));
  int y = static_cast<int>(
      std::floor((mouseY - minesweeper::CELLS_OFFSET.y) / 32.0));
  return {x, y};
}

bool isWithinBounds(const sf::Vector2i &pos) {
  return pos.x >= 0 && pos.x < minesweeper::CELLS_SIZE && pos.y >= 0 &&
         pos.y < minesweeper::CELLS_SIZE;
}

void floodFill(const sf::Vector2i &start) {
  std::vector<sf::Vector2i> queue = {start};
  while (!queue.empty()) {
    auto [x, y] = queue.front();
    queue.erase(queue.begin());
    for (int dx = -1; dx <= 1; ++dx) {
      for (int dy = -1; dy <= 1; ++dy) {
        int nx = x + dx;
        int ny = y + dy;
        if (nx >= 0 && nx < minesweeper::CELLS_SIZE && ny >= 0 &&
            ny < minesweeper::CELLS_SIZE && CELLS_SDATA[nx][ny] != -1 &&
            CELLS_DATA[nx][ny] != 9) {
          CELLS_SDATA[nx][ny] = -1;
          if (CELLS_DATA[nx][ny] == 0) {
            queue.push_back({nx, ny});
          }
        }
      }
    }
  }
}

void revealBombs() {
  for (int x = 0; x < minesweeper::CELLS_SIZE; ++x) {
    for (int y = 0; y < minesweeper::CELLS_SIZE; ++y) {
      if (CELLS_DATA[x][y] == 9) {
        CELLS_SDATA[x][y] = -1;
      }
    }
  }
}

void runMinesweeperGame() {
  sf::RenderWindow window(sf::VideoMode(852, 480), "Minesweeper",
                          sf::Style::Titlebar | sf::Style::Close);
  window.setVerticalSyncEnabled(true);

  Cell cell;
  initializeBombs();
  initializeNumbers();

  bool gameOver = false;

  while (window.isOpen()) {
    sf::Vector2i cellPosition = getCellPosition(window);
    bool cellBounds = isWithinBounds(cellPosition);

    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      } else if (!gameOver && event.type == sf::Event::MouseButtonPressed &&
                 cellBounds) {
        int8_t &cellLocation = CELLS_DATA[cellPosition.x][cellPosition.y];
        int8_t &cellSLocation = CELLS_SDATA[cellPosition.x][cellPosition.y];

        if (event.mouseButton.button == sf::Mouse::Left) {
          if (cellSLocation == 0) {
            cellSLocation = -1;
            if (cellLocation == 9) {
              revealBombs();
              gameOver = true;
            } else if (cellLocation == 0) {
              floodFill(cellPosition);
            }
          }
        } else if (event.mouseButton.button == sf::Mouse::Right) {
          cellSLocation = (cellSLocation == 1) ? 0 : 1;
        }
      }
    }

    for (int x = 0; x < minesweeper::CELLS_SIZE; ++x) {
      for (int y = 0; y < minesweeper::CELLS_SIZE; ++y) {
        switch (CELLS_SDATA[x][y]) {
        case 0:
          cell.change(10);
          break;
        case 1:
          cell.change(11);
          break;
        default:
          cell.change(CELLS_DATA[x][y]);
        }
        cell.draw(window, sf::Vector2i(x, y), minesweeper::CELLS_OFFSET);
      }
    }

    if (cellBounds) {
      int8_t &cellSLocation = CELLS_SDATA[cellPosition.x][cellPosition.y];
      int8_t &cellLocation = CELLS_DATA[cellPosition.x][cellPosition.y];
      if ((cellSLocation == -1 && cellLocation != 0) || (cellSLocation != -1)) {
        sf::RectangleShape highlight(sf::Vector2f(32, 32));
        highlight.setFillColor(sf::Color(255, 255, 255, 30));
        highlight.setPosition(cellPosition.x * 32 + minesweeper::CELLS_OFFSET.x,
                              cellPosition.y * 32 +
                                  minesweeper::CELLS_OFFSET.y);
        window.draw(highlight);
      }
    }

    window.display();
    window.clear();
  }
}
} // namespace minesweeper
