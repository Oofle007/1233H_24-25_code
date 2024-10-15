#include "pros/apix.h"
#include "lemlib/chassis/chassis.hpp"

#ifndef INC_1233H_24_25_CODE_ROBOT_H
#define INC_1233H_24_25_CODE_ROBOT_H

class Robot {
public:
    Robot();

    bool mogoPneumaticState;
    bool doinkerPneumaticState;
    pros::adi::DigitalOut mogoPneumatic;
    pros::adi::DigitalOut liftPneumatic;
    pros::adi::DigitalOut doinkerPneumatic;

    pros::Motor intake1;
    pros::Motor intake2;

    pros::MotorGroup leftMotors;
    pros::MotorGroup rightMotors;
    lemlib::Drivetrain drivetrain;
    lemlib::ControllerSettings lateralController;
    lemlib::ControllerSettings angularController;

    lemlib::PID intake2PID;

    pros::Rotation horizontalEncoder;
    pros::Rotation verticalEncoder;

    lemlib::TrackingWheel horizontalTrackingWheel;
    lemlib::TrackingWheel verticalTrackingWheel;
    pros::Imu imu;

    lemlib::OdomSensors sensors;
    lemlib::ExpoDriveCurve throttle_curve;
    lemlib::ExpoDriveCurve steer_curve;

    lemlib::Chassis chassis;

    pros::Optical opticalSensor;

    std::string allowedColor;

    bool liftUp;

//    void colorSort(std::int32_t requestedVoltage, bool sort)
};

#endif //INC_1233H_24_25_CODE_ROBOT_H
