//
// Created by robbie on 8-11-2016.
//

#ifndef CODE_DISPLAYCONTROLLER_H
#define CODE_DISPLAYCONTROLLER_H

#include "../../../libs/rtos/rtos.hpp"
#include "../../../libs/hwlib/hwlib.hpp"

class DisplayController : public rtos::task<> {
private:
    hwlib::glcd_oled_buffered &oled;
    rtos::channel< char, 2048 > buffer;
    rtos::timer timer_screen;
    rtos::flag clearFlag;
    rtos::flag flushFlag;

    void main();
public:
    DisplayController(hwlib::glcd_oled_buffered &o);
    void displayText(const char *);
};


#endif //CODE_DISPLAYCONTROLLER_H
