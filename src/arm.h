#pragma once
#include "raylib.h"

class Arm {
public:
    float link1Length;
    float link2Length;

    float shoulderAngle;
    float elbowAngle;

    Vector2 basePos;
    Vector2 elbowPos;
    Vector2 endEffectorPos;

    Arm(float startX, float startY, float l1, float l2);
    void ComputeIK(Vector2 targetPos);
    void ComputeFK();
    void Draw();
    void UpdateHardwareServos();
};
