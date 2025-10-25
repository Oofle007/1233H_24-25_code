//      _              _
//     / \     _   _  | |_    ___    _ __    ___
//    / _ \   | | | | | __|  / _ \  | '_ \  / __|
//   / ___ \  | |_| | | |_  | (_) | | | | | \__ \
//  /_/   \_\  \__,_|  \__|  \___/  |_| |_| |___/

#include <utility>
#include "../include/hteam/autons.h"

Autons::Autons(std::shared_ptr<Robot> robot) : robot(std::move(robot)) {

}


void Autons::red1() { // LEFT - SAWP
    robot->chassis.setPose(-13.25, -45.6, 0);

    // Get first clump of 3
    robot->intake.intakeNoOuttake();
    robot->chassis.moveToPoint(-13.5, -28, 400, {.maxSpeed=80});
    robot->chassis.turnToHeading(-45, 300, {.minSpeed=30});
    robot->chassis.moveToPose(-27, -18, -60, 1100, {.lead=0, .maxSpeed=40, .minSpeed=20, .earlyExitRange=2});

    // Move to match loader
    robot->chassis.turnToHeading(-135, 350, {.maxSpeed=100, .earlyExitRange=20}, false);
    robot->intake.stopIntake();
    robot->chassis.moveToPose(-46.5, -45, -145, 1100, {.lead=0}, false);
    robot->chassis.turnToHeading(180, 400, {.maxSpeed=100}, false);
    robot->matchLoaderPneumatic.set_value(true);
    robot->intake.intakeNoOuttake();

    // Get matchloads
    robot->chassis.moveToPose(-47, -61.5, 180, 600, {.lead=0, .maxSpeed=45, .minSpeed=5}, false);
    pros::delay(100);
    robot->chassis.moveToPose(-47, -62, 180, 650, {.lead=0, .maxSpeed=15}, false);

    // Drive and score on long goal
    robot->chassis.moveToPose(-47, -30, 180, 700, {.forwards=false, .lead=0, .minSpeed=70, .earlyExitRange=2}, false);
    robot->intake.outtakeBottom(false);
    robot->intake.intakePneumatic.set_value(true);
    pros::delay(350);
    robot->intake.outtakeTop();
    robot->chassis.moveToPose(-47, 0, 180, 1300, {.forwards=false, .lead=0, .maxSpeed=60, .earlyExitRange=2}, false);  // basically a wait but backing up into the goal
    robot->intake.stopIntake();

    // Go to mid goal
    robot->chassis.moveToPose(-47.5, -48, 180, 700, {.lead=0, .minSpeed=10, .earlyExitRange=2}, false);
    robot->intake.stopIntake();
    robot->matchLoaderPneumatic.set_value(false);
    robot->chassis.turnToHeading(-135, 400, {.maxSpeed=100}, false);
    robot->intake.intakeNoOuttake();
    robot->chassis.moveToPose(-10, -9, -135, 2000, {.forwards=false, .lead=0, .maxSpeed=80, .minSpeed=1, .earlyExitRange=2}, false);

    // Score on mid goal
    robot->intake.outtakeMiddle();
    pros::delay(1700);

    // Go and score on low goal
    robot->intake.intakeNoOuttake();
    pros::delay(100);
    robot->chassis.swingToHeading(120, DriveSide::LEFT, 600,{.direction= AngularDirection::CCW_COUNTERCLOCKWISE, .maxSpeed=80}, false);
    robot->intake.outtakeBottom();
    robot->chassis.moveToPose(13, -17, 90, 850, {.lead=0, .minSpeed=80, .earlyExitRange=6}, false);
    robot->chassis.turnToHeading(0, 300, {.minSpeed=20, .earlyExitRange=10}, false);
    robot->chassis.moveToPose(15, -13, -45, 1500, {.lead=0, .minSpeed=20, .earlyExitRange=2});
}

