#include "Game.h"
#include "raylib-cpp.hpp"
#include "raylib.h"
#include <cstdlib>

const std::string root_path = std::string(GetApplicationDirectory()) + "../";

namespace Raylib = raylib;

int main() {
    // Initialization
    Raylib::Window window{800, 400, "Template"};
    window.SetConfigFlags(FLAG_VSYNC_HINT);

    Game game{{20, 15}};

    // FPS cap
    window.SetTargetFPS(60);

    window.SetExitKey(KEY_Q);
    //--------------------------------------------------------------------------------------

    // Game loop switch flag
    bool running{true};
    bool exit_request{false};

    game.grid.gen_fruit();
    game.grid.print();

    while (running) {
        if (window.ShouldClose())
            exit_request = true;

        if (exit_request) {
            if (IsKeyPressed(KEY_Y))
                running = false;
            else if (IsKeyPressed(KEY_N))
                exit_request = false;
        }

        // Update
        //----------------------------------------------------------------------------------
        {
            //
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
