
#include "container/container.hpp"
#include "container/container.cpp"
#include <cstdio>
#include <raylib.h>
#include <vector>
const char* TITLE = "block Schematic";

int main(int argc, char* argv[]) {
    std::vector<Container*> containers;
    InitWindow(800, 650, TITLE);

    int WIDTH = GetMonitorWidth(GetCurrentMonitor());
    int HEIGHT = GetMonitorHeight(GetCurrentMonitor());
    
    Container* container = new Container(1, "test", 40);
    containers.push_back(container);

    SetWindowSize(WIDTH, HEIGHT);
    SetTargetFPS(60);
    SetWindowState(FLAG_FULLSCREEN_MODE);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawFPS(WIDTH - (WIDTH / 20), 10);
        int textWidth = MeasureText(TITLE, 100);

        int textX = (WIDTH/2) - (textWidth/2);
        int textY = (HEIGHT/2)-50;
        DrawText(TITLE, textX, textY, 100, BLACK);

        for(int i = 0; i < containers.size(); i++) {
            containers[i]->Draw();
        }
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}
