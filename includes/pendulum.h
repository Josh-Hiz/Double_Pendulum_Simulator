//
// Created by Josh Hizgiaev on 8/30/22.
//

#ifndef DOUBLE_PENDULUM_SIM_PENDULUM_H
#define DOUBLE_PENDULUM_SIM_PENDULUM_H


class pendulum {
public:

    //Pendulum length
    float pLength{};

    //Pendulum mass
    float pMass{};

    //Pendulum's x component
    float x{};

    //Pendulum's y component
    float y{};

    //Pendulum's angular displacement relative to its origin
    float pAngle{};

public:

    void setAngularV(float angV);
    void setAngularA(float angA);

    [[nodiscard]] float getX() const ;
    [[nodiscard]] float getY() const ;

    [[nodiscard]] float getAngle() const ;
    [[nodiscard]] float getMass() const;
    [[nodiscard]] float getLength() const;

    void setX(float length, float angle);
    void setY(float length, float angle);

    void setLength(float length);
    void setMass(float mass);
    void setAngle(float angle);

    //Default constructor
    pendulum();

    //Easier way to initialize pendulum
    pendulum(float length, float mass, float angle) : pLength(length), pMass(mass), pAngle(angle) {}

    //De-constructor to make sure pendulum objects are destroyed
    ~pendulum();


};

#endif //DOUBLE_PENDULUM_SIM_PENDULUM_H
