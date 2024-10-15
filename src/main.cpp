//   __  __           _
//  |  \/  |   __ _  (_)  _ __
//  | |\/| |  / _` | | | | '_ \
//  | |  | | | (_| | | | | | | |
//  |_|  |_|  \__,_| |_| |_| |_|

#include "main.h"
#include "hteam/interface.h"
#include "hteam/autons.h"
#include "hteam/robot.h"
#include <sstream>

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
            robot->allowedColor = "Blue";
            autons.blue1();
            break;
        case BLUE_2:
            robot->allowedColor = "Blue";
            autons.blue2();
            break;
        case BLUE_3:
            robot->allowedColor = "Blue";
            autons.blue3();
            break;
        case BLUE_4:
            robot->allowedColor = "Blue";
            autons.blue4();
            break;
        case SKILLS:
            autons.skills();
            break;
    }
}

void opcontrol() {
    robot->opticalSensor.set_led_pwm(100);
    std::uint8_t INTAKE2TARGET = 0;
    while (true) {
        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

        intake1_volt = 0;
        intake2_volt = 0;
        bool allow = true;

        // Detect Button presses
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {  // 2nd stage intake
            if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
                intake2_volt = 0;
                robot->intake2.move_velocity(80);  // Spin intake slow
                allow = false;
            } else {
                intake2_volt = 12000;
                robot->intake2.set_zero_position(INTAKE2TARGET);
            }

        }

        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
            controller.rumble("-");
        }

        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {  // 1st stage intake
            intake1_volt = 12000;
        }

        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {  // Lift Up
            robot->liftUp = true;
            robot->intake2.set_zero_position(INTAKE2TARGET);
        }

        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {  // Lift Down
            robot->liftUp = false;
        }

        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) { // Reverse Intake
            intake1_volt = -12000;
            intake2_volt = -12000;
        }

        robot->liftPneumatic.set_value(robot->liftUp);
        robot->intake1.move_voltage(intake1_volt);

        if (allow) {
            robot->intake2.move_voltage(intake2_volt);
        }

        if (robot->liftUp && !controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
            robot->intake2.move_voltage(robot->intake2PID.update(INTAKE2TARGET - robot->intake2.get_position()));  // PID to keep the intake from moving when the lift is up so rings can't fall off
        }

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

        std::stringstream ss;
        ss << robot->opticalSensor.get_hue() << "|" << robot->opticalSensor.get_proximity();

        // Print position
        pros::screen::erase();
        pros::screen::print(pros::E_TEXT_MEDIUM, 50, 15, "X: %f", robot->chassis.getPose().x);
        pros::screen::print(pros::E_TEXT_MEDIUM, 50, 30, "Y: %f", robot->chassis.getPose().y);
        pros::screen::print(pros::E_TEXT_MEDIUM, 50, 45, "Theta: %f", robot->chassis.getPose().theta);
        pros::screen::print(pros::E_TEXT_MEDIUM, 50, 75, "Optical Hue|Prox: %s", ss.str());


        pros::delay(10); // delay to prevent overloading the CPU
    }
}