void Autons::red2() {  // LEFT - 7T
    robot->chassis.setPose(-13.25, -45.6, 0);

    // Get first clump of 3
    robot->intake.intakeNoOuttake();
    robot->chassis.moveToPoint(-13.5, -28, 400, {.maxSpeed=80});
    robot->chassis.turnToHeading(-45, 300, {.minSpeed=30});
    robot->chassis.moveToPose(-27, -18, -60, 1100, {.lead=0, .maxSpeed=40, .minSpeed=20, .earlyExitRange=2});

    // Move to match loader
    robot->chassis.turnToHeading(-135, 350, {.maxSpeed=100, .earlyExitRange=20}, false);
    robot->intake.stopIntake();
    robot->chassis.moveToPose(-46.5, -45, -145, 1100, {.lead=0}, false);
    robot->chassis.turnToHeading(180, 400, {.maxSpeed=100}, false);
    robot->matchLoaderPneumatic.set_value(true);
    robot->intake.intakeNoOuttake();

    // Get matchloads
    robot->chassis.moveToPose(-47, -61.5, 180, 600, {.lead=0, .maxSpeed=45, .minSpeed=5}, false);
    pros::delay(100);
    robot->chassis.moveToPose(-47, -62, 180, 650, {.lead=0, .maxSpeed=15}, false);

    // Drive and score on long goal
    robot->chassis.moveToPose(-47, -30, 180, 700, {.forwards=false, .lead=0, .minSpeed=70, .earlyExitRange=2}, false);
    robot->intake.outtakeBottom(false);
    robot->intake.intakePneumatic.set_value(true);
    pros::delay(350);
    robot->intake.outtakeTop();
    robot->chassis.moveToPose(-47, 0, 180, 3900, {.forwards=false, .lead=0, .maxSpeed=60, .earlyExitRange=2}, false);  // basically a wait but backing up into the goal

    // Get matchloads AGAIN
    robot->matchLoaderPneumatic.set_value(true);
    robot->matchLoaderPneumaticState = true;
    robot->chassis.moveToPose(-47, -61.5, 180, 1500, {.lead=0, .maxSpeed=45, .minSpeed=5}, false);
    robot->intake.intakeNoOuttake();
    pros::delay(100);
    robot->chassis.moveToPose(-47, -62, 180, 1500, {.lead=0, .maxSpeed=15}, false);

    // outtake the blue ones
    robot->intake.outtakeMiddle();
}

void Autons::red3() {  // LEFT - 7T 4M
    robot->chassis.setPose(-13.25, -45.6, 0);

    // Get first clump of 3
    robot->intake.intakeNoOuttake();
    robot->chassis.moveToPoint(-13.5, -28, 400, {.maxSpeed=80});
    robot->chassis.turnToHeading(-45, 300, {.minSpeed=30});
    robot->chassis.moveToPose(-27, -18, -60, 1100, {.lead=0, .maxSpeed=40, .minSpeed=20, .earlyExitRange=2});

    // Move to match loader
    robot->chassis.turnToHeading(-135, 350, {.maxSpeed=100, .earlyExitRange=20}, false);
    robot->intake.stopIntake();
    robot->chassis.moveToPose(-46.5, -45, -145, 1100, {.lead=0}, false);
    robot->chassis.turnToHeading(180, 400, {.maxSpeed=100}, false);
    robot->matchLoaderPneumatic.set_value(true);
    robot->intake.intakeNoOuttake();

    // Get matchloads
    robot->chassis.moveToPose(-47, -61.5, 180, 600, {.lead=0, .maxSpeed=45, .minSpeed=5}, false);
    pros::delay(100);
    robot->chassis.moveToPose(-47, -62, 180, 650, {.lead=0, .maxSpeed=15}, false);

    // Drive and score on long goal
    robot->chassis.moveToPose(-47, -30, 180, 700, {.forwards=false, .lead=0, .minSpeed=70, .earlyExitRange=2}, false);
    robot->intake.outtakeBottom(false);
    robot->intake.intakePneumatic.set_value(true);
    pros::delay(350);
    robot->intake.outtakeTop();
    robot->chassis.moveToPose(-47, 0, 180, 1300, {.forwards=false, .lead=0, .maxSpeed=60, .earlyExitRange=2}, false);  // basically a wait but backing up into the goal
    robot->intake.stopIntake();

    // Go to mid goal
    robot->chassis.moveToPose(-47.5, -48, 180, 700, {.lead=0, .minSpeed=10, .earlyExitRange=2}, false);
    robot->intake.stopIntake();
    robot->matchLoaderPneumatic.set_value(false);
    robot->chassis.turnToHeading(-135, 400, {.maxSpeed=100}, false);
    robot->intake.intakeNoOuttake();
    robot->chassis.moveToPose(-10, -9, -135, 2000, {.forwards=false, .lead=0, .maxSpeed=80, .minSpeed=1, .earlyExitRange=2}, false);

    // Score on mid goal
    robot->intake.outtakeMiddle();
    pros::delay(2200);

    // Drive back to matchloader
    robot->chassis.moveToPose(-47.5, -48, -135, 1300, {.lead=0, .minSpeed=10, .earlyExitRange=2}, false);
    robot->chassis.turnToHeading(180, 400, {.maxSpeed=100}, false);

    // Get matchloads
    robot->matchLoaderPneumatic.set_value(true);
    robot->matchLoaderPneumaticState = true;
    robot->intake.outtakeMiddle();
    robot->chassis.moveToPose(-47, -61.5, 180, 600, {.lead=0, .maxSpeed=45, .minSpeed=5}, false);
    pros::delay(100);
    robot->chassis.moveToPose(-47, -62, 180, 650, {.lead=0, .maxSpeed=15}, false);
}

