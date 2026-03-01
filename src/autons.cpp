//      _              _
//     / \     _   _  | |_    ___    _ __    ___
//    / _ \   | | | | | __|  / _ \  | '_ \  / __|
//   / ___ \  | |_| | | |_  | (_) | | | | | \__ \
//  /_/   \_\  \__,_|  \__|  \___/  |_| |_| |___/

#include <utility>
#include "../include/hteam/autons.h"

Autons::Autons(std::shared_ptr<Robot> robot) : robot(std::move(robot)) {

}


void Autons::red1() { // LEFT - 9 SAWP
    robot->chassis.setPose(-13.25, -45.6, 0);

    // Get first clump of 3
    robot->intake.intakeNoOuttake();
    robot->chassis.moveToPoint(-13.5, -28, 400, {.maxSpeed=80});
    robot->chassis.turnToHeading(-45, 300, {.minSpeed=30});
    robot->chassis.moveToPose(-27, -15, -60, 1100, {.lead=0, .maxSpeed=40, .minSpeed=20, .earlyExitRange=2});

    // Move to match loader
    robot->chassis.turnToHeading(-135, 350, {.maxSpeed=100, .earlyExitRange=20}, false);
    robot->intake.stopIntake();
    robot->chassis.moveToPose(-47, -45, -145, 1100, {.lead=0}, false);
    robot->chassis.turnToHeading(180, 400, {.maxSpeed=100}, false);
    robot->matchLoaderPneumatic.set_value(true);
    robot->intake.intakeNoOuttake();

    // Get matchloads
    robot->chassis.moveToPose(-47.5, -65, 180, 1500, {.lead=0, .maxSpeed=45, .minSpeed=5}, false);

    // Drive and score on long goal
    robot->intake.intakePneumatic.set_value(false);
    robot->intake.stopIntake();
    robot->chassis.moveToPose(-48, -30, 180, 850, {.forwards=false, .lead=0, .minSpeed=10, .earlyExitRange=2}, false);
    robot->intake.outtakeBottom(false);
    pros::delay(200);
    robot->intake.outtakeTop();
    robot->chassis.moveToPose(-48, 0, 180, 1000, {.forwards=false, .lead=0, .maxSpeed=60, .earlyExitRange=2}, false);  // basically a wait but backing up into the goal
    robot->intake.stopIntake();

    // Go to mid goal
    robot->matchLoaderPneumatic.set_value(false);
    robot->chassis.moveToPose(-47.5, -48, 180, 700, {.lead=0, .minSpeed=40, .earlyExitRange=2}, false);
    robot->intake.outtakeBottom();
    pros::delay(100);
    robot->intake.stopIntake();
    robot->intake.intakePneumatic.set_value(true);
    robot->chassis.turnToHeading(-135, 400, {.maxSpeed=100}, false);
    robot->intake.intakeNoOuttake();
    robot->chassis.moveToPose(-12, -11, -135, 1300, {.forwards=false, .lead=0, .maxSpeed=80, .minSpeed=1, .earlyExitRange=2}, false);

    // Score on mid goal
    robot->intake.outtakeBottom();
    pros::delay(250);
    robot->intake.outtakeMiddle();
    pros::delay(1300);

    // NEW go and score on low goal
    robot->intake.intakeNoOuttake();
    pros::delay(100);
    robot->chassis.swingToHeading(90, DriveSide::LEFT, 600,{.direction= AngularDirection::CCW_COUNTERCLOCKWISE, .maxSpeed=80}, false);
    robot->chassis.moveToPose(31, -23, 90, 1400, {.lead=0, .maxSpeed=60}, false);
    robot->chassis.turnToHeading(-45, 400, {.maxSpeed=100, .earlyExitRange=5}, false);
    robot->chassis.moveToPose(18, -15, -45, 400, {.lead=0, .maxSpeed=100}, false);
    robot->intake.outtakeBottom();
    robot->chassis.moveToPose(13.5, -13.5, -45, 1500, {.lead=0, .minSpeed=20, .earlyExitRange=2});
}

void Autons::red2() {  // LEFT - 5T4M

}

