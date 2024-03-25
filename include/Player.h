#pragma once

// TODO: Player control

#include "Grid.h"
#include "raylib-cpp.hpp"
#include "raylib.h"
#include <iostream>
#include <vector>

namespace Raylib = raylib;

class Snake {
  private:
    using Direction = Grid::Direction;

    Raylib::Vector2 m_head_position{0, 0};
    Direction m_direction{Direction::RIGHT};
    Direction m_prev_direction{Direction::LEFT};

    // Directions from head to tail
    std::vector<Direction> m_body{};

    // In frames
    int m_speed{};

    // Fruits eaten + 1
    int m_length{1};

    Direction invert_direction(const Direction direction);

  public:
    Snake(const int speed = 4);
    Snake(Snake&&) = default;
    Snake(const Snake&) = default;
    Snake& operator=(Snake&&) = default;
    Snake& operator=(const Snake&) = default;
    ~Snake() = default;

    // Depends on m_direction
    void move(const Grid& grid);

    const Raylib::Vector2& get_head_pos() const;

    const int get_speed() const;

    void set_direction(const Direction direction);

    void eat_fruit();
};
