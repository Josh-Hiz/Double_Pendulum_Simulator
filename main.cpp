#include <iostream>
#include "raylib.h"
#include "includes/pendulum.h"
#include <rlgl.h>
#include <cmath>

void _testPendulum();

pendulum pen1;
pendulum pen2;


int main() {


    //Prompt to make the initial values themselves
    float uLength1, uLength2, uMass1, uMass2, uAngle1, uAngle2;

    try {

        std::cout << "Please choose the length of each pendulum, starting with Pendulum 1, then Pendulum 2. Each value provided can be up to 7 decimal digits" << "\n";
        std::cin >> uLength1 >> uLength2;
        std::cout << "Please choose the mass of each pendulum, starting with Pendulum 1, then Pendulum 2. Each value provided can be up to 7 decimal digits" << "\n";
        std::cin >> uMass1 >> uMass2;
        std::cout << "Please choose the starting angle of each pendulum, starting with Pendulum 1, then Pendulum 2. Each value provided can be up to 7 decimal digits" << "\n";
        std::cin >> uAngle1 >> uAngle2;

    } catch (const std::exception & e) {
        std::cout << e.what();
    }



    pen1.setMass(uMass1);
    pen1.setLength(uLength1);
    pen1.setAngle(uAngle1); //Can only set this once and cant anywhere else, why?
    pen1.setX(pen1.pLength,pen1.getAngle());
    pen1.setY(pen1.pLength, pen1.getAngle());

    std::cout << "X coord: " << pen1.getX() << " Y coord: " << pen1.getY() << std::endl;

    pen2.setMass(uMass2);
    pen2.setLength(uLength2);
    pen2.setAngle(uAngle2); //Can only set this once and cant anywhere else, why?
    pen2.setX( pen2.pLength,pen2.getAngle());
    pen2.setY( pen2.pLength,pen2.getAngle());
    pen2.x = pen1.getX() + pen2.getX();
    pen2.y = pen1.getY() + pen2.getY();

    std::cout << "X coord: " << pen2.getX() << " Y coord: " << pen2.getY() << std::endl;

    Vector2 origin{0,0};

    double screenWidth = 800;
    double screenHeight = 800;

    InitWindow((int) screenWidth, (int) screenHeight, "Double-Pendulum-Sim");

    int frameCounter = 0;

    SetTargetFPS(60);

    float px1 = pen1.getX();
    float py1 = pen1.getY();

    float px2 = pen2.getX();
    float py2 = pen2.getY();

    while (!WindowShouldClose()) {


        Vector2 rod1{px1,py1};
        Vector2 rod2 {px2, py2};

        /**------------------Update------------------*/

            frameCounter++;
            uAngle1 = (float) frameCounter;
            pen1.setAngle(uAngle1); //Can only set this once and cant anywhere else, why?
            pen1.setX(pen1.pLength,pen1.getAngle());
            pen1.setY(pen1.pLength, pen1.getAngle());

            px1 = pen1.getX();
            py1 = pen1.getY();

            uAngle2 += 5.0f;
            pen2.setAngle(uAngle2); //Can only set this once and cant anywhere else, why?
            pen2.setX( pen2.pLength,pen2.getAngle());
            pen2.setY( pen2.pLength,pen2.getAngle());
            pen2.x = pen1.getX() + pen2.getX();
            pen2.y = pen1.getY() + pen2.getY();

            px2 = pen2.getX();
            py2 = pen2.getY();


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


