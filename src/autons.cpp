//      _              _
//     / \     _   _  | |_    ___    _ __    ___
//    / _ \   | | | | | __|  / _ \  | '_ \  / __|
//   / ___ \  | |_| | | |_  | (_) | | | | | \__ \
//  /_/   \_\  \__,_|  \__|  \___/  |_| |_| |___/

#include <utility>
#include "../include/hteam/autons.h"

Autons::Autons(std::shared_ptr<Robot> robot) : robot(std::move(robot)) {

}

void Autons::red1() { // Red right
    robot->chassis.setPose(-53.6, -36, -90);

    // Grab MOGO
    robot->chassis.moveToPoint(-24, -24, 10000, {.forwards=false, .maxSpeed=65, .minSpeed=10, .earlyExitRange=1}, false);
    robot->mogoPneumatic.set_value(true);
    pros::delay(500);
    robot->intake.setVoltage(12000);
    pros::delay(700);

    // Get other ring
    robot->chassis.turnToHeading(-175, 10000, {.minSpeed=20, .earlyExitRange=20});
    robot->chassis.moveToPoint(-24, -48, 10000, {.minSpeed=10, .earlyExitRange=1}, false);
    pros::delay(1000);
    robot->intake.setVoltage(0);

    robot->chassis.turnToHeading(0, 10000, {.minSpeed=20, .earlyExitRange=20});
    robot->chassis.moveToPoint(-24, 0, 10000, {.maxSpeed=60});
}

void Autons::red2() {
    robot->chassis.setPose(-53.6, -36, -90);

    // Grab MOGO
    robot->chassis.moveToPoint(-24, -24, 10000, {.forwards=false, .maxSpeed=65, .minSpeed=10, .earlyExitRange=1}, false);
    robot->mogoPneumatic.set_value(true);
    pros::delay(500);
    robot->intake.setVoltage(12000);
    pros::delay(700);

    // Get other ring
    robot->chassis.turnToHeading(-175, 10000, {.minSpeed=20, .earlyExitRange=20});
    robot->chassis.moveToPoint(-24, -48, 10000, {.minSpeed=10, .earlyExitRange=1}, false);
    pros::delay(1000);
    robot->intake.setVoltage(0);

    robot->chassis.turnToHeading(90, 10000, {.minSpeed=5, .earlyExitRange=5});
    robot->chassis.moveToPoint(-7, 50, 10000, {.maxSpeed=40, .minSpeed=10, .earlyExitRange=1});
    robot->chassis.moveToPoint(-12, 45, 10000, {.forwards=false, .minSpeed=20, .earlyExitRange=2});
    robot->chassis.moveToPoint(-7, 48, 10000, {.maxSpeed=40, .minSpeed=10, .earlyExitRange=1});
    robot->chassis.moveToPoint(-30, 48, 10000, {.forwards=false, .minSpeed=20, .earlyExitRange=2});
    robot->chassis.turnToHeading(180, 10000, {.minSpeed=40, .earlyExitRange=20});
    robot->chassis.moveToPoint(-24, 0, 10000, {.maxSpeed=60});
}

void Autons::red3() {
    robot->chassis.setPose(-53, -53, 90);

    robot->chassis.moveToPoint(-35, -53, 10000);
}

void Autons::red4() {

}

void Autons::blue1() {
    robot->chassis.setPose(53.6, -36, 90);

    // Grab MOGO
    robot->chassis.moveToPoint(24, -24, 10000, {.forwards=false, .maxSpeed=65, .minSpeed=10, .earlyExitRange=1}, false);
    robot->mogoPneumatic.set_value(true);
    pros::delay(500);
    robot->intake.setVoltage(12000);
    pros::delay(700);

    // Get other ring
    robot->chassis.turnToHeading(175, 10000, {.minSpeed=20, .earlyExitRange=20});
    robot->chassis.moveToPoint(24, -48, 10000, {.minSpeed=10, .earlyExitRange=1}, false);
    pros::delay(1000);
    robot->intake.setVoltage(0);

    robot->chassis.turnToHeading(0, 10000, {.minSpeed=20, .earlyExitRange=20});
    robot->chassis.moveToPoint(24, 0, 10000, {.maxSpeed=60});
}

void Autons::blue2() {

}

void Autons::blue3() {

}

void Autons::blue4() {

}

void Autons::skills() {
    robot->chassis.setPose(-60, -32, -126);

    // Grab MOGO
    robot->chassis.moveToPoint(-48, -24, 10000, {.forwards=false, .maxSpeed=65, .minSpeed=10, .earlyExitRange=1}, false);
    robot->mogoPneumatic.set_value(true);
    pros::delay(500);
    robot->intake.setVoltage(12000);
    pros::delay(700);
    robot->intake.setVoltage(0);

    robot->chassis.turnToHeading(30, 10000, {.minSpeed=20, .earlyExitRange=20});
    robot->chassis.moveToPoint(-57, -54, 10000, {.forwards=false, .minSpeed=40, .earlyExitRange=3}, false);
    robot->mogoPneumatic.set_value(false);
    pros::delay(100);
    robot->chassis.moveToPoint(-48, 0, 10000, {.minSpeed=20, .earlyExitRange=2});
    robot->chassis.turnToHeading(-135, 10000, {.minSpeed=20, .earlyExitRange=20});
    robot->chassis.moveToPoint(-24, 24, 10000, {.forwards=false, .minSpeed=20, .earlyExitRange=2}, false);
    robot->mogoPneumatic.set_value(true);
    pros::delay(300);

    robot->chassis.turnToHeading(135, 10000, {.minSpeed=20, .earlyExitRange=20});
    robot->chassis.moveToPoint(-57, 54, 10000, {.forwards=false, .minSpeed=20, .earlyExitRange=2}, false);
    robot->mogoPneumatic.set_value(false);
    pros::delay(100);

    robot->chassis.moveToPoint(-12, 24, 10000, {.maxSpeed=50, .minSpeed=20, .earlyExitRange=2});
    robot->chassis.turnToHeading(-90, 10000, {.minSpeed=40, .earlyExitRange=20});
    robot->chassis.moveToPoint(56, 24, 10000, {.forwards=false, .minSpeed=20, .earlyExitRange=2}, false);
    robot->mogoPneumatic.set_value(true);
    pros::delay(300);

    robot->chassis.turnToHeading(180, 10000, {.minSpeed=40, .earlyExitRange=20});
    robot->chassis.moveToPoint(57, 54, 10000, {.forwards=false, .minSpeed=20, .earlyExitRange=2}, false);
    robot->mogoPneumatic.set_value(false);
    pros::delay(100);

    robot->chassis.moveToPoint(57, -54, 10000, {.minSpeed=100});
}
