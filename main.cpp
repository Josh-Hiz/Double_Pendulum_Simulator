#include <iostream>
#include "raylib.h"
#include "includes/pendulum.h"
#include <rlgl.h>
#include <cmath>

int main() {


    Vector2 origin{0,0};

    double screenWidth = 800;
    double screenHeight = 800;

    //Pendulum 1 & 2 properties:
    float l1 = 150.0f; //Length 1
    float l2 = 150.0f; //Length 2

    float m1 = 20.0f;
    float m2 = 20.0f;

    static float theta1 = 0.0f;
    static float theta2 = 0.0f;

    //First pendulum x & y
    float x1 = l1 * sin(theta1);
    float y1 = l1 * cos(theta1);

    //Second pendulum x & y
    float x2 = x1 + (l2 * sin(theta2));
    float y2 = y1 + (l2 * cos(theta2));

    Vector2 rod1{x1,y1};
    Vector2 rod2 {x2, y2};

    InitWindow((int) screenWidth, (int) screenHeight, "Double-Pendulum-Sim");

    SetTargetFPS(60);

    float num = 5.0f * DEG2RAD;

    while (!WindowShouldClose()) {

    /**---------------------------------Draw-Pendulums---------------------------------- */
        BeginDrawing();
            ClearBackground(BLACK);

            DrawFPS(-350, -200);

            rlTranslatef(400,250,0);

            DrawLineEx(origin, rod1, 5.0f, RAYWHITE);
            DrawCircle(x1,y1,m1,RAYWHITE);

            DrawLineEx(rod1, rod2, 5.0f, RAYWHITE);
            DrawCircle(x2,y2,m2,RAYWHITE);

            theta1 += num;
            theta2 += num;

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
