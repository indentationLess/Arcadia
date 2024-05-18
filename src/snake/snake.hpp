
#include "../scoreRenderer.hpp"
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

inline sf::Vector2i Snake::getHeadPosition() const {
  return sf::Vector2i(segments[0].x, segments[0].y);
}

inline int Snake::getSpeed() const { return speed; }

inline Snake::Snake() {
  segments.push_back(
      Segment(snake::WINDOW_WIDTH / 2, snake::WINDOW_HEIGHT / 2));
  direction = None;
  speed = snake::INITIAL_SNAKE_SPEED;
}

inline void Snake::update() {
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

inline void Snake::grow() {
  int lastX = segments.back().x;
  int lastY = segments.back().y;
  segments.push_back(Segment(lastX, lastY));
}

inline void Snake::changeDirection(sf::Keyboard::Key keyCode) {
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

inline bool Snake::checkCollision() {
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

inline void Snake::render(sf::RenderWindow &window) {
  sf::Font font;
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

inline void Food::render(sf::RenderWindow &window) { // Remove 'Food::'
  window.draw(shape);
}

inline Food::Food() {
  shape.setSize(sf::Vector2f(snake::CELL_SIZE, snake::CELL_SIZE));
  shape.setFillColor(sf::Color::Yellow);
}

inline void Food::spawn(int maxWidth, int maxHeight) {
  int x = (rand() % (maxWidth / snake::CELL_SIZE)) * snake::CELL_SIZE;
  int y = (rand() % (maxHeight / snake::CELL_SIZE)) * snake::CELL_SIZE;
  position = sf::Vector2i(x, y);
  shape.setPosition(static_cast<float>(x),
                    static_cast<float>(y)); // Update the shape's position
}

inline sf::Vector2i Food::getPosition() const { return position; }

class GameOverScreen {
public:
  GameOverScreen(sf::Font &font);
  void show(sf::RenderWindow &window);

private:
  sf::Text gameOverText;
};

inline GameOverScreen::GameOverScreen(sf::Font &font) {
  gameOverText.setFont(font);
  gameOverText.setCharacterSize(40);
  gameOverText.setFillColor(sf::Color::Red);
  gameOverText.setString("Game Over!");
  gameOverText.setPosition(snake::WINDOW_WIDTH / 2 - 100,
                           static_cast<float>(snake::WINDOW_HEIGHT) / 2 - 20);
}

inline void GameOverScreen::show(sf::RenderWindow &window) {
  window.draw(gameOverText);
}

class snakeGame {
public:
  snakeGame();
  void run();
  void addToScore(int points);

private:
  sf::RenderWindow window;
  Snake snake;
  sf::Clock clock;
  sf::Font font;
  bool gameOver;

  void handleEvents();
  void update();
  void render();

  Food food;
  ScoreRenderer scoreRenderer;
  GameOverScreen gameOverScreen;
  void spawnFood();
};

inline snakeGame::snakeGame()
    : window(sf::VideoMode(snake::WINDOW_WIDTH, snake::WINDOW_HEIGHT), "Snake"),
      gameOver(false), scoreRenderer(font, 30, sf::Color::White, 10, 10),
      gameOverScreen(font) {
  window.setFramerateLimit(30);
  if (!font.loadFromFile("includes/ClearSans.ttf")) {
    // Handle error
  }
  spawnFood();
  scoreRenderer.setScore(0);
}
inline void snakeGame::addToScore(int points) {
  int score = points;
  scoreRenderer.setScore(score);
}
inline void snakeGame::run() {
  while (window.isOpen()) {
    handleEvents();
    update();
    render();
  }
}

inline void snakeGame::handleEvents() {
  sf::Event event;
  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      window.close();
      std::cout << "Window closed event detected\n";
    } else if (event.type == sf::Event::KeyPressed) {
      snake.changeDirection(event.key.code);
      std::cout << "Key pressed event detected\n";
    }
  }
}

inline void snakeGame::spawnFood() {
  food.spawn(snake::WINDOW_WIDTH, snake::WINDOW_HEIGHT);
  std::cout << "Food spawned at: " << food.getPosition().x << ", "
            << food.getPosition().y << std::endl;
}

inline void snakeGame::update() {
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
      scoreRenderer.addToScore(1);
      std::cout << "Food eaten, score: " << scoreRenderer.m_score << '\n';
      spawnFood();
    }
  }
}

inline void snakeGame::render() {
  window.clear(sf::Color::Black);
  snake.render(window);
  food.render(window);
  if (gameOver) {
    gameOverScreen.show(window);
  }
  scoreRenderer.draw(window, sf::RenderStates::Default);
  window.display();
}