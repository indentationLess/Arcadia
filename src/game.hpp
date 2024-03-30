#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

// for game engine
class game {
private:
  // initializing variables
  // window
  void initVar();
  void initWindow();

public:
  // constructors and destructors
  game();
  virtual ~game();

  // functions
  void update();
  void render();
};
