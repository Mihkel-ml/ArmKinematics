#include "raylib.h"
#include "Arm.h"
#include <cmath>

int main() {
    InitWindow(1280, 720, "Kinematics Control Engine");
    SetTargetFPS(60);

    Arm myArm(640.0f, 200.0f, 200.0f, 150.0f);

    while (!WindowShouldClose()) {
        float runningTime = GetTime();

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            Vector2 mouseTarget = GetMousePosition();
            myArm.ComputeIK(mouseTarget);
        }
        else {
            Vector2 baseVec;
            baseVec.x = myArm.basePos.x;
            baseVec.y = myArm.basePos.y + myArm.link1Length + myArm.link2Length - 2.0f;
            myArm.ComputeIK(baseVec);
        }

        BeginDrawing();
        ClearBackground(WHITE);

        myArm.Draw();

        DrawText("Testing Forward Kinematics Model Pipeline...", 20, 20, 20, DARKGRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
