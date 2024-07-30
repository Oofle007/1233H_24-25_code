#include "../include/hteam/arm.h"
#include "pros/rtos.hpp"

void Arm::moveToPosition(float fourBarTarget, float twoBarTarget, float threshold) {
    this->fourBarTarget = fourBarTarget;
    this->twoBarTarget = twoBarTarget;
    this->threshold = threshold;
    settled = false;

    pros::Task armTask(moveTask, this, "ArmMoveTask");
}

void Arm::moveTask(void* param) {
    Arm* arm = static_cast<Arm*>(param);
    while (true) {
        arm->mutex.take(); // Lock the mutex to ensure exclusive access
        if (!arm->settled) {
            float fourBarError = arm->fourBarTarget - arm->fourBar.get_position();
            float fourBarOutput = arm->fourBarPID.update(fourBarError);
            arm->fourBar.move_voltage(fourBarOutput * 12000);

            float twoBarError = arm->twoBarTarget - arm->twoBar.get_position();
            float twoBarOutput = arm->twoBarPID.update(twoBarError);
            arm->twoBar.move_voltage(twoBarOutput);
            arm->settled = (std::abs(fourBarError) < arm->threshold);

            std::cout << arm->settled << std::endl;

            if (arm->settled) {
                arm->mutex.give();
                arm->fourBar.move_voltage(0);
                break;
            }
        }
        arm->mutex.give();
        pros::delay(20);
    }
}

void Arm::reset_positions() {
    fourBar.tare_position();
    twoBar.tare_position();
}

void Arm::open() {}

void Arm::close() {}

Arm::Arm(const std::int8_t fourBarPort, const std::int8_t twoBarPort, const pros::v5::MotorGears gearset) :
        fourBar(fourBarPort, gearset),
        twoBar(twoBarPort, gearset),
        fourBarPID(2, // kP
                   0, // kI
                   1, // kD
                   0, // integral anti-windup range
                   true), // don't reset integral when sign of error flips
        twoBarPID(0, // kP
                  0, // kI
                  0, // kD
                  0, // integral anti-windup range
                  false),// don't reset integral when sign of error flips
                  settled(false),
                  fourBarTarget(0),
                  twoBarTarget(0),
                  threshold(0),
                  mutex() {
}

double Arm::getFourBarPosition() {
    return fourBar.get_position();
}

void Arm::waitUntilDone() {
    while (!isDone()) {
        pros::delay(20);
    }
}

bool Arm::isDone() {
    mutex.take();  // Lock the mutex before accessing 'settled'
    bool result = settled;
    mutex.give();
    return result;  // Unlock the mutex after accessing 'settled'
}

void Arm::moveVoltage(std::int32_t fourBarVoltage, std::int32_t twoBarVoltage) {
    fourBar.move_voltage(fourBarVoltage);
    twoBar.move_voltage(twoBarVoltage);
}