void Autons::red4() {  // RIGHT - 7T
    robot->chassis.setPose(13.25, -45.6, 0);

    // Get first clump of 3
    robot->intake.intakeNoOuttake();
    robot->chassis.moveToPoint(13.5, -28, 400, {.maxSpeed=80});
    robot->chassis.turnToHeading(45, 300, {.minSpeed=30});
    robot->chassis.moveToPose(27, -18, 60, 1100, {.lead=0, .maxSpeed=40, .minSpeed=20, .earlyExitRange=2});

    // Move to match loader
    robot->chassis.turnToHeading(135, 350, {.maxSpeed=100, .earlyExitRange=20}, false);
    robot->intake.stopIntake();
    robot->chassis.moveToPose(46.5, -45, 145, 1100, {.lead=0}, false);
    robot->chassis.turnToHeading(180, 400, {.maxSpeed=100}, false);
    robot->matchLoaderPneumatic.set_value(true);
    robot->intake.intakeNoOuttake();

    // Get matchloads
    robot->chassis.moveToPose(47, -62, 180, 600, {.lead=0, .maxSpeed=45, .minSpeed=5}, false);
    pros::delay(100);
    robot->chassis.moveToPose(47, -62.5, 180, 650, {.lead=0, .maxSpeed=15}, false);

    // Drive and score on long goal
    robot->chassis.moveToPose(47, -30, 180, 700, {.forwards=false, .lead=0, .minSpeed=70, .earlyExitRange=2}, false);
    robot->intake.outtakeBottom(false);
    robot->intake.intakePneumatic.set_value(true);
    pros::delay(350);
    robot->intake.outtakeTop();
    robot->chassis.moveToPose(47, 0, 180, 3900, {.forwards=false, .lead=0, .maxSpeed=60, .earlyExitRange=2}, false);  // basically a wait but backing up into the goal

    // Get matchloads AGAIN
    robot->matchLoaderPneumatic.set_value(true);
    robot->matchLoaderPneumaticState = true;
    robot->chassis.moveToPose(47, -62, 180, 1500, {.lead=0, .maxSpeed=45, .minSpeed=5}, false);
    robot->intake.intakeNoOuttake();
    pros::delay(100);
    robot->chassis.moveToPose(47, -62.5, 180, 1500, {.lead=0, .maxSpeed=15}, false);

    // outtake the blue ones
    robot->intake.outtakeMiddle();
}

void Autons::blue1() {  // NONE

}

