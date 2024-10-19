#include "hteam/functions.h"

Toggle::Toggle() : state(false), pressed(false) {}

bool Toggle::update(bool input) {
    if (input) {
        if (!pressed) {
            state = !state;
            pressed = true;
        } else {
            pressed = false;
        }
    }
    return state;
}
