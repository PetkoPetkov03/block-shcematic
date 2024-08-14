
#include "container/container.hpp"
#include "container/container.cpp"
#include <cstdio>
#include <raylib.h>
#include <vector>
const char* TITLE = "block Schematic";

int selectedContainerIndex = -1;
Container* selectedContainer = nullptr;

void HandleMouseEvents(std::vector<Container*>* containers) {
      if(selectedContainer != nullptr && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
         Vector2 mousePosition = GetMousePosition();
          selectedContainer->SetPosition(&mousePosition);
          Rectangle body;
          body.width = selectedContainer->GetBody().width;
          body.height = selectedContainer->GetBody().height;
          body.x = selectedContainer->GetPosition().x - (body.width / 2);
          body.y = selectedContainer->GetPosition().y - (body.height / 2);
          selectedContainer->SetBody(&body);
          printf("Test:: X {%f}, Y {%f} Clicked: %i \n", selectedContainer->GetPosition().x, selectedContainer->GetPosition().y, selectedContainer == nullptr);

          (*containers)[selectedContainerIndex] = selectedContainer;

          printf("TTT: %i\n", selectedContainerIndex);

          selectedContainerIndex = -1;
          selectedContainer = nullptr;
          printf("Clicked %i\n", selectedContainer == nullptr);
          return;
      }
    if(selectedContainer == nullptr && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        for(int i = 0; i < containers->size(); i++) {
            Container* container = (*containers)[i];
            if(CheckCollisionPointRec(GetMousePosition(), container->GetBody())) {
                selectedContainerIndex = i;
                selectedContainer = container;
                break;
            }
        }
    }

  printf("Clicked? %i\n", selectedContainer == nullptr);

  
}

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
        
        HandleMouseEvents(&containers);
        EndDrawing();
    }
    
    printf("XX: %f, YY: %f\n", containers[0]->GetPosition().x, containers[0]->GetPosition().y);
    
    CloseWindow();
    return 0;
}
