//      _              _
//     / \     _   _  | |_    ___    _ __    ___
//    / _ \   | | | | | __|  / _ \  | '_ \  / __|
//   / ___ \  | |_| | | |_  | (_) | | | | | \__ \
//  /_/   \_\  \__,_|  \__|  \___/  |_| |_| |___/

#include <utility>
#include "../include/hteam/autons.h"

Autons::Autons(std::shared_ptr<Robot> robot) : robot(std::move(robot)) {

}

void Autons::red1() {  // RSWP
    // RED 1

    // Set Starting Position
    robot->chassis.setPose(-59, -16.5, 0);

    // Push blue ring out of the way
    robot->intake1.move_voltage(-6000);
    robot->chassis.moveToPoint(-59, 10, 10000, {.maxSpeed=50});
    // robot->chassis.moveToPose(-59, 11, 0, 10000);

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
    pros::delay(500);

    // Go to stack of rings and grab 1 and intake it onto mogo
    robot->chassis.turnToHeading(200, 1000);
    robot->chassis.moveToPoint(-18, -40, 10000, {}, false);

    pros::delay(1500);

    // Release MOGO so rings aren't touching the bot
    robot->mogoPneumatic.set_value(false);
    robot->pneumatic_state = false;

    // Touch ladder
    robot->chassis.moveToPose(-30, -9, 0, 3000, {.maxSpeed=80}, false);

    // Stop intake
    robot->intake1.move_voltage(0);
    robot->intake2.move_voltage(0);

}

void Autons::red2() { // L4MOGO
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
    robot->chassis.moveToPoint(-24, 45, 10000);

    // Back up to not pick up opponents ring
    robot->chassis.moveToPoint(-26, 43, 10000, {.forwards=false, .minSpeed=40, .earlyExitRange=2});

    // Get left ring of the two
    robot->chassis.moveToPoint(-11, 54, 10000, {.maxSpeed=60, .minSpeed=1, .earlyExitRange=2});

    // Back up
    robot->chassis.moveToPoint(-20, 44, 10000, {.forwards=false});

    // Get last ring
    robot->chassis.turnToPoint(-10, 44, 10000, {.minSpeed=1, .earlyExitRange=10});
    robot->chassis.moveToPoint(-10, 44, 10000, {.maxSpeed=80});

    // Back up
    robot->chassis.moveToPoint(-26, 40, 10000, {.forwards=false}, false);

    pros::delay(1000);

    // Release MOGO so rings aren't touching the bot
    robot->mogoPneumatic.set_value(false);
    robot->pneumatic_state = false;

    // Touch the ladder
    robot->chassis.moveToPose(-27, 9, 180, 10000);
}

void Autons::red3() {

}

void Autons::red4() {

}

void Autons::blue1() {  // RSWP
    // RED 1

    // Set Starting Position
    robot->chassis.setPose(59, -16.5, 0);

    // Push blue ring out of the way
    robot->intake1.move_voltage(-6000);
    robot->chassis.moveToPoint(59, 11, 10000, {.maxSpeed=50});

    // Line up to alliance stake and score
    robot->chassis.swingToHeading(-90, lemlib::DriveSide::RIGHT, 10000);
    robot->chassis.moveToPoint(60.5, 0, 10000, {}, false);

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
    robot->chassis.moveToPoint(50, 0, 10000);
    pros::delay(1500);

    // Get red ring
    robot->chassis.moveToPoint(42, -10, 10000);

    // Grab MOGO
    robot->intake2.move_voltage(0);
    robot->chassis.moveToPose(12, -28, 70, 10000, { .forwards=false, .minSpeed=1, .earlyExitRange=2}, false);
    robot->mogoPneumatic.set_value(true);
    robot->pneumatic_state = true;
    pros::delay(500);

    // Score intaked ring on MOGO
    robot->intake1.move_voltage(6000);
    robot->intake2.move_voltage(12000);
    pros::delay(500);

    // Go to stack of rings and grab 1 and intake it onto mogo
    robot->chassis.turnToHeading(-200, 1000);
    robot->chassis.moveToPoint(18, -40, 10000, {}, false);

    pros::delay(1500);

    // Release MOGO so rings aren't touching the bot
    robot->mogoPneumatic.set_value(false);
    robot->pneumatic_state = false;

    // Touch ladder
    robot->chassis.moveToPose(30, -6, 0, 3000, {.maxSpeed=80}, false);

    // Stop intake
    robot->intake1.move_voltage(0);
    robot->intake2.move_voltage(0);
}

