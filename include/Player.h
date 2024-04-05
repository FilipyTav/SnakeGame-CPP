#pragma once

#include "Grid.h"
#include "raylib-cpp.hpp"
#include "raylib.h"
#include <cstdint>
#include <iostream>
#include <vector>

namespace Raylib = raylib;

class Snake {
  private:
    using Direction = Orientation::Direction;

    Raylib::Vector2 m_head_pos{0, 0};

    // Position of the tiles composing the body.
    // Used for reseting a tile after the snakes moves away from it.
    std::vector<Raylib::Vector2> m_body{m_head_pos};

    Direction m_direction{Direction::RIGHT};
    uint16_t m_movements{};

    // In frames
    int m_speed{};

    // Fruits eaten + 1(head)
    int m_length{1};

    Direction invert_direction(const Direction direction);

  public:
    Snake(const int speed = 10);
    Snake(Snake&&) = default;
    Snake(const Snake&) = default;
    Snake& operator=(Snake&&) = default;
    Snake& operator=(const Snake&) = default;
    ~Snake() = default;

    // Depends on m_direction.
    void move(Grid& grid);

    const Raylib::Vector2& get_head_pos() const;

    const int get_speed() const;

    // Returns the type of drawing that should be used for the snake tile,
    // depending on the current and the next direction
    Draw::Snake set_direction(const Direction direction);

    void eat_fruit();

    void reset();

    const int get_length();
};
