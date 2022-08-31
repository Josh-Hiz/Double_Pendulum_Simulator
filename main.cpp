#include <iostream>
#include "raylib.h"
#include "includes/pendulum.h"
#include <rlgl.h>
#include <cmath>

void _testPendulum();

pendulum pen1;
pendulum pen2;

int main() {

    float theta1 = 45.0f;
    float theta2 = -45.0f;

    pen1.setMass(20.0f);
    pen1.setLength(150.0f);
    pen1.setAngle(theta1); //Can only set this once and cant anywhere else, why?
    pen1.setX(pen1.pLength,pen1.getAngle());
    pen1.setY(pen1.pLength, pen1.getAngle());

    std::cout << "X coord: " << pen1.getX() << " Y coord: " << pen1.getY() << std::endl;

    pen2.setMass(50.0f);
    pen2.setLength(150.0f);
    pen2.setAngle(theta2); //Can only set this once and cant anywhere else, why?
    pen2.setX( pen2.pLength,pen2.getAngle());
    pen2.setY( pen2.pLength,pen2.getAngle());
    pen2.x = pen1.getX() + pen2.getX();
    pen2.y = pen1.getY() + pen2.getY();

    std::cout << "X coord: " << pen2.getX() << " Y coord: " << pen2.getY() << std::endl;

    Vector2 origin{0,0};

    double screenWidth = 800;
    double screenHeight = 800;

    float px1 = pen1.getX();
    float py1 = pen1.getY();

    float px2 = pen2.getX();
    float py2 = pen2.getY();

    Vector2 rod1{px1,py1};
    Vector2 rod2 {px2, py2};

    /**--------------------------TEST VARIABLES--------------------------*/
    //Pendulum 1 & 2 properties:
    float l1 = 150.0f; //Length 1
    float l2 = 150.0f; //Length 2

    float m1 = 20.0f;
    float m2 = 20.0f;

    static float angle1 = 0.0f * DEG2RAD;
    static float angle2 = 0.0f * DEG2RAD;

    //First pendulum x & y
    float x1 = l1 * sin(theta1);
    float y1 = l1 * cos(theta1);

    //Second pendulum x & y
    float x2 = x1 + (l2 * sin(theta2));
    float y2 = y1 + (l2 * cos(theta2));
    /**--------------------------TEST VARIABLES--------------------------*/

    InitWindow((int) screenWidth, (int) screenHeight, "Double-Pendulum-Sim");

    int state = 0;
    int frameCounter = 0;

    SetTargetFPS(60);


    while (!WindowShouldClose()) {

        /**------------------Update------------------*/
        if(state == 0) {

            frameCounter++;
            theta1 = (float) frameCounter;
            pen1.setAngle(theta1);

            if(frameCounter >= 500) {
                frameCounter = 0;
                state = 1;
            }

        } else if(state == 1) {

            frameCounter++;
            theta2 = (float) frameCounter;
            pen2.setAngle(theta2);

            if(frameCounter >= 600) {
                frameCounter = 0;
                state = 0;
            }
        }

    /**---------------------------------Draw-Pendulums---------------------------------- */
        BeginDrawing();

            ClearBackground(BLACK);

            DrawFPS(-350, -200);

            rlTranslatef(400,250,0);

            DrawLineEx(origin, rod1, 5.0f, RAYWHITE);
            DrawCircle(px1,py1,pen1.pMass,RAYWHITE);

            DrawLineEx(rod1, rod2, 5.0f, RAYWHITE);
            DrawCircle(px2,py2,pen2.pMass,RAYWHITE);

            std::cout << "Pendulum 1 X & Y: " << pen1.getX() << " " << pen1.getY() << std::endl;
            std::cout << "Pendulum 2 X & Y: " << pen2.getX() << " " << pen2.getY() << std::endl;

        EndDrawing();
    }


    CloseWindow();


    return 0;
}

//Test function
void _testPendulum() {

    try {
        pen1.setMass(20.0f);
        pen1.setLength(150.0f);
        pen1.setAngle(0.0f);
        pen1.setX(pen1.pLength,pen1.getAngle());
        pen1.setY(pen1.pLength, pen1.getAngle());

        std::cout << "X coord: " << pen1.getX() << " Y coord: " << pen1.getY() << std::endl;

        pen2.setMass(50.0f);
        pen2.setLength(150.0f);
        pen2.setAngle(0.0f);
        pen2.setX( pen2.pLength,pen2.getAngle());
        pen2.setY( pen2.pLength,pen2.getAngle());
        pen2.x = pen1.getX() + pen2.getX();
        pen2.y = pen1.getY() + pen2.getY();

        std::cout << "X coord: " << pen2.getX() << " Y coord: " << pen2.getY() << std::endl;

    } catch (const std::exception & e) {
        std::cout << e.what();
    }

}


