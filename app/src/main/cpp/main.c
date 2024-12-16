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

    char text_1[100] = "                                      ";
    char text_2[100] = "                                      ";

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);
        sprintf(text_1, "Accelerometer step counter :%d", pedometer->step_counter_1);
        sprintf(text_2, "Gyroscope step counter :%d", pedometer->step_counter_2);
        DrawCircleV((Vector2) {100+50* GetAccelerometerLinearX(), 100+50* GetAccelerometerLinearY()}, 20, BLUE);

        update_pedometer(pedometer);


        DrawText(text_1, 50, 100, 50, LIGHTGRAY);
        DrawText(text_2, 50, 200, 50, LIGHTGRAY);

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
