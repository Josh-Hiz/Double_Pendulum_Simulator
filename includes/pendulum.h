//
// Created by Josh Hizgiaev on 8/30/22.
//

#ifndef DOUBLE_PENDULUM_SIM_PENDULUM_H
#define DOUBLE_PENDULUM_SIM_PENDULUM_H


class pendulum {
public:

    float pLength{};
    float pMass{};
    float x{};
    float y{};
    float pAngle{};

public:

    [[nodiscard]] float getX() const ;
    [[nodiscard]] float getY() const ;

    [[nodiscard]] float getAngle() const ;

    void setX(float length, float angle);
    void setY(float length, float angle);

    void setLength(float length);
    void setMass(float mass);
    void setAngle(float angle);

    pendulum();

    pendulum(float length, float mass, float angle) : pLength(length), pMass(mass), pAngle(angle) {}

    ~pendulum();


};

#endif //DOUBLE_PENDULUM_SIM_PENDULUM_H
