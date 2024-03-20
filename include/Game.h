#pragma once

#include "Grid.h"
#include "Vector2.hpp"
#include "raylib-cpp.hpp"
#include "raylib.h"
#include <vector>

namespace Raylib = raylib;

class Game {
  public:
    Grid grid{{20, 15}};

  public:
    Game(const Raylib::Vector2& grid_size);
    Game(Game&&) = default;
    Game(const Game&) = default;
    Game& operator=(Game&&) = default;
    Game& operator=(const Game&) = default;
    ~Game() = default;
};
