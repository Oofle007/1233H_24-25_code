//   ___           _                    __
//  |_ _|  _ __   | |_    ___   _ __   / _|   __ _    ___    ___
//   | |  | '_ \  | __|  / _ \ | '__| | |_   / _` |  / __|  / _ \
//   | |  | | | | | |_  |  __/ | |    |  _| | (_| | | (__  |  __/
//  |___| |_| |_|  \__|  \___| |_|    |_|    \__,_|  \___|  \___|

#include "../include/hteam/interface.h"
#include "../include/hteam/autons.h"

std::string toString(Auton auton) {
    switch (auton) {
        case NONE: return "None";
        case RED_1: return "Red 1";
        case RED_2: return "Red 2";
        case RED_3: return "Red 3";
        case RED_4: return "Red 4";
        case BLUE_1: return "Blue 1";
        case BLUE_2: return "Blue 2";
        case BLUE_3: return "Blue 3";
        case BLUE_4: return "Blue 4";
        case SKILLS: return "Skills";
        default: return "Unknown";
    }
}

void Interface::drawBn(std::int16_t x0, std::int16_t y0, std::int16_t x1, std::int16_t y1, pros::Color BGcolor,
                       std::string text) {

    pros::screen::set_pen(BGcolor);

    // Draw the rectangle
    pros::screen::draw_rect(x0, y0, x1, y1);

    // Estimate the text width and height based on a fixed character width and height
    int char_width = 8; // Approximate width of a character in pixels
    int char_height = 16; // Approximate height of a character in pixels
    int text_width = text.length() * char_width;
    int text_height = char_height;

    // Calculate the position to start drawing the text
    int rect_width = x1 - x0;
    int rect_height = y1 - y0;
    int text_x = x0 + (rect_width - text_width) / 2;
    int text_y = y0 + (rect_height - text_height) / 2;

    // Draw the text
    pros::screen::set_pen(pros::Color::white);
    pros::screen::print(pros::E_TEXT_MEDIUM, text_x, text_y, text.c_str());
}

Interface::Interface() :
    screen("Red"), selectedAuton(NONE) {
}

void Interface::run() {
    int touch_x = 0;
    int touch_y = 0;

    // Draw Top selector

    // Draw background
    pros::screen::set_pen(pros::Color::black);
    pros::screen::fill_rect(0, 0, 480, 60);

    // Draw Border
    pros::screen::set_pen(pros::Color::dim_gray);
    pros::screen::fill_rect(0, 0, 480, 5);  // Top line
    pros::screen::fill_rect(0, 55, 480, 60);  // Bottom Line
    pros::screen::fill_rect(0, 0, 5, 60);  // Leftmost line
    pros::screen::fill_rect(475, 0, 480, 60);  // Rightmost Line
    pros::screen::fill_rect(155, 0, 160, 60);  // Left Middle line
    pros::screen::fill_rect(315, 0, 320, 60);  // Right Middle line

    // Draw Text
    pros::screen::set_pen(pros::Color::white);
    pros::screen::print(pros::E_TEXT_LARGE, 50, 15, "Red");
    pros::screen::print(pros::E_TEXT_LARGE, 200, 15, "Blue");
    pros::screen::print(pros::E_TEXT_LARGE, 340, 15, "Skills");

    updateScreen(touch_x, touch_y);

    while (true) {
        pros::screen_touch_status_s_t touch_status = pros::screen::touch_status();  // Get any screen touch x and y coords

        // Checking if any part of the screen was touched by comparing the last values to the current ones
        if ((touch_x != touch_status.x) || (touch_y != touch_status.y)) {
            updateScreen(touch_status.x, touch_status.y);

            // Reset previous touch values
            touch_x = touch_status.x;
            touch_y = touch_status.y;
        }

        if (selectedAuton != NONE) {  // If you selected an auton
            // Clear entire screen
            pros::screen::set_pen(pros::Color::black);
            pros::screen::fill_rect(0, 0, 480, 240);

            // Display selected auton
            pros::screen::set_pen(pros::Color::white);

            if (screen == "Red") {
                pros::screen::set_pen(pros::Color::red);
            } else if (screen == "Blue") {
                pros::screen::set_pen(pros::Color::blue);
            } else {
                pros::screen::set_pen(pros::Color::white);
            }
            pros::screen::draw_rect(5, 5, 475, 235);

            pros::screen::set_pen(pros::Color::white);
            pros::screen::print(pros::E_TEXT_LARGE, 100, 100, "%s", toString(selectedAuton));
            break;
        }

        pros::delay(20); // don't hog resources
    }
}

