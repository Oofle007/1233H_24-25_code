#include "main.h"
#include "lemlib/api.hpp"
#include "pros/llemu.hpp"
#include "hteam/arm.h"
#include "hteam/interface.h"
#include "hteam/autons.h"

// Controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

// Define Motors
pros::MotorGroup leftMotors({-1, -2, -20}, pros::MotorGearset::blue);
pros::MotorGroup rightMotors({10, 11, 3}, pros::MotorGearset::blue);

// Define Encoders
pros::adi::Encoder horizontalEncoder('A', 'B');
pros::adi::Encoder verticalEncoder('C', 'D');

// Define Tracking Wheels
lemlib::TrackingWheel horizontalTrackingWheel(&horizontalEncoder, lemlib::Omniwheel::NEW_275, -5);
lemlib::TrackingWheel verticalTrackingWheel(&verticalEncoder, lemlib::Omniwheel::NEW_275, 1.25);

// IMU
pros::Imu imu(12);


// Declare Arm object
std::shared_ptr<Arm> arm = std::make_shared<Arm>(8, 15, pros::MotorGearset::green);

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
                                             3, // anti-windup
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
                                             3, // anti-windup
                                             1, // small error range, in degrees
                                             100, // small error range timeout, in milliseconds
                                             3, // large error range, in degrees
                                             500, // large error range timeout, in milliseconds
                                             0 // maximum acceleration (slew)
);

// Exponential drive curve for the throttle
lemlib::ExpoDriveCurve throttle_curve(3, // joystick deadband out of 127
                                      10, // minimum output where drivetrain will move out of 127
                                      1.019 // expo curve gain
);

// Exponential drive curve for steering
lemlib::ExpoDriveCurve steer_curve(3, // joystick deadband out of 127
                                   10, // minimum output where drivetrain will move out of 127
                                   1.019 // expo curve gain
);

// Define Chassis
std::shared_ptr<lemlib::Chassis> chassis = std::make_shared<lemlib::Chassis>(drivetrain,
                                                                             lateralController,
                                                                             angularController,
                                                                             sensors,
                                                                             &throttle_curve,
                                                                             &steer_curve
);

Autons autons(arm, chassis);

// Create our interface object
Interface interface;

void center_callback() {
    // Reset all lift motor values
    arm->reset_positions();
}

void initialize() {
    chassis->calibrate(); // calibrate sensors
}

void disabled() {}

void competition_initialize() {
    interface.run();
}

void autonomous() {
    auto auton = interface.getSelectedAuton();
    switch (auton) {
        case NONE:
            break;
        case RED_1:
            autons.red1();
            break;
        case RED_2:
            autons.red2();
            break;
        case RED_3:
            autons.red3();
            break;
        case RED_4:
            autons.red4();
            break;
        case BLUE_1:
            autons.blue1();
            break;
        case BLUE_2:
            autons.blue2();
            break;
        case BLUE_3:
            autons.blue3();
            break;
        case BLUE_4:
            autons.blue4();
            break;
        case SKILLS:
            autons.skills();
            break;
    }

//    arm->moveToPosition(400, 0, 1);
//    arm->waitUntilDone();
//    pros::lcd::print(4, "Arm Done", arm->getFourBarPosition());
}

void opcontrol() {
    while (true) {
        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

        // Detect Button presses
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
            arm->moveVoltage(12000, 0); // Move motor forward at full power (12000 mV)
        }
            // Check if the button R2 is pressed
        else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
            arm->moveVoltage(-12000, 0); // Move motor backward at full power (12000 mV)
        } else {
            arm->moveVoltage(0, 0); // Stop the motor
        }

        // Move bot with split-arcade drive
        chassis->arcade(leftY, rightX);

        pros::delay(20); // delay to prevent overloading the CPU
    }
}

