#include "pros/apix.h"
#include "lemlib/api.hpp"
#include <algorithm>

#ifndef INC_1233H_24_25_CODE_ROBOT_H
#define INC_1233H_24_25_CODE_ROBOT_H

class Arm {
public:
    Arm(std::int8_t motor1Port, std::int8_t motor2Port);

    void startArmTask();
    void setPosition(int position);
    void setZeroPosition();
private:
    lemlib::PID armPID;
    pros::MotorGroup armMotors;

    double targetPosition;

    pros::Mutex mutex;
    static void armTask(void* param);
};

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

    bool mogoPneumaticState;
    bool doinkerPneumaticState;
    pros::adi::DigitalOut mogoPneumatic;
    pros::adi::DigitalOut doinkerPneumatic;

    Intake intake;
    Arm arm;

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
};

#endif //INC_1233H_24_25_CODE_ROBOT_H