void Autons::blue2() { // L4MOGO
    // Set starting Pose
    robot->chassis.setPose(53.75, 24, 90);

    // Drive and get MOGO
    robot->chassis.moveToPoint(28, 24, 10000, {.forwards=false, .maxSpeed=80, .minSpeed=1, .earlyExitRange=1}, false);
    robot->mogoPneumatic.set_value(true);
    robot->pneumatic_state = true;

    // Make sure MOGO is on all the way
    pros::delay(500);

    // Start intake
    robot->intake1.move_voltage(6000);
    robot->intake2.move_voltage(12000);

    pros::delay(1000);

    // Get first red ring right next to MOGO
    robot->chassis.moveToPoint(24, 47, 10000);

    // Get left ring of the two
    robot->chassis.moveToPoint(11, 54, 10000, {.maxSpeed=60, .minSpeed=1, .earlyExitRange=2});

    // Back up
    robot->chassis.moveToPoint(20, 45, 10000, {.forwards=false});

    // Get last ring
    robot->chassis.moveToPoint(10, 46, 10000, {.maxSpeed=60});

    // Back up
    robot->chassis.moveToPoint(26, 40, 10000, {.forwards=false}, false);

    pros::delay(500);

    // Release MOGO so rings aren't touching the bot
    robot->mogoPneumatic.set_value(false);
    robot->pneumatic_state = false;


    robot->chassis.moveToPose(27, 9, 180, 10000, {}, false);
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
    robot->chassis.moveToPoint(-45, 28, 10000, {.forwards=false, .maxSpeed=60, .minSpeed=1,.earlyExitRange=3}, false);
    robot->mogoPneumatic.set_value(true);
    pros::delay(500);

    // Get red ring
    robot->intake1.move_voltage(6000);
    robot->intake2.move_voltage(12000);
    robot->chassis.moveToPoint(-28, 24, 10000);
    pros::delay(1000);

    // Go to Wall Stake Ring
    robot->chassis.moveToPose(0, 60, 45,10000, {.minSpeed=1, .earlyExitRange=0.2});

    // Collect 3 ring clump
    robot->chassis.turnToHeading(-96, 1000);
    robot->chassis.moveToPose(-58, 49, -90,10000, {.maxSpeed=60});
    pros::delay(3000);

    // Get ring right next to it
    robot->chassis.moveToPose(-35, 63, 80, 10000, {.minSpeed=3});

    // Put mogo in corner
    robot->chassis.moveToPoint(-60, 63, 10000, {.forwards=false}, false);
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
    pros::delay(500);
    robot->intake2.move_voltage(12000);

    // Get 2 rings (drives to wall stake)
    robot->chassis.turnToHeading(135, 10000);
    robot->chassis.moveToPose(0, -55, 100, 10000, {.lead=0.3});

    // Get 2 ring line in 3 ring group
    robot->chassis.moveToPoint(-18, -46, 10000, {.forwards=false});
//    pros::delay(1500); // Ring needs to be in the intake
    robot->chassis.turnToHeading(-90, 10000);
    robot->chassis.moveToPose(-53, -46, -90, 10000);
    pros::delay(2000);

    // Get final red ring
    robot->chassis.moveToPose(-22, -58, 100, 10000, {.minSpeed=1, .earlyExitRange=1});

    // Put MOGO in corner
    robot->chassis.moveToPoint(-50, -58, 10000, {.forwards=false, .minSpeed=3, .earlyExitRange=3.5}, false);
    pros::delay(500);
    robot->mogoPneumatic.set_value(false);
    robot->intake2.move_voltage(-12000);
    pros::delay(500);

    // Keep first stage going for a ring going across the field for blue alliance stake
    robot->intake2.move_voltage(0);

    // -------------- 1st MOGO --------------
    robot->chassis.moveToPose(50, 8, 10, 10000, {.minSpeed=5, .earlyExitRange=3}); // Drive across the field
    robot->chassis.turnToHeading(-30, 10000);
    robot->intake1.move_voltage(0);
    robot->chassis.moveToPoint(65, -45, 10000, {.forwards=false});
    robot->mogoPneumatic.set_value(false);

    // Put other in the corner
    robot->chassis.moveToPose(66, 68, 5, 3500, {.lead=0.5, .minSpeed=50, .earlyExitRange=3});

    // Score on alliance stake
    robot->chassis.moveToPoint(48, 10, 10000, {.forwards=false});
    robot->chassis.turnToHeading(-90, 10000);
    robot->chassis.moveToPose(64.5, 7, -90, 2000, {.forwards=false}, false);
    robot->intake1.move_voltage(6000);
    robot->intake2.move_voltage(12000);
    pros::delay(1000);
    robot->intake1.move_voltage(0);
    robot->intake2.move_voltage(0);

    // Hang
    robot->chassis.moveToPoint(28, 28, 10000);
    robot->chassis.turnToHeading(-135, 10000);
    robot->lift.move_voltage(12000);
    pros::delay(1000);
    robot->chassis.moveToPose(0, 0, -135, 2000, {.maxSpeed=39});
    robot->chassis.moveToPoint(100, 100, 50, {.forwards=false, .minSpeed=100}); // GET ROBOT OFF OF BAR IT GO FAST
    robot->chassis.moveToPoint(-100, -100, 50, {.minSpeed=100}); // GO OTHER WAY
    robot->lift.move_voltage(0);
}
