//
// Created by endargon on 10/27/16.
//

#ifndef CODE_REGISTERCONTROLLER_H
#define CODE_REGISTERCONTROLLER_H

#include "../../../libs/rtos/rtos.hpp"
#include "controller.h"
#include "../../../libs/hwlib/hwlib-ostream.hpp"
#include "displayController.h"
#include "../entities/gameParameters.h"

class RegisterController : public Controller, public rtos::task<> {
    rtos::flag enabled;
    DisplayController &displayCtrl;
    GameParameters &gameParameters;

    void main();

public:
    void enable();

    void receive(Command c);

    const char *get_name() {
        return this->name();
    }

    RegisterController(DisplayController &d, GameParameters &gameParameters);

};

#endif //CODE_REGISTERCONTROLLER_H
