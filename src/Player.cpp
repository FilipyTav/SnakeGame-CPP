#include "Player.h"
#include "Utils/Enums.h"

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
    // Puts the coords of the body in the array, and delete them to simulate
    // movement. Depends on m_length
    m_body[m_movements] = m_head_pos;

    m_movements = (m_movements + 1) % m_length;

    // EMPTY out the oldest body coord
    grid.set_tile(m_body[m_movements], Grid::Tile::EMPTY);

    m_head_pos = grid.get_tile_relative(m_head_pos, m_direction, 1);

    if (grid.get_fruit_coords() == m_head_pos) {
        this->eat_fruit();

        grid.gen_fruit();
    };
};

const Raylib::Vector2& Snake::get_head_pos() const { return m_head_pos; };

const int Snake::get_speed() const { return m_speed; };

Draw::Snake Snake::set_direction(const Direction direction) {
    Draw::Snake draw_type{};

    {
        using enum Direction;
        using enum Draw::Snake;

        switch (direction) {
        case UP:
        case DOWN:
            draw_type = VERTICAL;

        case LEFT:
        case RIGHT:
            draw_type = HORIZONTAL;

        default:
            break;
        }

        // Going to the opposite direction is an instant loss.
        // Also kinda annoying.
        if (invert_direction(direction) == m_direction ||
            m_direction == direction)
            return draw_type;

        // m_direction -> current
        // direction -> next
        if (m_direction == UP || direction == DOWN) {
            if (direction == LEFT || m_direction == RIGHT) {
                draw_type = UP_LEFT;
            } else if (direction == RIGHT || m_direction == LEFT) {
                draw_type = RIGHT_UP;
            }
        } else if (m_direction == DOWN || direction == UP) {
            if (direction == LEFT || m_direction == RIGHT) {
                draw_type = LEFT_DOWN;
            } else if (direction == RIGHT || m_direction == LEFT) {
                draw_type = DOWN_RIGHT;
            }
        }
    }

    m_direction = direction;

    return draw_type;
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

const int Snake::get_length() { return m_length; };
