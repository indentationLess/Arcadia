
#include "../settings.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>


class Snake {
public:
  Snake();
  void update();
  void grow();
  void changeDirection(sf::Keyboard::Key keyCode);
  bool checkCollision();
  void render(sf::RenderWindow &window);
  int getSpeed() const;
  sf::Vector2i getHeadPosition() const; // Add this method
private:
  enum Direction { None, Up, Down, Left, Right };
  struct Segment {
    int x, y;
    Segment(int _x, int _y) : x(_x), y(_y) {}
  };

  std::vector<Segment> segments;
  Direction direction;
  int speed;
};

sf::Vector2i Snake::getHeadPosition() const {
  return sf::Vector2i(segments[0].x, segments[0].y);
}

int Snake::getSpeed() const { return speed; }

Snake::Snake() {
  segments.push_back(
      Segment(snake::WINDOW_WIDTH / 2, snake::WINDOW_HEIGHT / 2));
  direction = None;
  speed = snake::INITIAL_SNAKE_SPEED;
}

void Snake::update() {
  if (direction != None) {
    int newX = segments[0].x;
    int newY = segments[0].y;
    if (direction == Up)
      newY -= snake::CELL_SIZE;
    else if (direction == Down)
      newY += snake::CELL_SIZE;
    else if (direction == Left)
      newX -= snake::CELL_SIZE;
    else if (direction == Right)
      newX += snake::CELL_SIZE;

    segments.insert(segments.begin(), Segment(newX, newY));
    segments.pop_back();
  }
}

void Snake::grow() {
  int lastX = segments.back().x;
  int lastY = segments.back().y;
  segments.push_back(Segment(lastX, lastY));
}

void Snake::changeDirection(sf::Keyboard::Key keyCode) {
  if ((keyCode == sf::Keyboard::Up && direction != Down) ||
      (keyCode == sf::Keyboard::Down && direction != Up) ||
      (keyCode == sf::Keyboard::Left && direction != Right) ||
      (keyCode == sf::Keyboard::Right && direction != Left)) {
    if (keyCode == sf::Keyboard::Up)
      direction = Up;
    else if (keyCode == sf::Keyboard::Down)
      direction = Down;
    else if (keyCode == sf::Keyboard::Left)
      direction = Left;
    else if (keyCode == sf::Keyboard::Right)
      direction = Right;
  }
}

bool Snake::checkCollision() {
  int headX = segments[0].x;
  int headY = segments[0].y;
  if (headX < 0 || headX >= snake::WINDOW_WIDTH || headY < 0 ||
      headY >= snake::WINDOW_HEIGHT)
    return true;

  for (size_t i = 1; i < segments.size(); ++i) {
    if (headX == segments[i].x && headY == segments[i].y)
      return true;
  }

  return false;
}

void Snake::render(sf::RenderWindow &window) {
  for (const auto &segment : segments) {
    sf::RectangleShape segmentShape(
        sf::Vector2f(snake::CELL_SIZE, snake::CELL_SIZE));
    segmentShape.setPosition(segment.x, segment.y);
    segmentShape.setFillColor(sf::Color::Green);
    window.draw(segmentShape);
  }
}

class Food {
public:
  Food();
  void spawn(int maxWidth, int maxHeight);
  sf::Vector2i getPosition() const;
  void render(sf::RenderWindow &window); // Remove 'Food::'

private:
  sf::Vector2i position;
  sf::RectangleShape shape;
};

void Food::render(sf::RenderWindow &window) { // Remove 'Food::'
  window.draw(shape);
}

Food::Food() {
  shape.setSize(sf::Vector2f(snake::CELL_SIZE, snake::CELL_SIZE));
  shape.setFillColor(sf::Color::Yellow);
}

void Food::spawn(int maxWidth, int maxHeight) {
  int x = (rand() % (maxWidth / snake::CELL_SIZE)) * snake::CELL_SIZE;
  int y = (rand() % (maxHeight / snake::CELL_SIZE)) * snake::CELL_SIZE;
  position = sf::Vector2i(x, y);
  shape.setPosition(static_cast<float>(x),
                    static_cast<float>(y)); // Update the shape's position
}

sf::Vector2i Food::getPosition() const { return position; }

class snakeGame {
public:
  snakeGame();
  void run();

private:
  sf::RenderWindow window;
  Snake snake;
  sf::Clock clock;
  sf::Font font;
  sf::Text gameOverText;
  bool gameOver;

  void handleEvents();
  void update();
  void render();

  Food food;

  void spawnFood();
};

snakeGame::snakeGame()
    : window(sf::VideoMode(snake::WINDOW_WIDTH, snake::WINDOW_HEIGHT), "Snake"),
      gameOver(false) {
  window.setFramerateLimit(30);
  if (!font.loadFromFile("ClearSans.ttf")) {
    // Handle error
  }
  gameOverText.setFont(font);
  gameOverText.setCharacterSize(40);
  gameOverText.setFillColor(sf::Color::Red);
  gameOverText.setString("Game Over!");
  gameOverText.setPosition(snake::WINDOW_WIDTH / 2 - 100,
                           snake::WINDOW_HEIGHT / 2 - 20);
  spawnFood();
}

void snakeGame::run() {
  while (window.isOpen()) {
    handleEvents();
    update();
    render();
  }
}

void snakeGame::handleEvents() {
  sf::Event event;
  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      window.close();
    } else if (event.type == sf::Event::KeyPressed) {
      snake.changeDirection(event.key.code);
    }
  }
}

void snakeGame::spawnFood() {
  food.spawn(snake::WINDOW_WIDTH, snake::WINDOW_HEIGHT);
}

void snakeGame::update() {
  if (!gameOver) {
    sf::Time elapsed = clock.restart();
    float dt = elapsed.asSeconds();
    while (dt > 0.0f) {
      float step = std::min(dt, 1.0f / snake.getSpeed());
      snake.update();
      dt -= step;
    }
    if (snake.checkCollision()) {
      gameOver = true;
    }

    if (snake.getHeadPosition().x == food.getPosition().x &&
        snake.getHeadPosition().y == food.getPosition().y) {
      snake.grow();
      spawnFood();
    }
  }
}

void snakeGame::render() {
  window.clear(sf::Color::Black);
  snake.render(window);
  food.render(window);
  if (gameOver) {
    window.draw(gameOverText);
  }
  window.display();
}

