#include "core/app.hpp"

App::App() {
    // Respect settings
    InitWindow(1200, 900, "Deadweight");
}

void App::run() {
    while(!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(RED);

        EndDrawing();
    }
}