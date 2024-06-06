#ifndef INC_1233H_24_25_CODE_ARM_H
#define INC_1233H_24_25_CODE_ARM_H

#include "../api.h"
#include "../lemlib/api.hpp"
#include <cmath>

class Arm {
public:
    Arm(std::int8_t fourBarPort, std::int8_t twoBarPort, pros::v5::MotorGears gearset);

    void moveToPosition(float fourBarTarget, float twoBarTarget, float threshold);
    void moveVoltage(std::int32_t fourBarVoltage, std::int32_t twoBarVoltage);
    void reset_positions();
    void open();
    void close();
    double getFourBarPosition();
    bool isDone();
    void waitUntilDone();

private:

    pros::Motor fourBar;
    pros::Motor twoBar;
    lemlib::PID fourBarPID;
    lemlib::PID twoBarPID;

    bool settled;
    float fourBarTarget;
    float twoBarTarget;
    float threshold;

    pros::Mutex mutex;

    static void moveTask(void* param);
};


#endif //INC_1233H_24_25_CODE_ARM_H
