#include "Player.h"

using Direction = Grid::Direction;

/* ---------- Private methods ---------- */
Direction Snake::invert_direction(const Direction direction) {
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

/* ---------- Public methods ---------- */
Snake::Snake(const int speed) : m_speed{speed} {};

void Snake::move(const Grid& grid) {
    // m_body.insert(m_body.begin(), invert_direction(m_direction));
    //
    // if (m_body.size() + 1 >= m_length) {
    //     // TODO: traverse body
    //     m_body.pop_back();
    // }

    m_head_position = grid.get_tile_relative(m_head_position, m_direction, 1);
};

const Raylib::Vector2& Snake::get_head_pos() const { return m_head_position; };

const int Snake::get_speed() const { return m_speed; };

void Snake::set_direction(const Direction direction) {
    m_direction = direction;
};

void Snake::eat_fruit() { m_length++; };
