#include "main.h"
#include "pedometer.h"




//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(0, 0, "raylib [core] example - basic window");
    SetTargetFPS(-1); // unlimited fps (in theory)
    //--------------------------------------------------------------------------------------
    KeepScreenOn(true);
    InitAudioDevice();

    pedometer_t *pedometer = load_pedometer();

    char text[20] = "            ";

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);
        sprintf(text, "Step count :%d", pedometer->step_counter);
        DrawCircleV((Vector2) {100+50* GetAccelerometerLinearX(), 100+50* GetAccelerometerLinearY()}, 20, BLUE);

        update_pedometer(pedometer);


        DrawText(text, 0, 20, 20, LIGHTGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    CloseAudioDevice();
    unload_pedometer(pedometer);

    return 0;
}
