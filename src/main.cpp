//   __  __           _
//  |  \/  |   __ _  (_)  _ __
//  | |\/| |  / _` | | | | '_ \
//  | |  | | | (_| | | | | | | |
//  |_|  |_|  \__,_| |_| |_| |_|

#include "main.h"
#include "hteam/interface.h"
#include "hteam/autons.h"
#include "hteam/robot.h"

ASSET(newPath_txt);
ASSET(testPath_txt);
ASSET(testPath2_txt);

// Controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

// Define a variable to store the previous state of the button
bool button_pressed = false;

std::shared_ptr<Robot> robot = std::make_shared<Robot>();

int intake1_volt = 0;
int intake2_volt = 0;
int lift_volt = 0;

Autons autons(robot);

// Create our interface object
Interface interface;

void initialize() {
    robot->chassis.calibrate(); // calibrate sensors
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

        intake1_volt = 0;
        intake2_volt = 0;
        lift_volt = 0;

        // Detect Button presses
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {  // 2nd stage intake
            intake2_volt = 12000;
        }

        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {  // 1st stage intake
            intake1_volt = 6000;
        }

        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {  // Lift Up
            lift_volt = 6000;
        }

        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {  // Lift Down
            lift_volt = -6000;
        }

        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) { // Reverse Intake
            intake1_volt = -6000;
            intake2_volt = -12000;
        }

        robot->intake1.move_voltage(intake1_volt);
        robot->intake2.move_voltage(intake2_volt);
        robot->lift.move_voltage(lift_volt);

        // Detect button press for toggling the pneumatic
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_B)) {  // Assume 'X' button is used for toggle
            if (!button_pressed) {  // Toggle only when the button is pressed, not held
                robot->pneumatic_state = !robot->pneumatic_state;  // Toggle the pneumatic state
                robot->mogoPneumatic.set_value(robot->pneumatic_state);  // Set the pneumatic to the new state
                button_pressed = true;  // Update the button pressed state
            }
        } else {
            button_pressed = false;  // Reset the button pressed state when the button is released
        }

        // Move bot with split-arcade drive
        robot->chassis.arcade(leftY, rightX);

        // Print position
        pros::screen::print(pros::E_TEXT_MEDIUM, 50, 15, "X: %f", robot->chassis.getPose().x);
        pros::screen::print(pros::E_TEXT_MEDIUM, 50, 30, "Y: %f", robot->chassis.getPose().y);
        pros::screen::print(pros::E_TEXT_MEDIUM, 50, 45, "Theta: %f", robot->chassis.getPose().theta);

        pros::delay(20); // delay to prevent overloading the CPU
    }
}