void Interface::updateScreen(int x, int y) {
    // Check for if the top slider was clicked
    if (y < 60) {
        if (x < 160) {  // Red
            screen = "Red";
            resetScreen();
            displayRedScreen();
        } else if (x < 320) {  // Blue
            screen = "Blue";
            resetScreen();
            displayBlueScreen();
        } else {  // Skills
            screen = "Skills";
            resetScreen();
            displaySkillsScreen();
        }
    } else {

        // Iterate over all the buttons and detect if the touched coords were inside any buttons
        for (const auto &button: buttons) {
            if (x >= button.x0 && x <= button.x1 && y >= button.y0 && y <= button.y1) {
                selectedAuton = button.auton; // Set the selected auton so the autonomous can run it
                break;
            }
        }
    }
}

void Interface::resetScreen() {
    pros::screen::set_pen(pros::Color::black);

    // Reset big area
    pros::screen::fill_rect(0, 60, 480, 240);

    // Reset each color box for top slider
    pros::screen::fill_rect(6, 45, 154, 55);
    pros::screen::fill_rect(161, 45, 314, 55);
    pros::screen::fill_rect(321, 45, 474, 55);

    buttons.clear();  // Clear existing buttons before creating new ones
}

void Interface::displayRedScreen() {
    // Display top slider color
    pros::screen::set_pen(pros::Color::red);
    pros::screen::fill_rect(6, 45, 154, 55);

    // Create all the buttons for the screen
    createButton(10, 70, 117, 230, "RSWP", pros::Color::red, RED_1);
    createButton(128, 70, 235, 230, "L4MOGO", pros::Color::red, RED_2);
    createButton(245, 70, 352, 230, "Auton 3", pros::Color::red, RED_3);
    createButton(362, 70, 470, 230, "Auton 4", pros::Color::red, RED_4);
}

void Interface::displayBlueScreen() {
    // Display top slider color
    pros::screen::set_pen(pros::Color::blue);
    pros::screen::fill_rect(161, 45, 314, 55);

    // Create all the buttons for the screen
    createButton(10, 70, 117, 230, "LSWP", pros::Color::blue, BLUE_1);
    createButton(128, 70, 235, 230, "R4MOGO", pros::Color::blue, BLUE_2);
    createButton(245, 70, 352, 230, "Auton 3", pros::Color::blue, BLUE_3);
    createButton(362, 70, 470, 230, "Auton 4", pros::Color::blue, BLUE_4);

}

void Interface::displaySkillsScreen() {
    // Display top slider color
    pros::screen::set_pen(pros::Color::white);
    pros::screen::fill_rect(321, 45, 474, 55);

    // Create the skills button
    createButton(30, 90, 450, 210, "45 PT SKILLS", pros::Color::white, SKILLS);
}

void Interface::createButton(std::int16_t x0, std::int16_t y0, std::int16_t x1, std::int16_t y1, std::string text,
                             pros::Color color,
                             Auton auton) {

    drawBn(x0, y0, x1, y1, color, text);
    Button button = {x0, y0, x1, y1, text, auton};
    buttons.push_back(button);
}

Auton Interface::getSelectedAuton() {
    return selectedAuton;
}