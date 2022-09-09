//
// Created by Josh Hizgiaev on 9/8/22.
//

#include <fstream>
#include <ostream>
#include "../includes/GenerateFile.h"
#include <boost/math/special_functions/round.hpp>

constexpr int maxstring{1024};
constexpr int maxLines{5000};
const char * fileName = "Values.txt";

namespace bs = boost::math;

void GenerateFile::getData(const std::string & frameCount, const std::string & angle1, const std::string & x1, const std::string & y1, const std::string & angle2, const std::string & x2, const std::string & y2) {



    if(file.is_open() && std::stoi(frameCount) <= maxLines) {
        //Very crude but it works!
        file << angle1 << "  | " << x1 << "  | " << y1 << "  | " << angle2 << "  | " << x2 << "  | " << y2 << "  | " << frameCount << std::endl;

    } else {
        file.close();
    }



}
