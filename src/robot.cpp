#include "hteam/robot.h"

Robot::Robot() : pneumatic_state(false),
                 mogoPneumatic('F'),
                 intake1(16), intake2(-14), lift(-15),
                 leftMotors({-17, -13, -2}, pros::MotorGearset::blue),
                 rightMotors({7, 1, 20}, pros::MotorGearset::blue),
                 drivetrain(&leftMotors, // left motors
                            &rightMotors, // right motors
                            12.5, // Track Width
                            lemlib::Omniwheel::NEW_275, // Wheel
                            450, // Drive RPM
                            2 // Horizontal Drift
                 ),
                 lateralController(8.5, // proportional gain (kP)
                                   0.02, // integral gain (kI)
                                   6, // derivative gain (kD)
                                   0, // anti-windup
                                   1.5, // small error range, in inches
                                   100, // small error range timeout, in milliseconds
                                   3.5, // large error range, in inches
                                   500, // large error range timeout, in milliseconds
                                   50), // maximum acceleration (slew)
                 angularController(2.6, // proportional gain (kP)
                                   0, // integral gain (kI)
                                   10, // derivative gain (kD)
                                   0, // anti-windup
                                   1.5, // small error range, in degrees
                                   100, // small error range timeout, in milliseconds
                                   3.5, // large error range, in degrees
                                   500, // large error range timeout, in milliseconds
                                   90), // maximum acceleration (slew)
                 horizontalEncoder('G', 'H'),
                 verticalEncoder('C', 'D'),
                 horizontalTrackingWheel(&horizontalEncoder, lemlib::Omniwheel::NEW_275, -2.75),
                 verticalTrackingWheel(&verticalEncoder, lemlib::Omniwheel::NEW_275, -0.25),
                 imu(11),
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
                         &steer_curve) {


}
