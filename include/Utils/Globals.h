#pragma once

#include "raylib-cpp.hpp"
#include <array>
#include <unordered_map>

namespace Raylib = raylib;

namespace Orientation {
enum class Direction { UP, DOWN, LEFT, RIGHT, MAX_DIRECTIONS };
}

namespace Draw {
/*
 * Standard: Tiles
 *
 * Player: Snake
 *
 * See:
 * https://stackoverflow.com/questions/18344646/combine-enums-c/18344715#18344715
 */
enum TileTp { Standard = 0x100, Player = 0x200 };

enum class Snake {
    HORIZONTAL = Player, // ⬌
    VERTICAL,            // ⬍
    DOWN_RIGHT,          // ↳
    RIGHT_UP,            // ⮥
    UP_LEFT,             // ↰
    LEFT_DOWN,           // ⮦

    MAX_DRAW_TYPES,
};

enum Tile { EMPTY = Standard, FRUIT, MAX_TILES };

inline const std::array<Raylib::Rectangle, 2>
get_composing_rects(const Snake value, const Raylib::Rectangle& tile_rec,
                    const Raylib::Vector2& tile_mid, const float snake_size) {
    // Easier use of points{}
    enum hv { H, V };
    /*
     * first: start
     * second: end
     *
     * 0: Horizontal
     * 1: Vertical
     */
    std::array<std::pair<Raylib::Rectangle, Raylib::Rectangle>, 2> points{{
        {// Horizontal
         {tile_rec.x, tile_mid.y - snake_size / 2,
          tile_rec.width / 2 + snake_size / 2, snake_size},
         {tile_rec.x + tile_rec.width / 2 - snake_size / 2,
          tile_mid.y - snake_size / 2, tile_rec.width / 2 + snake_size / 2,
          snake_size}},

        {// Vertical
         {tile_mid.x - snake_size / 2, tile_rec.y, snake_size,
          tile_rec.height / 2},
         {tile_mid.x - snake_size / 2, tile_rec.y + tile_rec.height / 2,
          snake_size, tile_rec.height / 2}},
    }};

    using enum Draw::Snake;
    // Stores the vertices of the shapes
    std::unordered_map<Draw::Snake, std::array<Raylib::Rectangle, 2>> vertices{
        {HORIZONTAL,
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

    return vertices[value];
};

struct TileType {
    int value;

    TileType() { value = Tile::EMPTY; }
    TileType(Tile val) : value((int)val) {}
    TileType(Snake val) : value((int)val) {}
    TileType& operator=(Tile val) {
        value = (int)val;
        return *this;
    }
    TileType& operator=(Snake val) {
        value = (int)val;
        return *this;
    }

    bool is_snake() const { return this->get_tile_type(value) == Player; };
    Tile as_tile() const {
        if (value >= TileTp::Standard && value < Tile::MAX_TILES)
            return (Tile)value;
        return Tile::MAX_TILES;
    }
    Snake as_snake() const {
        if (value >= TileTp::Player &&
            value < static_cast<int>(Snake::MAX_DRAW_TYPES))
            return (Snake)value;
        return Snake::MAX_DRAW_TYPES;
    }

    const int as_number() const { return value - this->get_tile_type(value); };

    constexpr TileTp get_tile_type(unsigned value) const {
        return static_cast<TileTp>(value & 0xFF00);
    }
};

} // namespace Draw
