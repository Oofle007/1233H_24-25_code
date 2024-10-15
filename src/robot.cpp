//   ____            _               _
//  |  _ \    ___   | |__     ___   | |_
//  | |_) |  / _ \  | '_ \   / _ \  | __|
//  |  _ <  | (_) | | |_) | | (_) | | |_
//  |_| \_\  \___/  |_.__/   \___/   \__|

#include "hteam/robot.h"
Robot::Robot() : mogoPneumaticState(false), doinkerPneumaticState(false),
                 mogoPneumatic('C'), liftPneumatic('A'), doinkerPneumatic('F'),
                 intake1(-6), intake2(4),
                 leftMotors({-5, 1, -11}, pros::MotorGearset::blue), // Rear, Stacked, Front
                 rightMotors({9, -10, 20}, pros::MotorGearset::blue),
                 drivetrain(&leftMotors, // left motors
                            &rightMotors, // right motors
                            12.5, // Track Width
                            lemlib::Omniwheel::NEW_275, // Wheel
                            480, // Drive RPM
                            2 // Horizontal Drift
                 ),
                 lateralController(0, // proportional gain (kP)
                                   0, // integral gain (kI)
                                   0, // derivative gain (kD)
                                   0, // anti-windup
                                   1.5, // small error range, in inches
                                   100, // small error range timeout, in milliseconds
                                   3.5, // large error range, in inches
                                   500, // large error range timeout, in milliseconds
                                   50), // maximum acceleration (slew)
                 angularController(0, // proportional gain (kP)
                                   0, // integral gain (kI)
                                   0, // derivative gain (kD)
                                   0, // anti-windup
                                   1.5, // small error range, in degrees
                                   100, // small error range timeout, in milliseconds
                                   3.5, // large error range, in degrees
                                   500, // large error range timeout, in milliseconds
                                   90), // maximum acceleration (slew)
                 horizontalEncoder(13),
                 verticalEncoder(-8),
                 horizontalTrackingWheel(&horizontalEncoder, lemlib::Omniwheel::NEW_2, -0.09),
                 verticalTrackingWheel(&verticalEncoder, lemlib::Omniwheel::NEW_2, 1),
                 imu(12),
                 sensors(&verticalTrackingWheel, // No Vertical Encoder
                         nullptr, // No second Vertical Encoder
                         &horizontalTrackingWheel, // Horizontal tracking wheel
                         nullptr, // No second Horizontal Encoder
                         &imu), // Inertial
                 throttle_curve(3, // joystick deadband out of 127
                                10, // minimum output where drivetrain will move out of 127
                                1.019), // expo curve gain
                 steer_curve(3, // joystick deadband out of 127
                             10, // minimum output where drivetrain will move out of 127
                             1.019), // expo curve gain
                 chassis(drivetrain,
                         lateralController,
                         angularController,
                         sensors,
                         &throttle_curve,
                         &steer_curve),
                 opticalSensor(4),
                 allowedColor("Red"), // Auto Default sorting color to red
                 intake2PID(100,  // kP
                            0,  // DON'T CHANGE FROM 0 EVER
                            0,  // kD
                            0,  // integral anti windup range
                            false),  // don't reset integral when sign of error flips
                 liftUp(false) {
}

//void Robot::colorSort(std::int32_t requestedVoltage, bool sort) {
//    const float REVERSE_TIME = 0.5;  // Time that the intake will reverse in MILLISECONDS
//    const int MIN_PROXIMITY = 50; // Minimum proximity (distance) that the color sorter "detects" a ring
//    const double BLUE_RING_HUE = 200;
//    double timeStartReverse;  // The time in milliseconds when we set the intake to run in reverse
//
//    if (sort) {  // Only sort rings when specified to
//        if (opticalSensor.get_proximity() > MIN_PROXIMITY) {  // If there is a ring in front of the optical sensor
//            // If the ring detected is red and we want to only allow blue rings, reset our time stamp to start reversing
//            if ((allowedColor == "Blue" && opticalSensor.get_hue() <= BLUE_RING_HUE) || (allowedColor == "Red" && opticalSensor.get_hue() >= BLUE_RING_HUE)) {
//                timeStartReverse = pros::c::millis();
//
//        }
//    }
//
//    if (pros::c::millis() - timeStartReverse >= REVERSE_TIME) {
//        intake2.move_voltage(requestedVoltage);
//    } else {
//        intake2.move_voltage(-1 * abs(requestedVoltage));
//    }
//}