void Autons::blue2() {  // LEFT - 7T
    robot->chassis.setPose(-13.25, -45.6, 0);

    // Get first clump of 3
    robot->intake.intakeNoOuttake();
    robot->chassis.moveToPoint(-13.5, -28, 400, {.maxSpeed=80});
    robot->chassis.turnToHeading(-45, 300, {.minSpeed=30});
    robot->chassis.moveToPose(-27, -18, -60, 1100, {.lead=0, .maxSpeed=40, .minSpeed=20, .earlyExitRange=2});

    // Move to match loader
    robot->chassis.turnToHeading(-135, 350, {.maxSpeed=100, .earlyExitRange=20}, false);
    robot->intake.stopIntake();
    robot->chassis.moveToPose(-46.5, -45, -145, 1100, {.lead=0}, false);
    robot->chassis.turnToHeading(180, 400, {.maxSpeed=100}, false);
    robot->matchLoaderPneumatic.set_value(true);
    robot->intake.intakeNoOuttake();

    // Get matchloads
    robot->chassis.moveToPose(-47, -61.5, 180, 600, {.lead=0, .maxSpeed=45, .minSpeed=5}, false);
    pros::delay(100);
    robot->chassis.moveToPose(-47, -62, 180, 650, {.lead=0, .maxSpeed=15}, false);

    // Drive and score on long goal
    robot->chassis.moveToPose(-47, -30, 180, 700, {.forwards=false, .lead=0, .minSpeed=70, .earlyExitRange=2}, false);
    robot->intake.outtakeBottom(false);
    robot->intake.intakePneumatic.set_value(true);
    pros::delay(350);
    robot->intake.outtakeTop();
    robot->chassis.moveToPose(-47, 0, 180, 3900, {.forwards=false, .lead=0, .maxSpeed=60, .earlyExitRange=2}, false);  // basically a wait but backing up into the goal

    // Get matchloads AGAIN
    robot->matchLoaderPneumatic.set_value(true);
    robot->matchLoaderPneumaticState = true;
    robot->chassis.moveToPose(-47, -61.5, 180, 1500, {.lead=0, .maxSpeed=45, .minSpeed=5}, false);
    robot->intake.intakeNoOuttake();
    pros::delay(100);
    robot->chassis.moveToPose(-47, -62, 180, 1500, {.lead=0, .maxSpeed=15}, false);

    // outtake the blue ones
    robot->intake.outtakeMiddle();
}

void Autons::blue3() {  // LEFT - 7T 4M
    robot->chassis.setPose(-13.25, -45.6, 0);

    // Get first clump of 3
    robot->intake.intakeNoOuttake();
    robot->chassis.moveToPoint(-13.5, -28, 400, {.maxSpeed=80});
    robot->chassis.turnToHeading(-45, 300, {.minSpeed=30});
    robot->chassis.moveToPose(-27, -18, -60, 1100, {.lead=0, .maxSpeed=40, .minSpeed=20, .earlyExitRange=2});

    // Move to match loader
    robot->chassis.turnToHeading(-135, 350, {.maxSpeed=100, .earlyExitRange=20}, false);
    robot->intake.stopIntake();
    robot->chassis.moveToPose(-46.5, -45, -145, 1100, {.lead=0}, false);
    robot->chassis.turnToHeading(180, 400, {.maxSpeed=100}, false);
    robot->matchLoaderPneumatic.set_value(true);
    robot->intake.intakeNoOuttake();

    // Get matchloads
    robot->chassis.moveToPose(-47, -61.5, 180, 600, {.lead=0, .maxSpeed=45, .minSpeed=5}, false);
    pros::delay(100);
    robot->chassis.moveToPose(-47, -62, 180, 650, {.lead=0, .maxSpeed=15}, false);

    // Drive and score on long goal
    robot->chassis.moveToPose(-47, -30, 180, 700, {.forwards=false, .lead=0, .minSpeed=70, .earlyExitRange=2}, false);
    robot->intake.outtakeBottom(false);
    robot->intake.intakePneumatic.set_value(true);
    pros::delay(350);
    robot->intake.outtakeTop();
    robot->chassis.moveToPose(-47, 0, 180, 1300, {.forwards=false, .lead=0, .maxSpeed=60, .earlyExitRange=2}, false);  // basically a wait but backing up into the goal
    robot->intake.stopIntake();

    // Go to mid goal
    robot->chassis.moveToPose(-47.5, -48, 180, 700, {.lead=0, .minSpeed=10, .earlyExitRange=2}, false);
    robot->intake.stopIntake();
    robot->matchLoaderPneumatic.set_value(false);
    robot->chassis.turnToHeading(-135, 400, {.maxSpeed=100}, false);
    robot->intake.intakeNoOuttake();
    robot->chassis.moveToPose(-10, -9, -135, 2000, {.forwards=false, .lead=0, .maxSpeed=80, .minSpeed=1, .earlyExitRange=2}, false);

    // Score on mid goal
    robot->intake.outtakeMiddle();
    pros::delay(2200);

    // Drive back to matchloader
    robot->chassis.moveToPose(-47.5, -48, -135, 1300, {.lead=0, .minSpeed=10, .earlyExitRange=2}, false);
    robot->chassis.turnToHeading(180, 400, {.maxSpeed=100}, false);

    // Get matchloads
    robot->matchLoaderPneumatic.set_value(true);
    robot->matchLoaderPneumaticState = true;
    robot->intake.outtakeMiddle();
    robot->chassis.moveToPose(-47, -61.5, 180, 600, {.lead=0, .maxSpeed=45, .minSpeed=5}, false);
    pros::delay(100);
    robot->chassis.moveToPose(-47, -62, 180, 650, {.lead=0, .maxSpeed=15}, false);
}

