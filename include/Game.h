#pragma once

#include "Grid.h"
#include "Player.h"
#include "raylib-cpp.hpp"
#include "raylib.h"
#include <vector>

namespace Raylib = raylib;

class Game {
  private:
  public:
    Grid grid{{20, 15}};
    Snake snake{};
    bool lost{};

  public:
    Game(const Raylib::Vector2& grid_size);
    Game(Game&&) = default;
    Game(const Game&) = default;
    Game& operator=(Game&&) = default;
    Game& operator=(const Game&) = default;
    ~Game() = default;

    void reset() {
        snake.reset();
        grid.reset();

        lost = false;
    };
};
