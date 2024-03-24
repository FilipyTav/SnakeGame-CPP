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

    // Eaten fruits + 1
    int m_length{1};

    Direction invert_direction(const Direction direction) {
        switch (direction) {
            using enum Direction;

        case UP:
            return DOWN;
        case DOWN:
            return UP;

        case LEFT:
            return RIGHT;
        case RIGHT:
            return LEFT;

        default:
            std::cerr << "Snake::invert_direction() - Incorrect direction\n";
            return MAX_DIRECTIONS;
        }
    };

  public:
    Snake(const int speed = 4) : m_speed{speed} {};
    Snake(Snake&&) = default;
    Snake(const Snake&) = default;
    Snake& operator=(Snake&&) = default;
    Snake& operator=(const Snake&) = default;
    ~Snake() = default;

    void move(const Grid& grid) {
        m_body.insert(m_body.begin(), invert_direction(m_direction));

        if (m_body.size() + 1 >= m_length) {
            // TODO: traverse body
            m_body.pop_back();
        }

        m_head_position = grid.get_adjacent_tile(m_head_position, m_direction);

        std::cout << "coords: (" << m_head_position.x << ", "
                  << m_head_position.y << ")\n";
        std::cout << "dir: " << m_direction << "\n\n";
    };

    const Raylib::Vector2& get_head_pos() const { return m_head_position; };

    const int get_speed() const { return m_speed; };

    void set_direction(const Direction direction) { m_direction = direction; };

    void eat_fruit() { m_length++; };
};
