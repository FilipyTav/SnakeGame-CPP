#include "Grid.h"
#include "Rectangle.hpp"
#include "Utils/Enums.h"
#include "Utils/Numbers.h"
#include "Utils/Redefinitions.h"
#include <algorithm>
#include <array>
#include <iostream>
#include <raylib.h>
#include <unordered_map>
#include <vector>

/* ---------- Public methods ---------- */
Grid::Grid(const Raylib::Vector2& size) : m_size{size} {
    m_data.resize(size.x * size.y);
    this->gen_fruit();
};

void Grid::draw(const Raylib::Window& window) const {
    Raylib::Color color{};

    using enum Draw::Snake;

    for (int row = 0; row < m_size.y; row++) {
        for (int col = 0; col < m_size.x; col++) {
            const TileType tile = this->get_tile(
                {static_cast<float>(col), static_cast<float>(row)});

            const Raylib::Rectangle tile_rec{col * m_tile_size.x,
                                             row * m_tile_size.y, m_tile_size.x,
                                             m_tile_size.y};

            // In pixels.
            float snake_size{std::min(tile_rec.width / 3, tile_rec.height / 3)};

            Vector2 tile_rec_mid{tile_rec.x + tile_rec.width / 2,
                                 tile_rec.y + tile_rec.height / 2};

            using Direction = Orientation::Direction;
            // Easier use of points{}
            enum hv { H, V };
            /*
             * first: start
             * second: end
             *
             * 0: Horizontal
             * 1: Vertical
             */
            std::array<std::pair<Raylib::Rectangle, Raylib::Rectangle>, 2>
                points{{
                    {// Horizontal
                     {tile_rec.x, tile_rec_mid.y - snake_size / 2,
                      tile_rec.width / 2 + snake_size / 2, snake_size},
                     {tile_rec.x + tile_rec.width / 2 - snake_size / 2,
                      tile_rec_mid.y - snake_size / 2,
                      tile_rec.width / 2 + snake_size / 2, snake_size}},

                    {// Vertical
                     {tile_rec_mid.x - snake_size / 2, tile_rec.y, snake_size,
                      tile_rec.height / 2},
                     {tile_rec_mid.x - snake_size / 2,
                      tile_rec.y + tile_rec.height / 2, snake_size,
                      tile_rec.height / 2}},
                }};

            // Stores the vertices of the shapes
            std::unordered_map<Draw::Snake, std::array<Raylib::Rectangle, 2>>
                vertices{{HORIZONTAL,
                          {
                              points[static_cast<int>(H)].first,
                              points[static_cast<int>(H)].second,
                          }},

                         {VERTICAL,
                          {
                              points[static_cast<int>(V)].first,
                              points[static_cast<int>(V)].second,
                          }},

                         {DOWN_RIGHT,
                          {
                              points[static_cast<int>(V)].first,
                              points[static_cast<int>(H)].second,
                          }},

                         {RIGHT_UP,
                          {
                              points[static_cast<int>(H)].first,
                              points[static_cast<int>(V)].first,
                          }},

                         {UP_LEFT,
                          {
                              points[static_cast<int>(H)].first,
                              points[static_cast<int>(V)].second,
                          }},

                         {LEFT_DOWN,
                          {
                              points[static_cast<int>(H)].second,
                              points[static_cast<int>(V)].second,
                          }}};

            if (tile.is_snake()) {
                color = WHITE;

                tile_rec.Draw(BLUE);

                for (auto rec : vertices[m_draw_type]) {
                    rec.Draw(color);
                }
            } else
                switch (tile.value) {
                    using enum Draw::Tile;
                    using enum Draw::Snake;

                case EMPTY:
                    color = BLANK;
                    break;

                case FRUIT: {
                    color = RED;

                    const float radius{
                        std::min(tile_rec.width / 2, tile_rec.height / 2)};

                    DrawCircleV({tile_rec.x + tile_rec.width / 2,
                                 tile_rec.y + tile_rec.height / 2},
                                radius, color);
                } break;

                default:
                    break;
                }

            // tile_rec.Draw(color);

            DrawRectangleLinesEx(tile_rec, .5, GRAY);
        }
    }
};

void Grid::print() const {
    // Clears console
    std::cout << "\x1B[2J\x1B[H";

    std::cout << "//"
                 "-------------------------------------------------------------"
                 "---------------------\n";
    for (int row = 0; row < m_size.y; row++) {
        for (int col = 0; col < m_size.x; col++) {
            const TileType tile = this->get_tile(
                {static_cast<float>(col), static_cast<float>(row)});

            if (tile.is_snake()) {
                /*
                 * Prints it in yellow
                 * See:
                 * https://en.wikipedia.org/wiki/ANSI_escape_code#Colors
                 *
                 * Also:
                 * https://stackoverflow.com/questions/2616906/how-do-i-output-coloured-text-to-a-linux-terminal
                 */
                std::cout << "| \033[1;33m" << tile.as_number() << "\033[0m ";
            } else
                switch (tile.value) {
                    using enum Draw::Tile;
                case FRUIT:
                    // Prints it in red
                    std::cout << "| \033[1;31m" << tile.as_number()
                              << "\033[0m ";
                    break;

                case EMPTY:
                    std::cout << "| " << tile.as_number() << " ";
                    break;

                // Assume it's the snake
                default:
                    break;
                }
        }
        std::cout << '\n';
    }

    std::cout << "-------------------------------------------------------------"
                 "---------------------//\n";
};

void Grid::set_tile(const Raylib::Vector2& coords, TileType tile) {
    m_data[coords.y * m_size.x + coords.x] = tile;
};

void Grid::gen_fruit() {
    if (this->get_tile(m_fruit_coords).value == Tile::FRUIT)
        this->set_tile(m_fruit_coords, Tile::EMPTY);

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

    if (this->get_tile(m_fruit_coords).value != Tile::EMPTY) {
        gen_fruit();
        return;
    }

    this->set_tile(m_fruit_coords, Tile::FRUIT);
};

const Grid::TileType Grid::get_tile(const Raylib::Vector2& coords) const {
    return m_data[coords.y * m_size.x + coords.x];
};

const Raylib::Vector2& Grid::get_size() const { return m_size; };

const Raylib::Vector2
Grid::get_tile_relative(const Raylib::Vector2& coords,
                        const Orientation::Direction direction,
                        const int step) const {
    Shy<int> result{coords};

    Shy<int> start{0, 0};
    Shy<int> limit{this->get_size()};

    switch (direction) {
        using enum Orientation::Direction;
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

void Grid::reset() {
    std::fill(m_data.begin(), m_data.end(), Tile::EMPTY);
    gen_fruit();
};

void Grid::update_tile_size(const Raylib::Window& window) {
    m_tile_size = Raylib::Vector2{window.GetWidth() / m_size.x,
                                  window.GetHeight() / m_size.y};
};

const Grid::SnakeDrawType Grid::get_draw_type() const { return m_draw_type; };
void Grid::set_draw_type(Grid::SnakeDrawType type) {
    if (type != m_draw_type)
        std::cout << "Draw type: " << static_cast<int>(type) << '\n';

    m_draw_type = type;
};
