//
// Created by Josh Hizgiaev on 8/30/22.
//

#include "includes/pendulum.h"
#include <cmath>
#include <iostream>
#include <raylib.h>

void pendulum::setX(float length, float angle) {
    x = length * sin(angle);
}

void pendulum::setY(float length, float angle) {
    y = length * cos(angle);
}

float pendulum::getX() const {
    return x;
}

float pendulum::getY() const {
    return y;
}

void pendulum::setLength(float length) {
    pLength = length;
}

void pendulum::setMass(float mass) {
    pMass = mass;
}

float pendulum::getAngle() const {
    return pAngle;
}

pendulum::~pendulum() {
    std::cout << "Pendulum destroyed" << std::endl;
}

void pendulum::setAngle(float angle) {
    pAngle = angle * DEG2RAD;
}

//Default constructor
pendulum::pendulum() = default;