void Autons::blue4() {  // RIGHT - 7T
    robot->chassis.setPose(13.25, -45.6, 0);

    // Get first clump of 3
    robot->intake.intakeNoOuttake();
    robot->chassis.moveToPoint(13.5, -28, 400, {.maxSpeed=80});
    robot->chassis.turnToHeading(45, 300, {.minSpeed=30});
    robot->chassis.moveToPose(27, -18, 60, 1100, {.lead=0, .maxSpeed=40, .minSpeed=20, .earlyExitRange=2});

    // Move to match loader
    robot->chassis.turnToHeading(135, 350, {.maxSpeed=100, .earlyExitRange=20}, false);
    robot->intake.stopIntake();
    robot->chassis.moveToPose(46.5, -45, 145, 1100, {.lead=0}, false);
    robot->chassis.turnToHeading(180, 400, {.maxSpeed=100}, false);
    robot->matchLoaderPneumatic.set_value(true);
    robot->intake.intakeNoOuttake();

    // Get matchloads
    robot->chassis.moveToPose(47, -62, 180, 600, {.lead=0, .maxSpeed=45, .minSpeed=5}, false);
    pros::delay(100);
    robot->chassis.moveToPose(47, -62.5, 180, 650, {.lead=0, .maxSpeed=15}, false);

    // Drive and score on long goal
    robot->chassis.moveToPose(47, -30, 180, 700, {.forwards=false, .lead=0, .minSpeed=70, .earlyExitRange=2}, false);
    robot->intake.outtakeBottom(false);
    robot->intake.intakePneumatic.set_value(true);
    pros::delay(350);
    robot->intake.outtakeTop();
    robot->chassis.moveToPose(47, 0, 180, 3900, {.forwards=false, .lead=0, .maxSpeed=60, .earlyExitRange=2}, false);  // basically a wait but backing up into the goal

    // Get matchloads AGAIN
    robot->matchLoaderPneumatic.set_value(true);
    robot->matchLoaderPneumaticState = true;
    robot->chassis.moveToPose(47, -62, 180, 1500, {.lead=0, .maxSpeed=45, .minSpeed=5}, false);
    robot->intake.intakeNoOuttake();
    pros::delay(100);
    robot->chassis.moveToPose(47, -62.5, 180, 1500, {.lead=0, .maxSpeed=15}, false);

    // outtake the blue ones
    robot->intake.outtakeMiddle();
}

