#pragma once

#include "Utils/Enums.h"
#include "Utils/Random.h"
#include "Vector2.hpp"
#include "raylib-cpp.hpp"
#include "raylib.h"
#include <array>
#include <iostream>
#include <vector>

namespace Raylib = raylib;

class Grid {
  public:
    enum Tile { EMPTY, SNAKE, FRUIT, MAX_TILES };

  private:
    using SnakeDrawType = Draw::Snake;

    // FIX: Should be on Snake class, but that would cause a circular
    // dependency
    SnakeDrawType m_draw_type{SnakeDrawType::HORIZONTAL};

    // On each axis
    Raylib::Vector2 m_size{};
    std::vector<Tile> m_data{};

    Raylib::Vector2 m_tile_size{};

    Raylib::Vector2 m_fruit_coords{};

  public:
    Grid(const Raylib::Vector2& size);
    Grid(Grid&&) = default;
    Grid(const Grid&) = default;
    Grid& operator=(Grid&&) = default;
    Grid& operator=(const Grid&) = default;
    ~Grid() = default;

    // Render to the screen
    void draw(const Raylib::Window& window) const;

    // Display for visualisation
    void print() const;

    // Change tile at coords
    void set_tile(const Raylib::Vector2& coords, Tile tile);

    // Get tile at position
    // {col, row} - {x, y}
    const Tile get_tile(const Raylib::Vector2& coords) const;

    // Random available tile
    void gen_fruit();

    const Raylib::Vector2& get_fruit_coords() const;

    const Raylib::Vector2& get_size() const;

    const Raylib::Vector2
    get_tile_relative(const Raylib::Vector2& coords,
                      const Orientation::Direction direction,
                      const int step = 1) const;

    void update_tile_size(const Raylib::Window& window);

    const SnakeDrawType get_draw_type() const;
    void set_draw_type(SnakeDrawType type);

    void reset();
};
