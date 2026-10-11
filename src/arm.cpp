#include "Arm.h"
#include "raylib.h"
#include <cmath>

Arm::Arm(float startX, float startY, float l1, float l2) {
    basePos.x = startX;
    basePos.y = startY;
    link1Length = l1;
    link2Length = l2;
    shoulderAngle = 0.0f;
    elbowAngle = 0.0f;
}

void Arm::ComputeFK() {
    elbowPos.x = basePos.x + (link1Length * cosf(shoulderAngle));
    elbowPos.y = basePos.y + (link1Length * sinf(shoulderAngle));

    endEffectorPos.x = elbowPos.x + (link2Length * cosf(shoulderAngle + elbowAngle));
    endEffectorPos.y = elbowPos.y + (link2Length * sinf(shoulderAngle + elbowAngle));
}

void Arm::ComputeIK(Vector2 targetPos) {
    float dx = targetPos.x - basePos.x;
    float dy = targetPos.y - basePos.y;
    float D = sqrtf(dx * dx + dy * dy);

    float maxLength = link1Length + link2Length;
    if (D >= maxLength) {
        return;
    }

    float cosElbow = (D * D - link1Length * link1Length - link2Length * link2Length) / (2.0f * link1Length * link2Length);
    
    if (cosElbow < -1.0f) cosElbow = -1.0f;
    if (cosElbow > 1.0f) cosElbow = 1.0f;

    elbowAngle = acosf(cosElbow);

    float baseHeading = atan2f(dy, dx);

    float cosAlpha = (link1Length * link1Length + D * D - link2Length * link2Length) / (2.0f * link1Length * D);
    
    if (cosAlpha < -1.0f) cosAlpha = -1.0f;
    if (cosAlpha > 1.0f) cosAlpha = 1.0f;

    float alpha = acosf(cosAlpha);

    shoulderAngle = baseHeading - alpha;

    ComputeFK();
}

void Arm::Draw() {
    DrawLineEx(basePos, elbowPos, 10.0f, DARKGRAY);
    DrawLineEx(elbowPos, endEffectorPos, 8.0f, BLUE);

    DrawCircleV(basePos, 8.0f, BLACK);
    DrawCircleV(elbowPos, 6.0f, BLACK);
    DrawCircleV(endEffectorPos, 5.0f, RED); 
}

void Arm::UpdateHardwareServos() {
    // future stm32 hooks
}
