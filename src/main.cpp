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

// LADY BROWN HEIGHTS
const int MOGO_POSITION = 10;
const int RING1_POSITION = 333;
const int RING2_POSITION = 0;
const int SCORE_POSITION = 220;

std::shared_ptr<Robot> robot = std::make_shared<Robot>();

int intakeVolt = 0;

Autons autons(robot);

// Create interface object
Interface interface;

void initialize() {
    robot->chassis.calibrate(); // calibrate sensors
    robot->intake.startIntakeTask();  // Start the intake task
    robot->arm.startArmTask();  // Start the arm task
}

void disabled() {}

void competition_initialize() {
    interface.run();
}

void autonomous() {
    robot->intake.disableColorSorting();

    auto auton = interface.getSelectedAuton();
    switch (auton) {
        case NONE:
            break;
        case RED_1:
            robot->intake.setAllowedColor(RED);
            autons.red1();
            break;
        case RED_2:
            robot->intake.setAllowedColor(RED);
            autons.red2();
            break;
        case RED_3:
            robot->intake.setAllowedColor(RED);
            autons.red3();
            break;
        case RED_4:
            robot->intake.setAllowedColor(RED);
            autons.red4();
            break;
        case BLUE_1:
            robot->intake.setAllowedColor(BLUE);
            autons.blue1();
            break;
        case BLUE_2:
            robot->intake.setAllowedColor(BLUE);
            autons.blue2();
            break;
        case BLUE_3:
            robot->intake.setAllowedColor(BLUE);
            autons.blue3();
            break;
        case BLUE_4:
            robot->intake.setAllowedColor(BLUE);
            autons.blue4();
            break;
        case SKILLS:
            robot->intake.setAllowedColor(RED);
            autons.skills();
            break;
    }

    autons.red2();
}

void opcontrol() {
    robot->intake.setVoltage(0);
    robot->intake.disableColorSorting();
    robot->arm.setPosition(0);

    while (true) {

        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

        intakeVolt = 0;

        // Detect Button presses
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {  // Intake Forward
            intakeVolt = 12000;
        }

        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {  // Intake Reverse
            intakeVolt = -12000;
        }

        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {  // LB Score Position
            robot->arm.setPosition(150);
        }

        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {  // LB Mogo Position
            robot->arm.setPosition(0);
        }

        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)) {  // LB Ring 1 Position
            robot->arm.setPosition(29);
        }

        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) { // Almost score position
            robot->arm.setPosition(115);
        }

//        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {  // LB Ring 2 Position
//            robot->arm.setPosition(RING2_POSITION);
//        }



        robot->intake.setVoltage(intakeVolt);

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
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) {  // 'Down' button used for toggle
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

        pros::screen::print(pros::E_TEXT_MEDIUM, 50, 15, "X: %f", robot->chassis.getPose().x);
        pros::screen::print(pros::E_TEXT_MEDIUM, 50, 30, "Y: %f", robot->chassis.getPose().y);
        pros::screen::print(pros::E_TEXT_MEDIUM, 50, 45, "Theta: %f", robot->chassis.getPose().theta);

        pros::delay(10); // delay to prevent overloading the CPU
    }
}

