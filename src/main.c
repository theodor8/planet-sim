#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "style_terminal.h"


#define WIDTH 1200
#define HEIGHT 600  
#define CAMERA_SPEED 5

int main(void)
{
    SetTraceLogLevel(LOG_DEBUG);
    InitWindow(WIDTH, HEIGHT, "testis");
    GuiLoadStyleTerminal();
    SetTargetFPS(60);
    Camera2D camera = {0};
    camera.rotation = 0;
    camera.zoom = 1;
    /*camera.offset = (Vector2){WIDTH / 2.0f, HEIGHT / 2.0f};*/
    camera.offset = (Vector2){0, 0};
    camera.target = (Vector2){0, 0};

    while (!WindowShouldClose())
    {

        if (IsKeyDown(KEY_W)) camera.target.y -= CAMERA_SPEED;
        if (IsKeyDown(KEY_A)) camera.target.x -= CAMERA_SPEED;
        if (IsKeyDown(KEY_S)) camera.target.y += CAMERA_SPEED;
        if (IsKeyDown(KEY_D)) camera.target.x += CAMERA_SPEED;

        BeginDrawing();
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
        BeginMode2D(camera);


        DrawCircle(300, 300, 100, RED);

        EndMode2D();
        DrawRectangle(0, 0, 200, HEIGHT, GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
