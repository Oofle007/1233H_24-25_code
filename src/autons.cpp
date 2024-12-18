//      _              _
//     / \     _   _  | |_    ___    _ __    ___
//    / _ \   | | | | | __|  / _ \  | '_ \  / __|
//   / ___ \  | |_| | | |_  | (_) | | | | | \__ \
//  /_/   \_\  \__,_|  \__|  \___/  |_| |_| |___/

#include <utility>
#include "../include/hteam/autons.h"

Autons::Autons(std::shared_ptr<Robot> robot) : robot(std::move(robot)) {

}

void Autons::red1() { // RED RUSH
    robot->chassis.setPose(-55, -36, 90);

    // Rush center goal and pull it backwards
    // robot->chassis.turnToHeading(95, 100, {.minSpeed=40}, false);
    // robot->chassis.moveToPoint(-20, -56.5, 1500, {.minSpeed=10, .earlyExitRange=2}, false);
    robot->chassis.moveToPose(-23, -43, 125, 1000, {.lead=0.2, .minSpeed=90, .earlyExitRange=12}, false);
    // robot->chassis.turnToHeading(120, 10000, {.minSpeed=5, .earlyExitRange=5});
    robot->doinkerPneumatic.set_value(true);
    pros::delay(300);
    robot->chassis.moveToPoint(-20, -37, 10000, {.forwards=false, .maxSpeed=50, .minSpeed=40, .earlyExitRange=2}, false);
    robot->doinkerPneumatic.set_value(false);

    // Pick up MOGO and score Preload
    robot->chassis.moveToPoint(-27, -26, 10000, {.forwards=false, .maxSpeed=60, .minSpeed=10, .earlyExitRange=2}, false);
    robot->mogoPneumatic.set_value(true);
    pros::delay(200);
    robot->intake.setVoltage(12000);
    pros::delay(700);
    robot->mogoPneumatic.set_value(false);

    // Go to ring stack and intake the ring
    robot->chassis.turnToHeading(150, 1000, {.maxSpeed=90, .minSpeed=50, .earlyExitRange=5});
    robot->chassis.moveToPoint(-16, -63, 10000, {.maxSpeed=90, .minSpeed=5, .earlyExitRange=1});
    pros::delay(1000);
    robot->intake.setVoltage(0);

    // Pick up MOGO that got rushed
    robot->chassis.moveToPoint(-24, -45, 1000, {.forwards=false, .maxSpeed=80, .minSpeed=1, .earlyExitRange=1});
    robot->chassis.turnToHeading(-100, 500, {.minSpeed=5, .earlyExitRange=1});
    robot->chassis.moveToPoint(-7, -45, 1500, {.forwards=false, .maxSpeed=60}, false);
    robot->mogoPneumatic.set_value(true);
    pros::delay(100);
    robot->intake.setVoltage(12000);

    // CHOPED
    robot->chassis.moveToPoint(-24, -24, 800);
    robot->chassis.turnToHeading(90, 500);
    robot->chassis.moveToPoint(-0, -24, 1500, {.maxSpeed=50});

    // Go get ring next to alliance stake
//    robot->chassis.moveToPoint(-42, -46, 1500, {}, false);
//    robot->mogoPneumatic.set_value(false);
//    robot->chassis.turnToHeading(0, 500, {.minSpeed=5, .earlyExitRange=5});
//    robot->chassis.moveToPoint(-48, -14, 10000, {.maxSpeed=100, .minSpeed=10, .earlyExitRange=1});
//    pros::delay(1100);
//    robot->chassis.moveToPoint(-48, 6, 1000, {.minSpeed=10});
//    pros::delay(700);
//    robot->intake.setVoltage(0);
//
//    // Back up to push ring out of the way
//    robot->chassis.moveToPoint(-60, -14, 1200, {.forwards=false, .minSpeed=5, .earlyExitRange=4});
//    robot->chassis.turnToHeading(0, 500, {.minSpeed=5, .earlyExitRange=1});
//    robot->chassis.moveToPoint(-60, 5, 1500, {.maxSpeed=90});
//
//    // Score on alliance stake
//    robot->chassis.moveToPoint(-55, -4, 1000, {.forwards=false, .maxSpeed=60});
//    robot->chassis.turnToHeading(70, 500);
//    robot->chassis.moveToPoint(-64, -4, 600, {.forwards=false, .maxSpeed=70});
//    robot->chassis.moveToPoint(-56.5, -4, 600, {}, false);
//    robot->intake.setVoltage(12000);
//    pros::delay(600);
//    robot->intake.setVoltage(0);
//    robot->chassis.moveToPoint(-28, -3, 1500);
}

