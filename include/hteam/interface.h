#ifndef INC_1233H_24_25_CODE_INTERFACE_H
#define INC_1233H_24_25_CODE_INTERFACE_H

#include "pros/screen.hpp"
#include "pros/apix.h"
#include "main.h"

enum Auton {
    NONE,
    RED_1,
    RED_2,
    RED_3,
    RED_4,
    BLUE_1,
    BLUE_2,
    BLUE_3,
    BLUE_4,
    SKILLS
};

class Interface {
public:
    Interface();

    void run();
    Auton getSelectedAuton();

private:

    std::string screen;
    void updateScreen(int x, int y);
    void resetScreen();
    void drawBn(std::int16_t x0, std::int16_t y0, std::int16_t x1, std::int16_t y1, pros::Color BGcolor, std::string text);

    struct Button {
        std::int16_t x0, y0, x1, y1;
        std::string text;
        Auton auton;
    };

    std::vector<Button> buttons;
    Auton selectedAuton;

    void displayRedScreen();
    void displayBlueScreen();
    void displaySkillsScreen();
    void createButton(std::int16_t x0, std::int16_t y0, std::int16_t x1, std::int16_t y1, std::string text, pros::Color color, Auton auton);
};
#endif //INC_1233H_24_25_CODE_INTERFACE_H