void Autons::red3() {  // LEFT - 3T4M OG
    robot->chassis.setPose(-13.25, -45.6, 0);

    // Get first clump of 3
    robot->intake.intakeNoOuttake();
    robot->chassis.moveToPoint(-13.5, -28, 400, {.maxSpeed=80});
    robot->chassis.turnToHeading(-45, 300, {.minSpeed=30});
    robot->chassis.moveToPose(-27, -15, -60, 1100, {.lead=0, .maxSpeed=30, .minSpeed=20, .earlyExitRange=2});

    // Move to match loader
    robot->chassis.turnToHeading(-135, 350, {.maxSpeed=100, .earlyExitRange=20}, false);
    robot->intake.stopIntake();
    robot->chassis.moveToPose(-47.5, -45, -145, 1100, {.lead=0}, false);
    robot->chassis.turnToHeading(180, 400, {.maxSpeed=100}, false);
    robot->matchLoaderPneumatic.set_value(true);
    robot->intake.intakeNoOuttake();

    // Get matchloads
    robot->chassis.moveToPose(-48, -65, 180, 1500, {.lead=0, .maxSpeed=45, .minSpeed=5}, false);

    // Drive and score on long goal
    robot->intake.intakePneumatic.set_value(false);
    robot->intake.stopIntake();
    robot->chassis.moveToPose(-48, -30, 180, 850, {.forwards=false, .lead=0, .minSpeed=10, .earlyExitRange=2}, false);
    robot->intake.outtakeBottom(false);
    pros::delay(200);
    robot->intake.outtakeTop();
    robot->chassis.moveToPose(-48, 0, 180, 1000, {.forwards=false, .lead=0, .maxSpeed=60, .earlyExitRange=2}, false);  // basically a wait but backing up into the goal
    robot->intake.stopIntake();

    // rail the goal
    robot->chassis.moveToPose(-48, -40, 180, 600, {.lead=0, .earlyExitRange=2}, false);
    robot->chassis.moveToPose(-48, -30, 180, 500, {.forwards=false, .lead=0, .minSpeed=100, .earlyExitRange=2}, false);

    // Go to mid goal
    robot->matchLoaderPneumatic.set_value(false);
    robot->chassis.moveToPose(-47.5, -48, 180, 700, {.lead=0, .minSpeed=40, .earlyExitRange=2}, false);
    robot->intake.outtakeBottom();
    pros::delay(100);
    robot->intake.stopIntake();
    robot->intake.intakePneumatic.set_value(true);
    robot->chassis.turnToHeading(-135, 400, {.maxSpeed=100}, false);
    robot->intake.intakeNoOuttake();
    robot->chassis.moveToPose(-10, -9, -135, 2000, {.forwards=false, .lead=0, .maxSpeed=80, .minSpeed=1, .earlyExitRange=2}, false);

    // Score on mid goal
    robot->intake.outtakeBottom();
    pros::delay(200);
    robot->intake.outtakeMiddle();
    pros::delay(1200);

    // drive back away far far away
    robot->chassis.moveToPose(-47, -48, 180, 1500, {.lead=0, .minSpeed=10, .earlyExitRange=2}, false);
    robot->chassis.turnToHeading(180, 400, {.maxSpeed=100}, false);
    robot->intake.intakeNoOuttake();
    robot->matchLoaderPneumatic.set_value(true);
    robot->matchLoaderPneumaticState = true;
    pros::delay(100);

    // get them matchloads
    robot->chassis.moveToPose(-47.5, -65, 180, 1600, {.lead=0, .maxSpeed=45, .minSpeed=5}, false);
}

