

#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "style_terminal.h"

#include "planet.h"
#include "world.h"

#define WIDTH 1200
#define HEIGHT 600
#define CAMERA_SPEED 5
#define CAMERA_ZOOM_SPEED 0.02;


void draw_planet_prev_path(planet_t *p)
{
    int i = p->prev_i;
    int prev_i;
    for (int j = 0; j < p->prev_siz - 1; ++j)
    {
        prev_i = i;
        ++i;
        if (i >= p->prev_siz) i = 0;
        Vector2 start = {p->prev_xs[prev_i], p->prev_ys[prev_i]};
        Vector2 end = {p->prev_xs[i], p->prev_ys[i]};
        Color color = {255, 255, 255, 100 * (1.0f - j / (float)(p->prev_siz - 1))};
        DrawLineV(start, end, color);
    }
}

int main(void)
{
    /*SetTraceLogLevel(LOG_ERROR);*/
    SetTraceLogLevel(LOG_DEBUG);
    InitWindow(WIDTH, HEIGHT, "Planet Sim");
    GuiLoadStyleTerminal();
    SetTargetFPS(60);
    SetConfigFlags(FLAG_MSAA_4X_HINT);

    RenderTexture2D target = LoadRenderTexture(WIDTH, HEIGHT);
    Shader shader = LoadShader(0, "src/bloom.fs");

    Camera2D camera = {0};
    camera.rotation = 0;
    camera.zoom = 1;
    camera.offset = (Vector2){WIDTH / 2.0f, HEIGHT / 2.0f};
    camera.target = (Vector2){0, 0};

    const Color colors[] = {RED, GREEN, BLUE, YELLOW, WHITE};


    world_t *world = world_create(4000);
    world_add_planet(world, planet_create(0, 0, 0, 0, 20, 2));
    world_add_planet(world, planet_create(200, 300, 0, -150, 10, 1));

    bool paused = false;
    float time_scale = 1;

    while (!WindowShouldClose())
    {
        if (!paused)
        {
            world_update(world, GetFrameTime() * time_scale);
        }

        if (IsKeyDown(KEY_W)) camera.target.y -= CAMERA_SPEED;
        if (IsKeyDown(KEY_A)) camera.target.x -= CAMERA_SPEED;
        if (IsKeyDown(KEY_S)) camera.target.y += CAMERA_SPEED;
        if (IsKeyDown(KEY_D)) camera.target.x += CAMERA_SPEED;
        if (IsKeyDown(KEY_Q)) camera.zoom -= CAMERA_ZOOM_SPEED;
        if (camera.zoom < 0) camera.zoom = 0;
        if (IsKeyDown(KEY_E)) camera.zoom += CAMERA_ZOOM_SPEED;


        BeginTextureMode(target); BeginMode2D(camera);
            ClearBackground(BLACK);
            for (int i = 0; i < world->planets_i; ++i)
            {
                draw_planet_prev_path(world->planets[i]);
            }
            for (int i = 0; i < world->planets_i; ++i)
            {
                planet_t *p = world->planets[i];
                DrawCircle(p->x, p->y, p->r, colors[p->id]);
            }
        EndMode2D(); EndTextureMode();
        BeginDrawing();
            ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
            BeginShaderMode(shader);
                DrawTextureRec(target.texture, (Rectangle){0, 0, (float)WIDTH, -(float)HEIGHT}, (Vector2){0, 0}, WHITE);
            EndShaderMode();
            DrawRectangle(0, 0, 220, HEIGHT, GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
            DrawLine(220, 0, 220, HEIGHT, DARKGREEN);
            DrawFPS(0, 0);
            GuiToggle((Rectangle){60, 40, 140, 30}, "Pause", &paused);
            GuiSliderBar((Rectangle){60, 100, 140, 30}, "Gravity", "", &world->gravity, 0, 10000);
            GuiSliderBar((Rectangle){60, 160, 140, 30}, "Time", "", &time_scale, 0, 2);
        EndDrawing();


    }

    CloseWindow();
    UnloadShader(shader);
    UnloadRenderTexture(target);
    world_destroy(world);
    return 0;
}
