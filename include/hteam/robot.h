#include "pros/apix.h"
#include "lemlib/api.hpp"
#include <algorithm>

#ifndef INC_1233H_24_25_CODE_ROBOT_H
#define INC_1233H_24_25_CODE_ROBOT_H

enum Color {
    BLUE, RED
};

class Intake {
public:
    explicit Intake(std::int8_t firstStagePort, std::int8_t secondStagePort, std::int8_t miniRollerPort);

    void outtakeTop();
    void outtakeBottom(bool closePneumatic=true);
    void outtakeMiddle();
    void intakeNoOuttake(bool closePneumatic=true);
    void stopIntake();

    pros::adi::DigitalOut intakePneumatic;
    pros::Distance distanceSensor;

    pros::Motor firstStageMotor;
    pros::Motor secondStageMotor;
    pros::Motor miniRollerMotor;

};

class Robot {
public:
    Robot();

    bool matchLoaderPneumaticState;
    bool parkPneumaticState;
    pros::adi::DigitalOut matchLoaderPneumatic;
    pros::adi::DigitalOut parkPneumatic;


    Intake intake;

    pros::MotorGroup leftMotors;
    pros::MotorGroup rightMotors;
    lemlib::Drivetrain drivetrain;
    lemlib::ControllerSettings lateralController;
    lemlib::ControllerSettings angularController;

    pros::Rotation verticalEncoder;

    lemlib::TrackingWheel verticalTrackingWheel;
    pros::Imu imu;

    lemlib::OdomSensors sensors;
    lemlib::ExpoDriveCurve throttle_curve;
    lemlib::ExpoDriveCurve steer_curve;

    lemlib::Chassis chassis;
};

#endif //INC_1233H_24_25_CODE_ROBOT_H