void Autons::red4() {  // LEFT 4T3M CENTER
    robot->chassis.setPose(-13.25, -45.6, 0);

    // Get first clump of 3
    robot->intake.intakeNoOuttake();
    robot->chassis.moveToPoint(-13.5, -25, 400, {.maxSpeed=80});
    robot->chassis.turnToHeading(-45, 300, {.minSpeed=30});
    robot->chassis.moveToPose(-21, -15, -60, 1200, {.lead=0, .minSpeed=80, .earlyExitRange=2}, false);
    robot->matchLoaderPneumatic.set_value(true);

    // Move to mid goal
    robot->chassis.moveToPose(-13, -15, -135, 600, {.forwards=false, .lead=0, .maxSpeed=80});

    // score on mid goal
    robot->chassis.moveToPose(-8, -8, -135, 1000, {.forwards=false, .lead=0, .maxSpeed=80});
    robot->intake.outtakeBottom();
    pros::delay(350);
    robot->intake.outtakeMiddle();
    pros::delay(1200);
    robot->intake.intakeNoOuttake();

    // Move to match loader
    robot->chassis.moveToPose(-48, -49, -135, 1500, {.lead=0}, false);
    robot->intake.outtakeMiddle();
    pros::delay(100);
    robot->intake.intakeNoOuttake();
    robot->chassis.turnToHeading(180, 400, {.maxSpeed=100}, false);

    // Get matchloads
    robot->chassis.moveToPose(-48.5, -58, 180, 500, {.lead=0, .maxSpeed=70, .minSpeed=50}, false);
    robot->chassis.moveToPose(-48.5, -66, 180, 700, {.lead=0, .maxSpeed=60, .minSpeed=30}, false);

    // Drive and score on long goal
    robot->intake.intakePneumatic.set_value(false);
    robot->intake.stopIntake();
    robot->chassis.moveToPose(-50, 30, 180, 700, {.forwards=false, .lead=0, .minSpeed=10, .earlyExitRange=2}, false);
    robot->intake.outtakeTop();
    robot->chassis.moveToPose(-49, 0, 180, 2600, {.forwards=false, .lead=0, .maxSpeed=60, .earlyExitRange=2}, false);  // basically a wait but backing up into the goal
    robot->intake.stopIntake();

    // push cubes into mid
    robot->descorePneumatic.set_value(false);
    robot->descorePneumaticState = false;
    robot->matchLoaderPneumatic.set_value(false);
    robot->chassis.moveToPose(-48, -37, 180, 600, {.lead=0, .minSpeed=20, .earlyExitRange=2});
    robot->chassis.turnToHeading(90, 400, {.maxSpeed=100}, false);
    robot->chassis.moveToPose(-59, -37, 90, 600, {.forwards=false, .lead=0, .minSpeed=20, .earlyExitRange=2});
    robot->chassis.turnToHeading(170, 700, {.maxSpeed=100}, false);
    robot->chassis.moveToPose(-59, -8, 180, 3000, {.forwards=false, .lead=0, .maxSpeed=40});

    robot->intake.intakePneumaticState = false;

}

void Autons::blue1() {  // NONE

}

void Autons::blue2() {  // LEFT - 7T

}

void Autons::blue3() {  // LEFT - 7T 4M

}

void Autons::blue4() {  // RIGHT - 7T

}

