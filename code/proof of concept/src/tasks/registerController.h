//
// Created by endargon on 10/27/16.
//

#ifndef CODE_REGISTERCONTROLLER_H
#define CODE_REGISTERCONTROLLER_H

#include "../../../libs/rtos/rtos.hpp"
#include "controller.h"
#include "../../../libs/hwlib/hwlib-ostream.hpp"
#include "displayController.h"

class RegisterController : public Controller, public rtos::task<> {
    rtos::flag enabled;
    DisplayController &displayCtrl;
    void main();

public:
    void enable();

    void receive(Command c);

    const char *get_name() {
        return this->name();
    }

    RegisterController(DisplayController &dCtrl);

};

#endif //CODE_REGISTERCONTROLLER_H
