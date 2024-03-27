#pragma once

#include "Grid.h"
#include "raylib-cpp.hpp"
#include "raylib.h"
#include <cstdint>
#include <iostream>
#include <vector>

namespace Raylib = raylib;

class Snake {
  public:
    enum class DrawType {
        HORIZONTAL, // ⬌
        VERTICAL,   // ⬍
        DOWN_RIGHT, // ↳
        RIGHT_UP,   // ⮥
        UP_LEFT,    // ↰
        LEFT_DOWN,  // ⮦

        MAX_DRAW_TYPES,
    };

  private:
    using Direction = Orientation::Direction;

    Raylib::Vector2 m_head_pos{0, 0};
    std::vector<Raylib::Vector2> m_body{m_head_pos};
    Direction m_direction{Direction::RIGHT};
    uint16_t m_movements{};

    DrawType m_draw_type{DrawType::HORIZONTAL};

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

    /*
     * Depends on m_direction.
     */
    void move(Grid& grid);

    const Raylib::Vector2& get_head_pos() const;

    const int get_speed() const;

    void set_direction(const Direction direction);

    void eat_fruit();

    void reset();

    const DrawType get_draw_type() const;

    const int get_length();
};