void Autons::red2() {  // RED SOLO WP
    robot->chassis.setPose(-60, 12.2, 199.6);

    // Score on alliance stake
    robot->arm.setPosition(150);
    pros::delay(1000);

    // Grab mogo on clump side
    robot->chassis.moveToPoint(-18, 40, 500, {.forwards=false});
    robot->chassis.turnToHeading(-90, 100);
    robot->arm.setPosition(0);
    robot->chassis.moveToPoint(-25, 20, 2000, {.forwards=false, .maxSpeed=70, .earlyExitRange=1}, false);
    robot->mogoPneumatic.set_value(true);

    // Get rings in clump
    robot->intake.setVoltage(12000);
    // MOVE TO POSE FIX
    robot->chassis.turnToHeading(-0, 500);
    robot->chassis.moveToPoint(-24, 45, 1500, {.maxSpeed=70});
    pros::delay(500);
    robot->chassis.turnToHeading(90, 600);
    robot->chassis.moveToPoint(-10, 50, 2000, {.maxSpeed=60});
    pros::delay(500);

//    robot->chassis.turnToHeading(35, 800);
//    robot->chassis.moveToPoint(-10.5, 35, 1000);
//    pros::delay(1500);
//    robot->chassis.turnToHeading(0, 500);
//    robot->chassis.moveToPoint(-11, 55, 1500, {.maxSpeed=60});
//    pros::delay(500);

    robot->chassis.moveToPoint(-48, 48, 500, {.forwards=false});

//    // Go get other mogo
//    robot->chassis.moveToPoint(-30, -12, 2000, {.forwards=false, .minSpeed=50}, false);
//    robot->chassis.turnToHeading(135, 500);
//    robot->mogoPneumatic.set_value(false);
//    robot->chassis.moveToPoint(-48, -24, 1000, {.minSpeed=10, .earlyExitRange=1});
//    robot->chassis.turnToHeading(-90, 300, {.minSpeed=40});
//    robot->chassis.moveToPoint(-18, -24, 1500, {.forwards=false, .maxSpeed=60}, false);
//    pros::delay(100);
//    robot->mogoPneumatic.set_value(true);
//    robot->chassis.turnToHeading(-140, 700, {.minSpeed=40});
//    robot->chassis.moveToPoint(-24, -48, 1500);
//    robot->chassis.turnToHeading(45, 400, {.minSpeed=40});
//    robot->chassis.moveToPoint(-24, -16, 1000, {.minSpeed=20, .earlyExitRange=15});
//    pros::delay(1000);
//    robot->chassis.moveToPoint(-24, 0, 800);

}

void Autons::red3() {

}

void Autons::red4() {

}

void Autons::blue1() {
    robot->chassis.setPose(55, -36, -90);

    // Rush center goal and pull it backwards
    // robot->chassis.turnToHeading(95, 100, {.minSpeed=40}, false);
    // robot->chassis.moveToPoint(-20, -56.5, 1500, {.minSpeed=10, .earlyExitRange=2}, false);
    robot->chassis.moveToPose(23, -43, -125, 1000, {.lead=0.2, .minSpeed=90, .earlyExitRange=12}, false);
    // robot->chassis.turnToHeading(120, 10000, {.minSpeed=5, .earlyExitRange=5});
    robot->doinkerPneumatic.set_value(true);
    pros::delay(300);
    robot->chassis.moveToPoint(20, -37, 10000, {.forwards=false, .maxSpeed=50, .minSpeed=40, .earlyExitRange=2}, false);
    robot->doinkerPneumatic.set_value(false);

    // Pick up MOGO and score Preload
    robot->chassis.moveToPoint(27, -26, 10000, {.forwards=false, .maxSpeed=60, .minSpeed=10, .earlyExitRange=2}, false);
    robot->mogoPneumatic.set_value(true);
    pros::delay(200);
    robot->intake.setVoltage(12000);
    pros::delay(700);
    robot->mogoPneumatic.set_value(false);

    // Go to ring stack and intake the ring
    robot->chassis.turnToHeading(-150, 1000, {.maxSpeed=90, .minSpeed=50, .earlyExitRange=5});
    robot->chassis.moveToPoint(16, -63, 10000, {.maxSpeed=90, .minSpeed=5, .earlyExitRange=1});
    pros::delay(1000);
    robot->intake.setVoltage(0);

    // Pick up MOGO that got rushed
    robot->chassis.moveToPoint(24, -45, 1000, {.forwards=false, .maxSpeed=80, .minSpeed=1, .earlyExitRange=1});
    robot->chassis.turnToHeading(100, 500, {.minSpeed=5, .earlyExitRange=1});
    robot->chassis.moveToPoint(7, -45, 1500, {.forwards=false, .maxSpeed=60}, false);
    robot->mogoPneumatic.set_value(true);
    pros::delay(100);
    robot->intake.setVoltage(12000);

    // CHOPED
    robot->chassis.moveToPoint(24, -24, 800);
    robot->chassis.turnToHeading(-90, 500);
    robot->chassis.moveToPoint(-0, -24, 1500, {.maxSpeed=50});
}

