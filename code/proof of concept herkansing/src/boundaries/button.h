//
// Created by smart on 11/19/2016.
//

#ifndef CODE_BUTTON_H
#define CODE_BUTTON_H

#include "../../../libs/rtos/rtos.hpp"
#include "../controllers/runGameController.h"
#include "../../../libs/hwlib/hwlib.hpp"


class Button : public rtos::task<> {
    private:
        rtos::clock clock;
        hwlib::target::pin_in& pin;
        RunGameController &controller;

    public:
        Button(int priority, hwlib::target::pin_in pin, RunGameController& controller);

        void main();
};
#endif //CODE_BUTTON_H