void Autons::skills() {
    robot->chassis.setPose(-13.25, -45.6, 0);

    // Go to match loader #1
    robot->chassis.swingToHeading(-90, DriveSide::LEFT, 600, {.direction=AngularDirection::CCW_COUNTERCLOCKWISE ,.maxSpeed=60, .earlyExitRange=5});
    robot->chassis.moveToPose(-48, -40, -90, 1300, {.lead=0, .maxSpeed=90, .minSpeed=5, .earlyExitRange=0.5});
    robot->chassis.turnToHeading(180, 700, {.maxSpeed=100}, false);
    robot->intake.intakeNoOuttake();

    // Get matchloads
    robot->matchLoaderPneumatic.set_value(true);
    pros::delay(100); // let the match loader fall down
    robot->chassis.moveToPose(-49, -61, 180, 2000, {.lead=0, .maxSpeed=40, .minSpeed=20, .earlyExitRange=2});
    robot->chassis.moveToPose(-49, -60, 180, 800, {.forwards=false, .lead=0, .maxSpeed=80, .minSpeed=10, .earlyExitRange=2});
    pros::delay(3000);

    // Drive and score on long goal
    robot->chassis.moveToPose(-47, -30, 180, 1000, {.forwards=false, .lead=0, .maxSpeed=70, .minSpeed=5, .earlyExitRange=2}, false);

    // shuffle the cubes around
    robot->intake.outtakeBottom();
    pros::delay(500);

    robot->intake.outtakeTop();
    robot->matchLoaderPneumatic.set_value(false);
    robot->chassis.moveToPose(-48, 0, 180, 4000, {.forwards=false, .lead=0, .maxSpeed=20, .earlyExitRange=2}, false);  // basically a wait but backing up into the goal
    robot->intake.stopIntake();

    // Drive away from match loader and turn around to go to the next one
    robot->chassis.moveToPose(-47, -36, 180, 1300, {.lead=0, .maxSpeed=90, .minSpeed=10, .earlyExitRange=2});
    robot->chassis.turnToHeading(-90, 400, {.maxSpeed=100}, false);
    robot->chassis.moveToPose(-60, -36, -90, 1300, {.lead=0, .maxSpeed=90, .minSpeed=10, .earlyExitRange=2});
    robot->chassis.turnToHeading(0, 400, {.maxSpeed=100}, false);

    // Go across field
    robot->intake.stopIntake();
    robot->chassis.moveToPose(-60, 48, 0, 3000, {.lead=0, .maxSpeed=100, .minSpeed=10, .earlyExitRange=2});

    // Line up to match loader
    robot->chassis.turnToHeading(90, 400, {.maxSpeed=100}, false);
    robot->chassis.moveToPose(-48, 48, 90, 1300, {.lead=0, .maxSpeed=90, .minSpeed=10, .earlyExitRange=2});
    robot->chassis.turnToHeading(0, 700, {.maxSpeed=80}, false);

    // Get matchloads
    robot->matchLoaderPneumatic.set_value(true);
    pros::delay(100); // let the match loader fall down
    robot->intake.intakeNoOuttake();
    robot->chassis.moveToPose(-47, 63, 0, 2000  , {.lead=0, .maxSpeed=40, .minSpeed=25, .earlyExitRange=2});
    robot->chassis.moveToPose(-47, 63, 0, 800, {.forwards=false, .lead=0, .maxSpeed=80, .minSpeed=10, .earlyExitRange=2});
    pros::delay(3000);

    // Drive and score on long goal
    robot->chassis.moveToPose(-47.5, 31, 0, 1000, {.forwards=false, .lead=0, .maxSpeed=70, .minSpeed=5, .earlyExitRange=2}, false);

    // shuffle the cubes around
    robot->intake.outtakeBottom();
    pros::delay(500);

    robot->intake.outtakeTop();
    robot->matchLoaderPneumatic.set_value(false);
    robot->chassis.moveToPose(-48, 0, 0, 4000, {.forwards=false, .lead=0, .maxSpeed=15, .earlyExitRange=2}, false);  // basically a wait but backing up into the goal
    robot->intake.stopIntake();
}
