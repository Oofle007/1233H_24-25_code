//   ____            _               _
//  |  _ \    ___   | |__     ___   | |_
//  | |_) |  / _ \  | '_ \   / _ \  | __|
//  |  _ <  | (_) | | |_) | | (_) | | |_
//  |_| \_\  \___/  |_.__/   \___/   \__|

#include "hteam/robot.h"

Robot::Robot() : matchLoaderPneumaticState(false), matchLoaderPneumatic('H'),
                 parkPneumaticState(false), parkPneumatic('G'),
                 intake(19, -18, 9),
                 leftMotors({-12, -14, -15}, pros::MotorGearset::blue), // Rear, Middle, Front
                 rightMotors({13, 16, 17}, pros::MotorGearset::blue),
                 drivetrain(&leftMotors, // left motors
                            &rightMotors, // right motors
                            12.5, // Track Width
                            3.25, // Wheel
                            480, // Drive RPM
                            2 // Horizontal Drift
                 ),
                 lateralController(6, // proportional gain (kP)
                                   0, // integral gain (kI)
                                   7, // derivative gain (kD)
                                   0, // anti-windup
                                   1.5, // small error range, in inches
                                   100, // small error range timeout, in milliseconds
                                   3.5, // large error range, in inches
                                   300, // large error range timeout, in milliseconds
                                   127), // maximum acceleration (slew)
                 angularController(1.5, // proportional gain (kP)
                                   0, // integral gain (kI)
                                   7, // derivative gain (kD)
                                   0, // anti-windup
                                   1.5, // small error range, in degrees
                                   100, // small error range timeout, in milliseconds
                                   3.5, // large error range, in degrees
                                   500, // large error range timeout, in milliseconds
                                   90), // maximum acceleration (slew)
                 verticalEncoder(8),
                 verticalTrackingWheel(&verticalEncoder, 2, 0),
                 imu(11),
                 sensors(&verticalTrackingWheel, // Vertical Encoder
                         nullptr, // No second Vertical Encoder
                         nullptr, // Horizontal tracking wheel
                         nullptr, // No second Horizontal Encoder
                         &imu), // Inertial
                 throttle_curve(3, // joystick deadband out of 127
                                10, // minimum output where drivetrain will move out of 127
                                1.019), // expo curve gain
                 steer_curve(3, // joystick deadband out of 127
                             10, // minimum output where drivetrain will move out of 127
                             1), // expo curve gain
                 chassis(drivetrain,
                         lateralController,
                         angularController,
                         sensors,
                         &throttle_curve,
                         &steer_curve) {}


Intake::Intake(const std::int8_t firstStagePort, const std::int8_t secondStagePort, const std::int8_t miniRollerPort) :
        firstStageMotor(firstStagePort),
        secondStageMotor(secondStagePort),
        miniRollerMotor(miniRollerPort),
        intakePneumatic('E'),
        distanceSensor(20) {
}

void Intake::outtakeTop() {
    firstStageMotor.move_voltage(12000);
    secondStageMotor.move_voltage(12000);
    miniRollerMotor.move_voltage(6000);
    intakePneumatic.set_value(true);
}

void Intake::outtakeMiddle() {
    firstStageMotor.move_voltage(12000);
    secondStageMotor.move_voltage(6000);
    miniRollerMotor.move_voltage(-6000);
    intakePneumatic.set_value(false);
}

void Intake::outtakeBottom(const bool closePneumatic) {
    firstStageMotor.move_voltage(-12000);  // halfed wattage to go slower
    secondStageMotor.move_voltage(-6000);
    miniRollerMotor.move_voltage(-6000);
    if (closePneumatic) {
        intakePneumatic.set_value(false);
    }
}

void Intake::intakeNoOuttake(const bool closePneumatic) {
    firstStageMotor.move_voltage(12000);
    secondStageMotor.move_voltage(6000);
    miniRollerMotor.move_voltage(6000);
    if (closePneumatic) {
        intakePneumatic.set_value(false);
    }
}

void Intake::stopIntake() {
    firstStageMotor.move_voltage(0);
    secondStageMotor.move_voltage(0);
    miniRollerMotor.move_voltage(0);

    if (distanceSensor.get_distance() > 180) {
        intakePneumatic.set_value(false);
    }
}






