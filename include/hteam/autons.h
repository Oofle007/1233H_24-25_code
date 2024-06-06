#ifndef INC_1233H_24_25_CODE_AUTONS_H
#define INC_1233H_24_25_CODE_AUTONS_H

#include "arm.h"
#include "lemlib/chassis/chassis.hpp"

class Autons {
public:
    Autons(std::shared_ptr<Arm> arm, std::shared_ptr<lemlib::Chassis> chassis);

    void red1();
    void red2();
    void red3();
    void red4();
    void blue1();
    void blue2();
    void blue3();
    void blue4();

    void skills();
private:
    std::shared_ptr<Arm> arm;
    std::shared_ptr<lemlib::Chassis> chassis;
};
#endif //INC_1233H_24_25_CODE_AUTONS_H
