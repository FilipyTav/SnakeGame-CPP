#include "Grid.h"
#include "Rectangle.hpp"
#include "Utils/Numbers.h"
#include "Utils/Redefinitions.h"
#include <iostream>
#include <raylib.h>

/* ---------- Public methods ---------- */
Grid::Grid(const Raylib::Vector2& size) : m_size{size} {
    m_data.resize(size.x * size.y);
};

void Grid::draw(const Raylib::Window& window) const {
    Raylib::Vector2 tile_size{window.GetWidth() / m_size.x,
                              window.GetHeight() / m_size.y};

    Raylib::Color color{};

    for (int row = 0; row < m_size.y; row++) {
        for (int col = 0; col < m_size.x; col++) {
            const Tile tile = this->get_tile(
                {static_cast<float>(col), static_cast<float>(row)});

            switch (tile) {
            case EMPTY:
                color = BLANK;
                break;

            case SNAKE:
                color = WHITE;
                break;

            case FRUIT:
                color = RED;
                break;

            default:
                std::cerr << "Grid::draw() - Incorrect tile\n";
                return;
            }

            const Raylib::Rectangle tile_rec{
                col * tile_size.x, row * tile_size.y, tile_size.x, tile_size.y};

            tile_rec.Draw(color);

            DrawRectangleLinesEx(tile_rec, .5, GRAY);
        }
    }
};

void Grid::print() const {
    std::cout << "//"
                 "-------------------------------------------------------------"
                 "---------------------\n";
    for (int row = 0; row < m_size.y; row++) {
        for (int col = 0; col < m_size.x; col++) {
            const Tile tile = this->get_tile(
                {static_cast<float>(col), static_cast<float>(row)});

            switch (tile) {
            case SNAKE:
                /*
                 * Prints it in yellow
                 * See: https://en.wikipedia.org/wiki/ANSI_escape_code#Colors
                 *
                 * Also:
                 * https://stackoverflow.com/questions/2616906/how-do-i-output-coloured-text-to-a-linux-terminal
                 */
                std::cout << "| \033[1;33m" << tile << "\033[0m ";
                break;

            case FRUIT:
                // Prints it in red
                std::cout << "| \033[1;31m" << tile << "\033[0m ";
                break;

            default:
                std::cout << "| " << tile << " ";
                break;
            }
        }
        std::cout << '\n';
    }

    std::cout << "-------------------------------------------------------------"
                 "---------------------//\n";
};

void Grid::set_tile(const Raylib::Vector2& coords, Tile tile) {
    m_data[coords.y * m_size.x + coords.x] = tile;
};

void Grid::gen_fruit() {
    if (this->get_tile(m_fruit_coords) == Tile::FRUIT)
        this->set_tile(m_fruit_coords, EMPTY);

    const int rngn{Random::get(0, m_data.size() - 1)};

    // Column
    m_fruit_coords.x = rngn % static_cast<int>(m_size.x);

    /*
     * Just to remember how I did this before
     *
     * Pos = (row * width) + col
     * row = (Pos - col) / w
     * pos.y = static_cast<int>((rngn - pos.x) / m_size.x);
     */

    m_fruit_coords.y = static_cast<int>(rngn / 20);

    if (this->get_tile(m_fruit_coords) == Tile::SNAKE) {
        gen_fruit();
        return;
    }

    this->set_tile(m_fruit_coords, Tile::FRUIT);
};

const Grid::Tile Grid::get_tile(const Raylib::Vector2& coords) const {
    return m_data[coords.y * m_size.x + coords.x];
};

const Raylib::Vector2& Grid::get_size() const { return m_size; };

const Raylib::Vector2 Grid::get_tile_relative(const Raylib::Vector2& coords,
                                              const Direction direction,
                                              const int step) const {
    Shy<int> result{coords};

    Shy<int> start{0, 0};
    Shy<int> limit{this->get_size()};

    switch (direction) {
    case UP:
        result.y = numbers::wrap_range(coords.y - step, start.y, limit.y);
        break;

    case DOWN:
        result.y = numbers::wrap_range(coords.y + step, start.y, limit.y);
        break;

    case LEFT:
        result.x = numbers::wrap_range(coords.x - step, start.x, limit.x);
        break;

    case RIGHT:
        result.x = numbers::wrap_range(coords.x + step, start.x, limit.x);
        break;

    default:
        std::cerr << "Snake::get_adjacent_tile() - Incorrect direction\n";
    }

    return result;
};

const Raylib::Vector2& Grid::get_fruit_coords() const {
    return m_fruit_coords;
};
