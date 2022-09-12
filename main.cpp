#include <iostream>
#include <fstream>
#include "raylib.h"
#include "includes/pendulum.h"
#include "includes/GenerateFile.h"
#include <cmath>

void testPendulum();

GenerateFile generator;

pendulum pen1;
pendulum pen2;

//The universal constant for gravity, for these purposes however, it can be any value as long as it works
const float g = 9.8;
const float dt = (1/10.0);

int main() {

    //Prompt to make the initial values themselves
    float uLength1, uLength2, uMass1, uMass2, uAngle1, uAngle2;

    //Recommendation: 100 200 for length, 20 25 for mass, 45 0 for angle
    try {

        std::cout << "Please choose the length of each pendulum, starting with Pendulum 1, then Pendulum 2. Each value provided can be up to 7 decimal digits, " << "\n" << "length MUST BE greater than 50 and less than 200" << "\n";
        std::cin >> uLength1 >> uLength2;
        std::cout << "Please choose the mass of each pendulum, starting with Pendulum 1, then Pendulum 2. Each value provided can be up to 7 decimal digits, " << "\n" << "mass MUST BE greater than 20 and less than 100" << "\n";
        std::cin >> uMass1 >> uMass2;
        std::cout << "Please choose the starting angle of each pendulum, starting with Pendulum 1, then Pendulum 2. Each value provided can be up to 7 decimal digits" << "\n";
        std::cin >> uAngle1 >> uAngle2;

    } catch (const std::exception & e) {
        std::cout << e.what();
    }

    //Init angular acceleration and angular velocity for pendulums

    float angularV1 = 0;
    float angularV2 = 0;

    //Pendulum 1 settings
    pen1.setMass(uMass1);
    pen1.setLength(uLength1);
    pen1.setAngle(uAngle1);
    pen1.setX(pen1.pLength,pen1.getAngle());
    pen1.setY(pen1.pLength, pen1.getAngle());

    std::cout << "X coord: " << pen1.getX() << " Y coord: " << pen1.getY() << std::endl;

    //Pendulum 2 settings
    pen2.setMass(uMass2);
    pen2.setLength(uLength2);
    pen2.setAngle(uAngle2); //Can only set this once and cant anywhere else, why?
    pen2.setX( pen2.pLength,pen2.getAngle());
    pen2.setY( pen2.pLength,pen2.getAngle());
    pen2.x = pen1.getX() + pen2.getX();
    pen2.y = pen1.getY() + pen2.getY();

    std::cout << "X coord: " << pen2.getX() << " Y coord: " << pen2.getY() << std::endl;

    //Window settings
    const double screenWidth = 1440;
    const double screenHeight = 1080;

    Vector2 origin{(float) screenWidth/2,(float) screenHeight/3};

    InitWindow((int) screenWidth, (int) screenHeight, "Double-Pendulum-Sim");

    int frameCounter = 0;

    SetTargetFPS(60);

    //Set coords for pendulums
    float px1 = pen1.getX() + origin.x;
    float py1 = pen1.getY() + origin.y;

    float px2 = pen2.getX() + origin.x;
    float py2 = pen2.getY() + origin.y;

    //Load & start pathing
    RenderTexture2D target = LoadRenderTexture((int) screenWidth, (int) screenHeight);

    BeginTextureMode(target);
    ClearBackground(RAYWHITE);
    EndTextureMode();

    /****Write data to a file*****/

    //Init new Values.txt file
    generator.file.open("Values.txt");

    if(!generator.file) {
        perror("Error finding or opening file");
    } else {
        std::cout << "File opened successfully" << std::endl;
    }
    generator.file << "Angle 1    | X_1         | Y_1         | Angle 2    | X_2         | Y_2         | Frame # " << std::endl;



    //Main while loop
    while (!WindowShouldClose()) {
        Vector2 rod1{px1,py1};
        Vector2 rod2 {px2, py2};

        //Implement angular acceleration for first pendulum equations:
        float num1 = -g * (2 * pen1.getMass() + pen2.getMass()) * sin(pen1.getAngle());
        float num2 = -pen2.getMass() * g * sin(pen1.getAngle() - 2 * pen2.getAngle());
        float num3 = -2 * sin(pen1.getAngle() - pen2.getAngle()) * pen2.getMass();
        float num4 = pow(angularV2, 2) * pen2.getLength() + pow(angularV1,2) * pen1.getLength() * cos(pen1.getAngle() - pen2.getAngle());
        float den1 = pen1.getLength() * (2*pen1.getMass() + pen2.getMass() - pen2.getMass() * cos(2*pen1.getAngle() - 2 * pen2.getAngle()));

        float angularA1 = ((num1 + num2 + num3*num4) / den1) * dt;

        //Angular acceleration for second pendulum:
         num1 = 2 * sin(pen1.getAngle() - pen2.getAngle());
         num2 = (pow(angularV1,2.0) * pen1.getLength() * (pen1.getMass() + pen2.getMass()));
         num3 = g * (pen1.getMass() + pen2.getMass()) * cos(pen1.getAngle());
         num4 = pow(angularV2,2.0) * pen2.getLength() * pen2.getMass() * cos(pen1.getAngle() - pen2.getAngle());
         den1 = pen2.getLength() * (2*pen1.getMass() + pen2.getMass() - pen2.getMass() * cos(2*pen1.getAngle() - 2*pen2.getAngle()));

        float angularA2 = ((num1 * (num2 + num3 + num4)) / den1) * dt;



        /**------------------Update------------------*/

            frameCounter++;
            uAngle1 += (RAD2DEG * (angularV1 * dt));
            angularV1 += angularA1;
            pen1.setAngle(uAngle1); //Can only set this once and cant anywhere else, why?
            pen1.setX(pen1.pLength,pen1.getAngle());
            pen1.setY(pen1.pLength, pen1.getAngle());

            px1 = pen1.getX() + origin.x;
            py1 = pen1.getY() + origin.y;

            uAngle2 += (RAD2DEG * (angularV2 * dt));
            angularV2 += angularA2;
            pen2.setAngle(uAngle2); //Can only set this once and cant anywhere else, why?
            pen2.setX( pen2.pLength,pen2.getAngle());
            pen2.setY( pen2.pLength,pen2.getAngle());
            pen2.x = pen1.getX() + pen2.getX();
            pen2.y = pen1.getY() + pen2.getY();

            px2 = pen2.getX() + origin.x;
            py2 = pen2.getY() + origin.y;

            //Write data to file by first getting the values of the pendulums:
            generator.getData(std::to_string(frameCounter),std::to_string(uAngle1),std::to_string(px1),std::to_string(px2),std::to_string(uAngle2),std::to_string(px2),std::to_string(py2));

    /**---------------------------------Draw-Pendulums & Path---------------------------------- */

    BeginDrawing();


            BeginTextureMode(target);
            DrawCircleV(rod2, 2.0f, RED);
//            DrawPixelV(rod2, RED);
            EndTextureMode();

            DrawTextureRec(target.texture, (Rectangle){0,0, (float) target.texture.width, (float) -target.texture.height}, (Vector2){0,0}, WHITE);

            ClearBackground(RAYWHITE);

            DrawFPS(100, 100);


            DrawLineEx(origin, rod1, 5.0f, BLACK);
            DrawCircle( px1,py1,pen1.pMass,BLACK);

            DrawLineEx(rod1, rod2, 5.0f, BLACK);
            DrawCircle(px2,py2,pen2.pMass,BLACK);

            std::cout << "Frame #: " <<  frameCounter << std::endl;
            std::cout << "Pendulum 1 Angle: " << uAngle1 << std::endl;
            std::cout << "Pendulum 2 Angle: " << uAngle2 << std::endl;
            std::cout << "Pendulum 1 X & Y: " << pen1.getX() << " " << pen1.getY() << std::endl;
            std::cout << "Pendulum 2 X & Y: " << pen2.getX() << " " << pen2.getY() << std::endl;

    EndDrawing();

    }

    CloseWindow();

    generator.file.close();

    std::cout << "Please view Values.txt to view your own data!";

    return 0;
}

//Test function
void testPendulum() {

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


