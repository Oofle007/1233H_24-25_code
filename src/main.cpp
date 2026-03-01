//   __  __           _
//  |  \/  |   __ _  (_)  _ __
//  | |\/| |  / _` | | | | '_ \
//  | |  | | | (_| | | | | | | |
//  |_|  |_|  \__,_| |_| |_| |_|

#include "main.h"
#include "hteam/interface.h"
#include "hteam/autons.h"
#include "hteam/robot.h"


// Controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

// Define a variable to store the previous state of the button
bool matchLoaderButtonPressed = false;
bool intakeButtonPressed = false;
bool descoreButtonPressed = false;

pros::Distance cubeDetector = pros::Distance(2);
bool parkPneumaticState = true;

std::shared_ptr<Robot> robot = std::make_shared<Robot>();

Autons autons(robot);

// Create interface object
Interface interface;

void initialize() {
    robot->parkPneumatic.set_value(true);  // Flip to up
    robot->chassis.calibrate(); // calibrate sensors
    robot->intake.intakePneumatic.set_value(true);
    robot->descorePneumatic.set_value(false);
}

void disabled() {}

void competition_initialize() {
    interface.run();
}

void autonomous() {
    robot->descorePneumatic.set_value(true);
    robot->descorePneumaticState = true;

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
    //autons.red4();
    //autons.red1();
}

void opcontrol() {

    controller.print(0, 0, "Vex");
    controller.clear();
    while (true) {
        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {  //  INTAKE
            robot->intake.intakeNoOuttake();
        } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {  // BOTTOM
            robot->intake.outtakeBottom();
        } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {  // MIDDLE
            robot->intake.outtakeMiddle();
        } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)) {  // HOLD for park
            if (cubeDetector.get_distance() < 100) {  // Cube Detected
                robot->parkPneumatic.set_value(false);  // PARK
                parkPneumaticState = false;
                robot->intake.intakeNoOuttake();
                pros::delay(100);
                robot->intake.stopIntake();
            } else {  // Spin the intake to find a cube
                if (parkPneumaticState) {
                    robot->intake.outtakeBottom();  // only spin when park is UP
                }
            }
        } else {
            robot->intake.stopIntake();
        }

        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {  // If the driver messed up the park
            robot->parkPneumatic.set_value(true);  // UN-PARK
            parkPneumaticState = true;
        }

        // Detect button press for toggling the MOGO pneumatic
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_B)) {  // 'B' button used for toggle
            if (!matchLoaderButtonPressed) {  // Toggle only when the button is pressed, not held
                robot->matchLoaderPneumaticState = !robot->matchLoaderPneumaticState;  // Toggle the pneumatic state
                robot->matchLoaderPneumatic.set_value(robot->matchLoaderPneumaticState);  // Set the pneumatic to the new state
                matchLoaderButtonPressed = true;  // Update the button pressed state
            }
        } else {
            matchLoaderButtonPressed = false;  // Reset the button pressed state when the button is released
        }

        // Detect button press for toggling the INTAKE pneumatic
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {  // 'L1' button used for toggle
            if (!intakeButtonPressed) {  // Toggle only when the button is pressed, not held
                robot->intake.intakePneumaticState = !robot->intake.intakePneumaticState;  // Toggle the pneumatic state
                robot->intake.intakePneumatic.set_value(robot->intake.intakePneumaticState);  // Set the pneumatic to the new state
                intakeButtonPressed = true;  // Update the button pressed state
            }
        } else {
            intakeButtonPressed = false;  // Reset the button pressed state when the button is released
        }

        // Detect button press for toggling the DESCORE pneumatic
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {  // 'DOWN' button used for toggle
            if (!descoreButtonPressed) {  // Toggle only when the button is pressed, not held
                robot->descorePneumaticState = !robot->descorePneumaticState;  // Toggle the pneumatic state
                robot->descorePneumatic.set_value(robot->descorePneumaticState);  // Set the pneumatic to the new state
                descoreButtonPressed = true;  // Update the button pressed state
            }
        } else {
            descoreButtonPressed = false;  // Reset the button pressed state when the button is released
        }

        // Move bot with split-arcade drive
        robot->chassis.arcade(leftY, rightX);

        pros::screen::print(pros::E_TEXT_MEDIUM, 1, "X: %f", robot->chassis.getPose().x);
        pros::screen::print(pros::E_TEXT_MEDIUM, 2, "Y: %f", robot->chassis.getPose().y);
        pros::screen::print(pros::E_TEXT_MEDIUM, 3, "Theta: %f", robot->chassis.getPose().theta);
        pros::screen::print(pros::E_TEXT_MEDIUM, 4, "Distance: %d mm", robot->intake.distanceSensor.get_distance());
        pros::screen::print(pros::E_TEXT_MEDIUM, 5, "Cube Detector: %d mm", cubeDetector.get_distance());

        int leftDriveHeat = robot->leftMotors.get_temperature();  // Get left motor temperature
        int rightDriveHeat = robot->rightMotors.get_temperature(); // Get right motor temperature

        // Display Drive Heat on Controller
        controller.set_text(0, 0, ("Drive Heat: " + std::to_string((leftDriveHeat + rightDriveHeat) / 2) + "%").c_str());

        pros::delay(10); // delay to prevent bad things
    }
}

