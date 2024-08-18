#include "container/container.hpp"
#include "container/container.cpp"
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <raylib.h>
#include <string>
#include <vector>

enum RenderState {
    Input,
    Display,
};

const char* TITLE = "block Schematic";

int selectedContainerIndex = -1;
Container* selectedContainer = nullptr;

void GenerateContainer(std::vector<Container*>* containers, std::string input) {
    Container* newContainer = new Container(1, input, 40);

    containers->push_back(newContainer);
}

void HandleInputLogic(std::vector<Container*>* containers, bool mouseOnText, std::string* input, enum RenderState* renderState, bool* disableHotkeys) {
    if(mouseOnText) {
        SetMouseCursor(MOUSE_CURSOR_IBEAM);

        int key = GetCharPressed();

        while (key > 0) {
            if(key >= 32 && key < 125) {
                *input += (char)key;
            }
            key = GetCharPressed();
        }

        if(IsKeyPressed(KEY_BACKSPACE)) {
            if(input->size() > 0) {
                input->pop_back();
            }
        }

        if(IsKeyPressed(KEY_ENTER)) {
            GenerateContainer(containers, *input);
            *input = "";
            *renderState = RenderState::Display;
            *disableHotkeys = false;
        }
    }else SetMouseCursor(MOUSE_CURSOR_DEFAULT);
}

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

          (*containers)[selectedContainerIndex] = selectedContainer;

          selectedContainerIndex = -1;
          selectedContainer = nullptr;
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
}

void HandleKeyboardEvents(bool* disableHotkeys, std::string* input, enum RenderState* renderState, std::vector<Container*>* containers) {
    if(!*disableHotkeys) {
        if (selectedContainer != nullptr && (IsKeyDown(KEY_D) || IsKeyDown(KEY_DELETE))) {
            std::vector<Container*>::iterator it;

            it = std::find(containers->begin(), containers->end(), selectedContainer);
            Container* c = (*containers)[selectedContainerIndex];
            containers->erase(it);

            delete c;

            selectedContainerIndex = -1;
            selectedContainer = nullptr;
        }

        if(selectedContainer != nullptr && IsKeyDown(KEY_C)) {
            Container* container = (*containers)[selectedContainerIndex];

            Vector2 mousePosition = GetMousePosition();

            Container* selectedContainerIn;

            for(int i = 0; i < containers->size(); i++) {
                Container* possibleContainer;
                if(CheckCollisionPointRec(GetMousePosition(), (*containers)[i]->GetBody())) {
                    possibleContainer = (*containers)[i];
                }

                selectedContainerIn = possibleContainer;
            }

            if(selectedContainerIn != nullptr) {
                Rectangle body;
                body.x = selectedContainerIn->GetBody().x;
                body.y = container->GetBody().y;
                body.width = container->GetBody().width;
                body.height = container->GetBody().height;
                container->SetBody(&body);

                selectedContainerIndex = -1;
                selectedContainer = nullptr;
            }
        }
    }

    if(*disableHotkeys && *renderState == RenderState::Input) {
        HandleInputLogic(containers, disableHotkeys, input, renderState, disableHotkeys);
    }
}

RenderState HandleRenderState(bool* disableHotkeys, enum RenderState renderState) {
    if(selectedContainer == nullptr && (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyDown(KEY_S))) {
        WaitTime(0.3);
        *disableHotkeys = !*disableHotkeys;
        return renderState == RenderState::Display ? RenderState::Input : RenderState::Display;
    }

    return renderState;
}

void SetMouseOnText(bool* mouseOnText, Rectangle* textBox) {
    if(CheckCollisionPointRec(GetMousePosition(), *textBox)) *mouseOnText = true;
    else *mouseOnText = false;
}

int main(int argc, char* argv[]) {
    bool disableHotkeys = false;
    enum RenderState renderState = RenderState::Display;
    std::vector<Container*> containers;
    InitWindow(800, 650, TITLE);
    int WIDTH = GetMonitorWidth(GetCurrentMonitor());
    int HEIGHT = GetMonitorHeight(GetCurrentMonitor());

    SetWindowSize(WIDTH, HEIGHT);
    SetTargetFPS(60);
    SetWindowState(FLAG_FULLSCREEN_MODE);

    int textWidth = MeasureText(TITLE, 100);

    int textX = (WIDTH/2) - (textWidth/2);
    int textY = (HEIGHT/2)-50;

    /* Handle input logic */
    std::string input = "";

    Rectangle textBox = { WIDTH/5.f, HEIGHT/2.f, WIDTH/1.5f, 50 };
    bool mouseOnText = false;

    while (!WindowShouldClose())
    {
        SetMouseOnText(&mouseOnText, &textBox);
        HandleMouseEvents(&containers);
        HandleKeyboardEvents(&disableHotkeys, &input, &renderState, &containers);
        renderState = HandleRenderState(&disableHotkeys, renderState);
        switch (renderState) {
            case RenderState::Display: {
                BeginDrawing();
                ClearBackground(RAYWHITE);
                DrawFPS(WIDTH - (WIDTH / 20), 10);
                DrawText(TITLE, textX, textY, 100, BLACK);

                for(int i = 0; i < containers.size(); i++) {
                    containers[i]->Draw();
                } 

                EndDrawing();

                break;
            }

            case RenderState::Input: {
                BeginDrawing();
                ClearBackground(RAYWHITE); 
                std::string inputTitle = "Input";
                float inputTitleSize = MeasureText(inputTitle.c_str(), 30);
                DrawText(inputTitle.c_str(), textBox.x, textBox.y - (inputTitleSize / 2), 30, RED);
                DrawRectangleRec(textBox, LIGHTGRAY);
                DrawText(input.c_str(), (int)textBox.x + 5, (int)textBox.y + 8, 40, MAROON);
                EndDrawing();
                break;
            }

            default:
                BeginDrawing();
                DrawText("State error", textX, textY, 100, RED);
                EndDrawing();

        }
    }

    for(int i = 0; i < containers.size(); i++) {
      delete containers[i];
    }

    CloseWindow();
    return 0;
}