void Autons::skills() {
    robot->chassis.setPose(13.25, -45.6, 0);

    // Go to match loader #1
    robot->chassis.swingToHeading(90, DriveSide::RIGHT, 600, {.direction=AngularDirection::CW_CLOCKWISE ,.maxSpeed=60, .earlyExitRange=5});
    robot->chassis.moveToPose(48.7, -40, 90, 1300, {.lead=0, .maxSpeed=90, .minSpeed=5, .earlyExitRange=0.5});
    robot->chassis.turnToHeading(180, 700, {.maxSpeed=100}, false);
    robot->intake.intakeNoOuttake();

    // Get matchloads
    robot->matchLoaderPneumatic.set_value(true);
    pros::delay(100); // let the match loader fall down

    robot->chassis.moveToPose(47, -56, 180, 350, {.lead=0, .minSpeed=5}, false);  // go get real personal
    robot->chassis.moveToPose(47, -65, 180, 1100, {.lead=0, .maxSpeed=35, .minSpeed=5}, false);  // get first three
    robot->chassis.moveToPose(47, -56, 180, 500, {.forwards=false, .lead=0, .minSpeed=20}, false);  // back out of that joint
    pros::delay(300);
    robot->chassis.moveToPose(47, -65, 180, 2000, {.lead=0, .maxSpeed=35, .minSpeed=5}, false);  // get the next three

    robot->intake.stopIntake();
    robot->intake.intakePneumatic.set_value(false);

    // Drive and score on long goal
    robot->chassis.moveToPose(47.5, -24, 180, 1000, {.forwards=false, .lead=0, .maxSpeed=70, .minSpeed=5, .earlyExitRange=2}, false);

    // shuffle the cubes around

    robot->intake.outtakeTop();
    robot->chassis.moveToPose(48, 0, 180, 3000, {.forwards=false, .lead=0, .maxSpeed=70, .earlyExitRange=2}, false);  // basically a wait but backing up into the goal
    robot->intake.stopIntake();

    // Drive away from match loader and turn around to go to the next one
    robot->chassis.moveToPose(48.5, -45, 180, 1300, {.lead=0, .maxSpeed=90, .minSpeed=10, .earlyExitRange=2});


    // GO TO LEFT SIDE OF FIELD --------------------------------------------------
    robot->chassis.turnToHeading(-90, 400, {.maxSpeed=100}, false);
    robot->chassis.moveToPose(-47, -45, -90, 5000, {.lead=0}, false);

    // turn and get matchloads
    robot->chassis.turnToHeading(180, 400, {.maxSpeed=100}, false);
    robot->intake.intakePneumatic.set_value(true);
    pros::delay(100); // let the match loader fall down
    robot->intake.intakeNoOuttake();


    robot->chassis.moveToPose(-47.5, -56, 180, 500, {.lead=0, .minSpeed=5}, false);  // go get real personal
    robot->chassis.moveToPose(-47.5, -65, 180, 1100, {.lead=0, .maxSpeed=35, .minSpeed=5}, false);  // get first three
    robot->chassis.moveToPose(-47.5, -56, 180, 500, {.forwards=false, .lead=0, .minSpeed=20}, false);  // back out of that joint
    pros::delay(300);
    robot->chassis.moveToPose(-47.5, -65, 180, 2000, {.lead=0, .maxSpeed=35, .minSpeed=5}, false);  // get the next three


    robot->intake.stopIntake();
    robot->intake.intakePneumatic.set_value(false);

    // drive and score on long goal
    robot->chassis.moveToPose(-48.5, -24, 180, 1000, {.forwards=false, .lead=0, .maxSpeed=70, .minSpeed=5, .earlyExitRange=2}, false);

    // // shuffle the cubes around

    robot->intake.outtakeTop();
    robot->chassis.moveToPose(-48.5, 0, 180, 3000, {.forwards=false, .lead=0, .maxSpeed=70, .earlyExitRange=2}, false);  // basically a wait but backing up into the goal
    robot->intake.stopIntake();
    robot->matchLoaderPneumatic.set_value(false);

    // RESET POSITION TO WHAT IT SHOULD BE
    pros::delay(300);
    robot->chassis.setPose(-48, -29, robot->chassis.getPose().theta);


    // --------- MATCHLOADER #3 --------------------------------------------------
    // Drive away from match loader and turn around to go to the next one
    robot->chassis.moveToPose(-47, -43, 180, 1300, {.lead=0, .maxSpeed=90, .minSpeed=40, .earlyExitRange=2});
    robot->chassis.turnToHeading(-90, 700, {.maxSpeed=80}, false);
    robot->chassis.moveToPose(-61, -43, -90, 1300, {.lead=0, .maxSpeed=90, .minSpeed=10, .earlyExitRange=2});
    robot->chassis.turnToHeading(0, 400, {.maxSpeed=100}, false);

    // Go across field
    robot->intake.stopIntake();
    robot->chassis.moveToPose(-63.5, 48, 0, 3000, {.lead=0, .maxSpeed=100, .minSpeed=10, .earlyExitRange=2});

    // Line up to match loader
    robot->chassis.turnToHeading(90, 400, {.maxSpeed=100}, false);
    robot->chassis.moveToPose(-51.5, 48, 90, 1300, {.lead=0, .maxSpeed=90, .minSpeed=10, .earlyExitRange=2});
    robot->chassis.turnToHeading(0, 700, {.maxSpeed=80}, false);

    pros::screen::print(pros::E_TEXT_MEDIUM, 1, "X: %f", robot->chassis.getPose().x);
    pros::screen::print(pros::E_TEXT_MEDIUM, 2, "Y: %f", robot->chassis.getPose().y);
    pros::screen::print(pros::E_TEXT_MEDIUM, 3, "Theta: %f", robot->chassis.getPose().theta);

    // Get match loads
    robot->intake.intakePneumatic.set_value(true);
    robot->matchLoaderPneumatic.set_value(true);
    pros::delay(100); // let the match loader fall down
    robot->intake.intakeNoOuttake();

    robot->chassis.moveToPose(-51.5, 56, 0, 300, {.lead=0, .minSpeed=5}, false);  // go get real personal
    robot->chassis.moveToPose(-51.5, 65, 0, 1100, {.lead=0, .maxSpeed=35, .minSpeed=5}, false);  // get first three
    robot->chassis.moveToPose(-51.5, 56, 0, 500, {.forwards=false, .lead=0, .minSpeed=20}, false);  // back out of that joint
    pros::delay(300);
    robot->chassis.moveToPose(-51.5, 65, 0, 2000, {.lead=0, .maxSpeed=35, .minSpeed=5}, false);  // get the next three


    // back up out of the matchloader and turn
    robot->chassis.moveToPose(-51, 45, 0, 3000, {.forwards=false, .lead=0, .minSpeed=5}, false);
    robot->chassis.turnToHeading(90, 400, {.maxSpeed=100}, false);

    // Go across field  -----------------------------------------
    robot->chassis.moveToPose(46, 45, 90, 5000, {.lead=0}, false);
    robot->intake.stopIntake();

    robot->chassis.turnToHeading(0, 400, {.maxSpeed=100}, false);
    robot->intake.intakePneumatic.set_value(false);

    // drive and score on long goal
    robot->chassis.moveToPose(47, 24, 0, 1000, {.forwards=false, .lead=0, .maxSpeed=70, .minSpeed=5, .earlyExitRange=2}, false);

    robot->intake.outtakeTop();
    robot->chassis.moveToPose(47, 0, 0, 3000, {.forwards=false, .lead=0, .maxSpeed=70, .earlyExitRange=2}, false);  // basically a wait but backing up into the goal
    robot->intake.stopIntake();
    //

    // --------- MATCHLOADER #4 --------------------------------------------------
    robot->intake.intakeNoOuttake();
    robot->intake.intakePneumatic.set_value(true);

    robot->chassis.moveToPose(46, 59, 0, 1000, {.lead=0, .minSpeed=5}, false);  // go get real personal
    robot->chassis.moveToPose(46, 68, 0, 1100, {.lead=0, .maxSpeed=35, .minSpeed=5}, false);  // get first three
    robot->chassis.moveToPose(46, 59, 0, 500, {.forwards=false, .lead=0, .minSpeed=20}, false);  // back out of that joint
    pros::delay(300);
    robot->chassis.moveToPose(46, 68, 0, 2000, {.lead=0, .maxSpeed=35, .minSpeed=5}, false);  // get the next three

    robot->intake.stopIntake();

    // back up out of the matchloader and turn
    robot->chassis.moveToPose(45, 45, 0, 3000, {.forwards=false, .lead=0, .minSpeed=5}, false);
    robot->chassis.turnToHeading(-90, 400, {.maxSpeed=100}, false);
    robot->matchLoaderPneumatic.set_value(false);

    // SCORING THE LAST LONG GOAL

    // drive across field
    robot->chassis.moveToPose(-49, 45, -90, 5000, {.lead=0}, false);
    robot->chassis.turnToHeading(0, 400, {.maxSpeed=100}, false);
    robot->intake.intakePneumatic.set_value(false);

    // drive and score on long goal
    robot->chassis.moveToPose(-47, 24, 0, 1000, {.forwards=false, .lead=0, .maxSpeed=70, .minSpeed=5, .earlyExitRange=2}, false);

    robot->intake.outtakeTop();
    robot->chassis.moveToPose(-47, 0, 0, 3000, {.forwards=false, .lead=0, .maxSpeed=70, .earlyExitRange=2}, false);  // basically a wait but backing up into the goal
    robot->intake.stopIntake();


}
