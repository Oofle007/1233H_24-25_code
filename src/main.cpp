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
bool mogoButtonPressed = false;
bool doinkerButtonPressed = false;

std::shared_ptr<Robot> robot = std::make_shared<Robot>();

int intake1_volt = 0;
int intake2_volt = 0;

Autons autons(robot);

// Create our interface object
Interface interface;

void initialize() {
    robot->chassis.calibrate(); // calibrate sensors
    robot->intake2.startIntakeTask();  // Start the intake task
    robot->intake2.enableColorSorting();
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
            robot->intake2.setAllowedColor(RED);
            autons.red1();
            break;
        case RED_2:
            robot->intake2.setAllowedColor(RED);
            autons.red2();
            break;
        case RED_3:
            robot->intake2.setAllowedColor(RED);
            autons.red3();
            break;
        case RED_4:
            robot->intake2.setAllowedColor(RED);
            autons.red4();
            break;
        case BLUE_1:
            robot->intake2.setAllowedColor(BLUE);
            autons.blue1();
            break;
        case BLUE_2:
            robot->intake2.setAllowedColor(BLUE);
            autons.blue2();
            break;
        case BLUE_3:
            robot->intake2.setAllowedColor(BLUE);
            autons.blue3();
            break;
        case BLUE_4:
            robot->intake2.setAllowedColor(BLUE);
            autons.blue4();
            break;
        case SKILLS:
            robot->intake2.setAllowedColor(RED);
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

        // Detect Button presses
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {  // 2nd stage intake
            intake2_volt = 12000;
        }

        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
            controller.rumble("-");
        }

        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {  // 1st stage intake
            intake1_volt = 12000;
        }

        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {  // Lift Up
            robot->liftUp = true;
            robot->intake2.holdIntake();
        }

        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {  // Lift Down
            robot->liftUp = false;
            robot->intake2.stopHoldingIntake();
        }

        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) { // Reverse Intake
            intake1_volt = -12000;
            intake2_volt = -12000;
        }

        robot->liftPneumatic.set_value(robot->liftUp);
        robot->intake1.move_voltage(intake1_volt);
        robot->intake2.setVoltage(intake2_volt);

        // Detect button press for toggling the MOGO pneumatic
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_B)) {  // 'B' button used for toggle
            if (!mogoButtonPressed) {  // Toggle only when the button is pressed, not held
                robot->mogoPneumaticState = !robot->mogoPneumaticState;  // Toggle the pneumatic state
                robot->mogoPneumatic.set_value(robot->mogoPneumaticState);  // Set the pneumatic to the new state
                mogoButtonPressed = true;  // Update the button pressed state
            }
        } else {
            mogoButtonPressed = false;  // Reset the button pressed state when the button is released
        }

        // Detect button press for toggling the DOINKER pneumatic
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {  // 'Down' button used for toggle
            if (!doinkerButtonPressed) {  // Toggle only when the button is pressed, not held
                robot->doinkerPneumaticState = !robot->doinkerPneumaticState;  // Toggle the pneumatic state
                robot->doinkerPneumatic.set_value(robot->doinkerPneumaticState);  // Set the pneumatic to the new state
                doinkerButtonPressed = true;  // Update the button pressed state
            }
        } else {
            doinkerButtonPressed = false;  // Reset the button pressed state when the button is released
        }

        // Move bot with split-arcade drive
        robot->chassis.arcade(leftY, rightX);

        // Print position
        pros::screen::print(pros::E_TEXT_MEDIUM, 50, 15, "X: %f", robot->chassis.getPose().x);
        pros::screen::print(pros::E_TEXT_MEDIUM, 50, 30, "Y: %f", robot->chassis.getPose().y);
        pros::screen::print(pros::E_TEXT_MEDIUM, 50, 45, "Theta: %f", robot->chassis.getPose().theta);

        pros::delay(10); // delay to prevent overloading the CPU
    }
}

