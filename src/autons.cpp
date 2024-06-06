#include <utility>

#include "../include/hteam/autons.h"

Autons::Autons(std::shared_ptr<Arm> arm, std::shared_ptr<lemlib::Chassis> chassis) : arm(std::move(arm)), chassis(std::move(chassis)) {

}

void Autons::red1() {

}

void Autons::red2() {
    arm->moveToPosition(400, 0, 5);
}

void Autons::red3() {

}

void Autons::red4() {

}

void Autons::blue1() {

}

void Autons::blue2() {

}

void Autons::blue3() {

}

void Autons::blue4() {

}

void Autons::skills() {

}
