#pragma once
#include <SFML/System/Vector2.hpp>
#include <cstdint>

namespace tw {
const int FIELD_WIDTH = 4;
const int FIELD_HEIGHT = 4;
const int FIELD_MARGIN = 40;
const int TILE_MARGIN = 20;
const float ANIMATION_DURATION = 0.1f;
} // namespace tw
namespace snake {
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int CELL_SIZE = 20;
const int INITIAL_SNAKE_LENGTH = 3;
const int INITIAL_SNAKE_SPEED = 1;
} // namespace snake

namespace minesweeper {
const unsigned short CELLS_SIZE = 14;
const unsigned short CELLS_BOMBS = 24;
const sf::Vector2i CELLS_OFFSET =
    sf::Vector2i(202, 16); // The position where the grid of cells will generate

} // namespace minesweeper