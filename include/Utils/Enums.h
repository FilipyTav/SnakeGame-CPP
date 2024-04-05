#pragma once

namespace Orientation {
enum class Direction { UP, DOWN, LEFT, RIGHT, MAX_DIRECTIONS };
}

namespace Draw {
enum class Snake {
    HORIZONTAL, // ⬌
    VERTICAL,   // ⬍
    DOWN_RIGHT, // ↳
    RIGHT_UP,   // ⮥
    UP_LEFT,    // ↰
    LEFT_DOWN,  // ⮦

    MAX_DRAW_TYPES,
};

}
