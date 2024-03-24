#include "Game.h"
#include "raylib-cpp.hpp"
#include "raylib.h"
#include <concepts>
#include <cstdlib>
#include <iostream>

const std::string root_path = std::string(GetApplicationDirectory()) + "../";

namespace Raylib = raylib;

void handle_input(Game& game);

int main() {
    // Initialization
    //--------------------------------------------------------------------------------------
    Raylib::Window window{800, 400, "Template"};
    window.SetConfigFlags(FLAG_VSYNC_HINT);

    // FPS cap
    window.SetTargetFPS(60);

    window.SetExitKey(KEY_Q);

    int frames_counter = 0;
    Game game{{20, 15}};

    float dt{};
    //--------------------------------------------------------------------------------------

    // Game loop switch flag
    bool running{true};
    bool exit_request{false};

    game.grid.gen_fruit();
    game.grid.print();

    // FIX: error on snake movement
    // return 0;

    while (running) {
        if (window.ShouldClose())
            exit_request = true;

        if (exit_request) {
            if (IsKeyPressed(KEY_Y))
                running = false;
            else if (IsKeyPressed(KEY_N))
                exit_request = false;
        }

        handle_input(game);

        // Update
        //----------------------------------------------------------------------------------
        {
            frames_counter++;

            // TODO: update player
            if (frames_counter >= (60 / game.snake.get_speed())) {
                frames_counter = 0;

                game.snake.move(game.grid);
            }

            dt = GetFrameTime();
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        {
            window.BeginDrawing();

            window.ClearBackground(BLACK);

            game.grid.draw(window);

            if (exit_request) {
                DrawRectangle(0, 100, GetRenderWidth(), 200, BLACK);
                DrawText("Are you sure you want to exit? [Y/N]", 40, 180, 30,
                         WHITE);
            }

            window.EndDrawing();
        }
        //----------------------------------------------------------------------------------
    }
cleanup:

    return EXIT_SUCCESS;
}

void handle_input(Game& game) {
    // Snake movement
    //----------------------------------------------------------------------------------
    game.grid.set_tile(game.snake.get_head_pos(), Grid::Tile::EMPTY);

    if (IsKeyDown(KEY_W))
        game.snake.set_direction(Grid::Direction::UP);

    if (IsKeyDown(KEY_A))
        game.snake.set_direction(Grid::Direction::LEFT);

    if (IsKeyDown(KEY_S))
        game.snake.set_direction(Grid::Direction::DOWN);

    if (IsKeyDown(KEY_D))
        game.snake.set_direction(Grid::Direction::RIGHT);

    game.grid.set_tile(game.snake.get_head_pos(), Grid::Tile::SNAKE);
    //----------------------------------------------------------------------------------

    if (IsKeyPressed(KEY_SPACE))
        game.grid.gen_fruit();
};
