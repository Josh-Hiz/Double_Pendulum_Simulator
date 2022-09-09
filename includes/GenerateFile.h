//
// Created by Josh Hizgiaev on 9/8/22.
//

#ifndef DOUBLE_PENDULUM_SIM_GENERATEFILE_H
#define DOUBLE_PENDULUM_SIM_GENERATEFILE_H

#include <iostream>

class GenerateFile {

public:
    std::ofstream file;

    void getData(const std::string & frameCount, const std::string & angle1, const std::string & x1, const std::string & y1, const std::string & angle2, const std::string & x2, const std::string & y2);
};


#endif //DOUBLE_PENDULUM_SIM_GENERATEFILE_H
