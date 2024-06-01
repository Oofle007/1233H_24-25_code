#include "main.h"
#include "lemlib/api.hpp"

// Define Motors
pros::MotorGroup leftMotors({1, 2, 3}, pros::MotorGearset::blue);
pros::MotorGroup rightMotors({4, 5, 6}, pros::MotorGearset::blue);

// Define Encoders
pros::adi::Encoder horizontalEncoder('A', 'B');
pros::adi::Encoder verticalEncoder('C', 'D');

// Define Tracking Wheels
lemlib::TrackingWheel horizontalTrackingWheel(&horizontalEncoder, lemlib::Omniwheel::NEW_275, 1.25);
lemlib::TrackingWheel verticalTrackingWheel(&verticalEncoder, lemlib::Omniwheel::NEW_275, 5);

// IMU
pros::Imu imu(10);

// Define the drivetrain
lemlib::Drivetrain drivetrain(&leftMotors, // left motors
                              &rightMotors, // right motors
                              12.5, // Track Width
                              lemlib::Omniwheel::NEW_275, // Wheel
                              450, // Drive RPM
                              2 // Horizontal Drift
);

// Define Sensors
lemlib::OdomSensors sensors(&verticalTrackingWheel, // Vertical tracking wheel
                            nullptr, // No second Vertical Encoder
                            &horizontalTrackingWheel, // Horizontal tracking wheel
                            nullptr, // No second Horizontal Encoder
                            &imu // Inertial
);

// Lateral PID controller
lemlib::ControllerSettings lateralController(10, // proportional gain (kP)
                                             0, // integral gain (kI)
                                             3, // derivative gain (kD)
                                             3, // anti windup
                                             1, // small error range, in inches
                                             100, // small error range timeout, in milliseconds
                                             3, // large error range, in inches
                                             500, // large error range timeout, in milliseconds
                                             20 // maximum acceleration (slew)
);

// Angular PID controller
lemlib::ControllerSettings angularController(2, // proportional gain (kP)
                                             0, // integral gain (kI)
                                             10, // derivative gain (kD)
                                             3, // anti windup
                                             1, // small error range, in degrees
                                             100, // small error range timeout, in milliseconds
                                             3, // large error range, in degrees
                                             500, // large error range timeout, in milliseconds
                                             0 // maximum acceleration (slew)
);

// Define Chassis
lemlib::Chassis chassis(drivetrain, // drivetrain settings
                        lateralController, // lateral PID settings
                        angularController, // angular PID settings
                        sensors // Sensors

);

void initialize() {
    pros::lcd::initialize(); // initialize brain screen
    chassis.calibrate(); // calibrate sensors
    // print position to brain screen
    pros::Task screen_task([&]() {
        while (true) {
            // Print robot Pose to the screen
            pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
            pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
            pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
            pros::delay(20); // don't starve cpu
        }
    });

}

void disabled() {}

void competition_initialize() {}

void autonomous() {

}

void opcontrol() {
    // Define controller
    pros::Controller controller(pros::E_CONTROLLER_MASTER);



    pros::delay(20); // delay to prevent overloading the CPU

}

