#include "Grid.h"
#include "Rectangle.hpp"
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
                std::cout << "Grid::draw() - Incorrect tile\n";
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
    for (int row = 0; row < m_size.y; row++) {
        for (int col = 0; col < m_size.x; col++) {
            const Tile tile = this->get_tile(
                {static_cast<float>(col), static_cast<float>(row)});

            if (tile == Tile::FRUIT)
                std::cout << "| \033[1;31m" << tile << "\033[0m ";
            else
                std::cout << "| " << tile << " ";
        }
        std::cout << '\n';
    }
};

void Grid::set_tile(const Raylib::Vector2& coords, Tile tile) {
    m_data[coords.y * m_size.x + coords.x] = tile;
};

void Grid::gen_fruit() {
    set_tile(m_fruit_coords, EMPTY);

    const int rngn{Random::get(0, m_data.size() - 1)};

    // TODO: use m_fruit_coords instead of this var
    Raylib::Vector2 pos{};

    // Column
    pos.x = rngn % static_cast<int>(m_size.x);

    // Pos = (row * width) + col
    // row = (Pos - col) / w
    // pos.y = static_cast<int>((rngn - pos.x) / m_size.x);

    pos.y = static_cast<int>(rngn / 20);

    if (m_data[rngn] == Tile::SNAKE) {
        gen_fruit();
        return;
    }

    m_fruit_coords = pos;
    set_tile(pos, FRUIT);
};

const Grid::Tile Grid::get_tile(const Raylib::Vector2& coords) const {
    return m_data[coords.y * m_size.x + coords.x];
};
