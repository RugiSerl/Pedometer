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

        DrawCircleV((Vector2) {100+50* GetGyroscopeY(), 100+50* GetGyroscopeX()}, 20, BLUE);

        update_pedometer(pedometer);



        //DrawText(text, 190, 200, 20, LIGHTGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context

    unload_pedometer(pedometer);

    return 0;
}
