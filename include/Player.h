#pragma once

// TODO: Player control

#include "Grid.h"
#include "raylib-cpp.hpp"
#include "raylib.h"
#include <cstdint>
#include <iostream>
#include <vector>

namespace Raylib = raylib;

class Snake {
  private:
    using Direction = Grid::Direction;

    Raylib::Vector2 m_head_pos{0, 0};
    std::vector<Raylib::Vector2> m_body{m_head_pos};
    Direction m_direction{Direction::RIGHT};
    uint16_t m_movements{};

    // In frames
    int m_speed{};

    // Fruits eaten + 1(head)
    int m_length{1};

    Direction invert_direction(const Direction direction);

  public:
    Snake(const int speed = 7);
    Snake(Snake&&) = default;
    Snake(const Snake&) = default;
    Snake& operator=(Snake&&) = default;
    Snake& operator=(const Snake&) = default;
    ~Snake() = default;

    /*
     * Depends on m_direction.
     *
     * Returns whether or not the snake lost the game on this move.
     */
    bool move(Grid& grid);

    const Raylib::Vector2& get_head_pos() const;

    const int get_speed() const;

    void set_direction(const Direction direction);

    void eat_fruit();

    bool did_lose(const Grid& grid) const;

    void reset();
};
