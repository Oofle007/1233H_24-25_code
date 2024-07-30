#include "pros/apix.h"
#include "lemlib/chassis/chassis.hpp"

#ifndef INC_1233H_24_25_CODE_ROBOT_H
#define INC_1233H_24_25_CODE_ROBOT_H

class Robot {
public:
    Robot();

    bool pneumatic_state;
    pros::adi::DigitalOut mogoPneumatic;

    pros::Motor intake1;
    pros::Motor intake2;
    pros::Motor lift;

    pros::MotorGroup leftMotors;
    pros::MotorGroup rightMotors;
    lemlib::Drivetrain drivetrain;
    lemlib::ControllerSettings lateralController;
    lemlib::ControllerSettings angularController;

    pros::adi::Encoder horizontalEncoder;
    pros::adi::Encoder verticalEncoder;

    lemlib::TrackingWheel horizontalTrackingWheel;
    lemlib::TrackingWheel verticalTrackingWheel;
    pros::Imu imu;

    lemlib::OdomSensors sensors;
    lemlib::ExpoDriveCurve throttle_curve;
    lemlib::ExpoDriveCurve steer_curve;

    lemlib::Chassis chassis;
};

#endif //INC_1233H_24_25_CODE_ROBOT_H
