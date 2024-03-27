#include "Game.h"
#include "raylib-cpp.hpp"
#include "raylib.h"
#include <cstdlib>

const std::string root_path = std::string(GetApplicationDirectory()) + "../";

namespace Raylib = raylib;

void handle_input(Game& game);
void pause(bool condition);

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

    // Delta time
    float dt{};
    //--------------------------------------------------------------------------------------

    // Game loop switch flags
    bool running{true};
    bool exit_request{false};
    bool paused{false};

    while (running) {
        if (window.ShouldClose()) {
            exit_request = true;
            paused = true;
        }

        if (exit_request) {
            if (IsKeyPressed(KEY_Y))
                running = false;
            else if (IsKeyPressed(KEY_N)) {
                exit_request = false;
                paused = !paused;
            }
        }

        if (paused) {
            if (game.lost) {
                if (IsKeyPressed(KEY_Y)) {
                    game.reset();
                    paused = !paused;
                } else if (IsKeyPressed(KEY_N))
                    running = false;
            }
        }

        // Update
        //----------------------------------------------------------------------------------
        {
            if (!paused) {
                handle_input(game);

                // game.grid.print();
                frames_counter++;

                if (frames_counter >= (60 / game.snake.get_speed())) {
                    frames_counter = 0;

                    // Pauses if the user loses
                    game.lost = game.snake.move(game.grid);
                    paused = game.lost;
                }

                dt = GetFrameTime();
            }
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        {
            window.BeginDrawing();

            if (!paused) {
                window.ClearBackground(BLACK);

                game.grid.draw(window);
            } else {
                if (game.lost) {
                    DrawRectangle(0, 100, GetRenderWidth(), 200, BLACK);
                    DrawText("You lost! Wanna try again? [Y/N]", 40, 180, 30,
                             WHITE);
                }
            }

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
        game.snake.eat_fruit();
};
