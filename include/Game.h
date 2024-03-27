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
    bool lost{false};
    bool won{false};

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

    bool did_lose() const { return lost; };
    bool did_win() const { return won; };

    void update_result() {
        lost = grid.get_tile(snake.get_head_pos()) == Grid::Tile::SNAKE;
        won = grid.get_size().x * grid.get_size().y != snake.get_length();
    };
};