void Autons::blue2() {
    robot->chassis.setPose(60, 12.2, -199.6);

    // Score on alliance stake
    robot->arm.setPosition(150);
    pros::delay(1000);

    // Grab mogo on clump side
    robot->chassis.moveToPoint(18, 40, 500, {.forwards=false});
    robot->chassis.turnToHeading(90, 100);
    robot->arm.setPosition(0);
    robot->chassis.moveToPoint(25, 20, 2000, {.forwards=false, .maxSpeed=70, .earlyExitRange=1}, false);
    robot->mogoPneumatic.set_value(true);

    // Get rings in clump
    robot->intake.setVoltage(12000);
    // MOVE TO POSE FIX  // CHOPPED AGAIN BRO WHAT
    robot->chassis.turnToHeading(0, 500);
    robot->chassis.moveToPoint(24, 45, 1500, {.maxSpeed=70});
    pros::delay(500);
    robot->chassis.turnToHeading(-90, 600);
    robot->chassis.moveToPoint(6, 50, 2000, {.maxSpeed=60});
    pros::delay(2000);


    robot->chassis.moveToPoint(24, -48, 800, {.forwards=false});
    robot->chassis.turnToHeading(-90, 500);
    robot->chassis.moveToPoint(-0, -24, 1500, {.maxSpeed=50});

//    // Go get other mogo
// CHOPPED
//    robot->chassis.moveToPoint(30, -12, 2000, {.forwards=false, .minSpeed=50}, false);
//    robot->chassis.turnToHeading(-135, 500);
//    robot->mogoPneumatic.set_value(false);
//    robot->chassis.moveToPoint(48, -24, 1000, {.minSpeed=10, .earlyExitRange=1});
//    robot->chassis.turnToHeading(90, 300, {.minSpeed=40});
//    robot->chassis.moveToPoint(18, -24, 1500, {.forwards=false, .maxSpeed=60}, false);
//    pros::delay(100);
//    robot->mogoPneumatic.set_value(true);
//    robot->chassis.turnToHeading(140, 700, {.minSpeed=40});
//    robot->chassis.moveToPoint(24, -48, 1500);
//    robot->chassis.turnToHeading(-45, 400, {.minSpeed=40});
//    robot->chassis.moveToPoint(24, -16, 1000, {.minSpeed=20, .earlyExitRange=15});
//    pros::delay(1000);
//    robot->chassis.moveToPoint(24, 0, 800);
}

void Autons::blue3() {

}

void Autons::blue4() {

}

void Autons::skills() {
    robot->chassis.setPose(-62.5, 0, 90);

    // Score on alliance stake
    robot->intake.setVoltage(12000);
    pros::delay(700);

    // Pick up MOGO
    robot->chassis.moveToPoint(-55, 0, 500);
    robot->chassis.turnToHeading(180, 500);
    robot->chassis.moveToPoint(-45, 27, 1000, {.forwards=false}, false);
    robot->mogoPneumatic.set_value(true);
    pros::delay(200);

    // Drive to corner
    robot->chassis.turnToHeading(45, 500);
    robot->chassis.moveToPoint(-62.5, 62.5, 1500);
    robot->chassis.turnToHeading(123, 500, {}, false);
    robot->chassis.moveToPoint(-63.5, 62.5, 500, {.forwards=false}, false);
    robot->mogoPneumatic.set_value(false);

    // Grab 2nd MOGO
    robot->chassis.moveToPoint(-48, 48, 500);
    robot->chassis.turnToHeading(0, 500);
    robot->chassis.moveToPoint(-55, 24, 1500, {.forwards=false});
    robot->chassis.moveToPoint(-46, -30, 1500, {.forwards=false, .maxSpeed=60}, false);
    pros::delay(200);
    robot->mogoPneumatic.set_value(true);
    pros::delay(200);

    // Put 2nd MOGO in corner
    robot->chassis.turnToHeading(45, 500);
    robot->chassis.moveToPoint(-62.5, -62.5, 1000, {.forwards=false}, false);
    robot->mogoPneumatic.set_value(false);
    pros::delay(200);



}
