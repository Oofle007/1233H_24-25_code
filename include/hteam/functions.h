#ifndef INC_1233H_24_25_CODE_FUNCTIONS_H
#define INC_1233H_24_25_CODE_FUNCTIONS_H

class Toggle {
public:
    Toggle();

    bool update(bool input);

private:
    bool state;
    bool pressed;
};

#endif //INC_1233H_24_25_CODE_FUNCTIONS_H
