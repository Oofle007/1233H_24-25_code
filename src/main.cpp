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

std::shared_ptr<Robot> robot = std::make_shared<Robot>();

Autons autons(robot);

// Create interface object
Interface interface;

void initialize() {
    robot->parkPneumatic.set_value(true);  // Flip to up
    robot->chassis.calibrate(); // calibrate sensors
    robot->intake.intakePneumatic.set_value(false);
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
}

void opcontrol() {



    while (true) {
        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {  //  INTAKE
            robot->intake.intakeNoOuttake();
        } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {  // BOTTOM
            robot->intake.outtakeBottom();
        } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {  // TOP
            robot->intake.outtakeTop();
        } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {  // MIDDLE
            robot->intake.outtakeMiddle();
        } else {
            robot->intake.stopIntake();
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

        // Move bot with split-arcade drive
        robot->chassis.arcade(leftY, rightX);

        pros::screen::print(pros::E_TEXT_MEDIUM, 1, "X: %f", robot->chassis.getPose().x);
        pros::screen::print(pros::E_TEXT_MEDIUM, 2, "Y: %f", robot->chassis.getPose().y);
        pros::screen::print(pros::E_TEXT_MEDIUM, 3, "Theta: %f", robot->chassis.getPose().theta);
        pros::screen::print(pros::E_TEXT_MEDIUM, 4, "Distance: %d mm", robot->intake.distanceSensor.get_distance());



        pros::delay(10); // delay to prevent bad things
    }
}

