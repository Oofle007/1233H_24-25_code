#include "pros/apix.h"
#include "lemlib/chassis/chassis.hpp"

#ifndef INC_1233H_24_25_CODE_ROBOT_H
#define INC_1233H_24_25_CODE_ROBOT_H

enum Color {
    BLUE, RED
};

class Intake {
public:
    explicit Intake(std::int8_t intakePort);
    void startIntakeTask();
    void enableColorSorting();
    void disableColorSorting();
    void holdIntake();
    void stopHoldingIntake();
    void setVoltage(std::int32_t voltage);
    void setAllowedColor(Color color);
private:
    pros::Motor intakeMotor;
    std::int32_t currentVoltage;
    bool holding;
    lemlib::PID holdPID;

    bool sortColors;
    Color allowedColor;
    pros::Optical opticalSensor;

    pros::Mutex mutex;
    static void intakeTask(void* param);
};

class Robot {
public:
    Robot();

    pros::adi::DigitalOut mogoPneumatic;
    pros::adi::DigitalOut liftPneumatic;
    pros::adi::DigitalOut doinkerPneumatic;

    pros::Motor intake1;
    Intake intake2;

    pros::MotorGroup leftMotors;
    pros::MotorGroup rightMotors;
    lemlib::Drivetrain drivetrain;
    lemlib::ControllerSettings lateralController;
    lemlib::ControllerSettings angularController;

    pros::Rotation horizontalEncoder;
    pros::Rotation verticalEncoder;

    lemlib::TrackingWheel horizontalTrackingWheel;
    lemlib::TrackingWheel verticalTrackingWheel;
    pros::Imu imu;

    lemlib::OdomSensors sensors;
    lemlib::ExpoDriveCurve throttle_curve;
    lemlib::ExpoDriveCurve steer_curve;

    lemlib::Chassis chassis;

    bool liftUp;
};

#endif //INC_1233H_24_25_CODE_ROBOT_H
