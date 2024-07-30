#include <utility>
#include "../include/hteam/autons.h"

Autons::Autons(std::shared_ptr<Robot> robot) : robot(std::move(robot)) {

}

void Autons::red1() {  // RIGHT SOLO WP
    // RED 1

    // Set Starting Position
    robot->chassis.setPose(-59, -16.8, 0);

    // Push blue ring out of the way
    robot->intake1.move_voltage(-6000);
    robot->chassis.moveToPose(-59, 10, 0, 10000);

    // Line up to alliance stake and score
    robot->chassis.swingToHeading(90, lemlib::DriveSide::LEFT, 10000);
    robot->chassis.moveToPoint(-60.5, 0, 10000, {}, false);

    // Spin intake for .5 seconds
    robot->intake1.move_voltage(6000);
    robot->intake2.move_voltage(12000);
    pros::delay(500);

    // Make sure intake is off of alliance stake just in case it didn't score fully

    robot->intake1.move_voltage(-6000);
    robot->intake2.move_voltage(-12000);
    pros::delay(200);

    robot->intake1.move_voltage(6000);
    robot->intake2.move_voltage(12000);

    // Push blue ring out of the way
    robot->chassis.moveToPoint(-50, 0, 10000);
    pros::delay(1500);

    // Get red ring
    robot->chassis.moveToPoint(-42, -10, 10000);

    // Grab MOGO
    robot->intake2.move_voltage(0);
    robot->chassis.moveToPose(-12, -28, -70, 10000, { .forwards=false, .minSpeed=1, .earlyExitRange=2}, false);
    robot->mogoPneumatic.set_value(true);
    robot->pneumatic_state = true;

    // Score intaked ring on MOGO
    robot->intake1.move_voltage(6000);
    robot->intake2.move_voltage(12000);

    // Go to stack of rings and grab 1 and intake it onto mogo
    robot->chassis.turnToHeading(200, 1000);
    robot->chassis.moveToPoint(-18, -40, 10000, {}, false);

    // Touch ladder
    robot->chassis.moveToPose(-30, -9, 0, 10000, {.maxSpeed=80}, false);

    pros::delay(5000);

    // Stop intake
    robot->intake1.move_voltage(0);
    robot->intake2.move_voltage(0);
}

void Autons::red2() {

}

void Autons::red3() {

}

void Autons::red4() {

}

void Autons::blue1() {
    //  LEFT 75% WP

    // Set starting Pose
    robot->chassis.setPose(-53.75, 24, -90);

    // Drive and get MOGO
    robot->chassis.moveToPoint(-28, 24, 10000, {.forwards=false, .maxSpeed=80, .minSpeed=1, .earlyExitRange=1}, false);
    robot->mogoPneumatic.set_value(true);
    robot->pneumatic_state = true;

    // Make sure MOGO is on all the way
    pros::delay(500);

    // Start intake
    robot->intake1.move_voltage(6000);
    robot->intake2.move_voltage(12000);

    pros::delay(1000);

    // Get first red ring right next to MOGO
    robot->chassis.moveToPoint(-24, 47, 10000);

    // Get left ring of the two
    robot->chassis.moveToPose(-11, 54, 90, 10000, {.maxSpeed=60});

    // Back up
    robot->chassis.moveToPoint(-20, 48, 10000, {.forwards=false});

    // Get last ring
    robot->chassis.moveToPose(-10, 46, 90, 10000, {.maxSpeed=60});

    // Back up
    robot->chassis.moveToPoint(-26, 46, 10000, {.forwards=false});
    robot->chassis.moveToPose(-27, 9, 180, 10000);
}

void Autons::blue2() {

}

void Autons::blue3() {

}

void Autons::blue4() {

}

void Autons::skills() {
    // Set initial position
    robot->chassis.setPose(-61.5, 0, 90);

    // Score on alliance stake
    robot->intake2.move_voltage(12000);
    pros::delay(450);
    robot->intake2.move_voltage(0);

    // Make sure intake isn't on alliance stake
    robot->intake2.move_voltage(-12000);
    pros::delay(150);
    robot->intake2.move_voltage(0);

    // Get and Grab MOGO
    robot->chassis.moveToPoint(-55, 0, 10000);
    robot->chassis.moveToPoint(-45, 28, 10000, {.forwards=false, .maxSpeed=70, .minSpeed=1,.earlyExitRange=3}, false);
    robot->mogoPneumatic.set_value(true);
    pros::delay(500);

    // Get red ring
    robot->intake1.move_voltage(6000);
    robot->intake2.move_voltage(12000);
    robot->chassis.moveToPose(-24, 24, 90, 10000, {.minSpeed=1, .earlyExitRange=2});
    pros::delay(1000);

    // Go to Wall Stake Ring
    robot->chassis.moveToPose(0, 60, 45,10000, {.minSpeed=1, .earlyExitRange=0.2});

    // Collect 3 ring clump
    robot->chassis.turnToHeading(-96, 1000);
    robot->chassis.moveToPose(-58, 50, -90,10000, {.maxSpeed=60});

    // Get ring right next to it
    robot->chassis.moveToPose(-45, 60, 80, 10000, {.minSpeed=3});

    // Put mogo in corner
    robot->chassis.turnToHeading(135, 10000);
    robot->chassis.moveToPoint(-60, 60, 10000, {.forwards=false});
    robot->mogoPneumatic.set_value(false);
    robot->intake2.move_voltage(-12000);
    pros::delay(500);
    robot->intake2.move_voltage(12000);

    // -------------- NEXT QUADRANT --------------

    // Go get red ring on other side of field
    robot->chassis.moveToPose(-22, -22, 135, 10000, {}, false);
    robot->intake2.move_voltage(0);

    // Grab MOGO
    robot->chassis.moveToPoint(-46, -22, 10000, {.forwards=false, .maxSpeed=70, .minSpeed=1, .earlyExitRange=2}, false);
    robot->mogoPneumatic.set_value(true);
    robot->intake2.move_voltage(12000);
    pros::delay(500);

    // Get 2 rings (drives to wall stake)
    robot->chassis.turnToHeading(135, 10000);
    robot->chassis.moveToPose(0, -55, 100, 10000, {.lead=0.3});

    // Get 2 ring line in 3 ring group
    robot->chassis.moveToPoint(-18, -46, 10000, {.forwards=false});
    robot->chassis.turnToHeading(-90, 10000);
    robot->chassis.moveToPose(-53, -46, -90, 10000);

    // Get final red ring
    robot->chassis.moveToPose(-32, -58, 100, 10000, {.minSpeed=1, .earlyExitRange=1});

    // Put MOGO in corner
    robot->chassis.moveToPoint(-50, -58, 10000, {.forwards=false, .minSpeed=3, .earlyExitRange=3.5}, false);
    pros::delay(3000);
    robot->mogoPneumatic.set_value(false);
    robot->intake2.move_voltage(-12000);
    pros::delay(500);
    robot->intake1.move_voltage(0);
    robot->intake2.move_voltage(0);

    // -------------- 1st MOGO --------------
    robot->chassis.moveToPose(50, 12, 10, 10000); // Drive across the field
    robot->chassis.turnToHeading(-30, 10000);
    robot->chassis.moveToPoint(48, -48, 10000, {.forwards=false});
}
