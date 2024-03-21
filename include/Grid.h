#pragma once

#include "Utils/Random.h"
#include "Vector2.hpp"
#include "raylib-cpp.hpp"
#include "raylib.h"
#include <array>
#include <vector>

namespace Raylib = raylib;

class Grid {
  public:
    enum Tile { EMPTY, SNAKE, FRUIT };

  private:
    // On each axis
    Raylib::Vector2 m_size{};
    std::vector<Tile> m_data{};

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
    // {col, row}
    const Tile get_tile(const Raylib::Vector2& coords) const;

    // Random available tile
    void gen_fruit();
};
