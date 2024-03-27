#include "Player.h"
#include "Utils/Numbers.h"

using Direction = Orientation::Direction;

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

void Snake::move(Grid& grid) {
    m_body[m_movements] = m_head_pos;

    grid.set_tile(m_body[numbers::wrap_range(m_movements + 1, 0, m_length)],
                  Grid::Tile::EMPTY);

    m_movements = (m_movements + 1) % m_length;

    m_head_pos = grid.get_tile_relative(m_head_pos, m_direction, 1);

    if (grid.get_fruit_coords() == m_head_pos) {
        this->eat_fruit();

        grid.gen_fruit();
    };
};

const Raylib::Vector2& Snake::get_head_pos() const { return m_head_pos; };

const int Snake::get_speed() const { return m_speed; };

void Snake::set_direction(const Direction direction) {
    // Going to the opposite direction is an instant loss.
    // Also kinda annoying.
    if (invert_direction(direction) != m_direction)
        m_direction = direction;
};

void Snake::eat_fruit() {
    // It instantly worked when changed from vector::reserve.
    // Why though?
    m_body.resize(++m_length);
};

void Snake::reset() {
    m_head_pos = Raylib::Vector2{};
    m_length = 1;

    m_movements = 0;

    m_body = {m_head_pos};
    m_direction = Direction::RIGHT;
};

const Snake::DrawType Snake::get_draw_type() const { return m_draw_type; };

const int Snake::get_length() { return m_length; };
