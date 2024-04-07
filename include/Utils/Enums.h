#pragma once

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

    bool is_snake() const {
        if (this->get_tile_type(value) == Player)
            return true;

        return false;
    };
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

    const int as_number() const {
        TileTp type{this->get_tile_type(value)};

        switch (type) {
        case Standard:
            return Tile::MAX_TILES - static_cast<int>(type);
            break;

        case Player:
            return static_cast<int>(Snake::MAX_DRAW_TYPES) -
                   static_cast<int>(type);
            break;
        }

        return -1;
    };

    constexpr TileTp get_tile_type(unsigned value) const {
        return static_cast<TileTp>(value & 0xFF00);
    }
};

} // namespace Draw
