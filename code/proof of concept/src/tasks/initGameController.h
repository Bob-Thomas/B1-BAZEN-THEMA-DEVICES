//
// Created by endargon on 10/26/16.
//

#ifndef CODE_INITGAMECONTROLLER_H
#define CODE_INITGAMECONTROLLER_H

#include "../../../libs/rtos/rtos.hpp"
#include "../../../libs/hwlib/hwlib.hpp"
#include "controller.h"

class InitGameController :  public Controller, public rtos::task<> {
    rtos::flag enabled;
    rtos::flag command_available;
    Command command;
    void main();

public:
    void enable();
    void receive(Command c);
    const char * get_name() {
        return this->name();
    }
    InitGameController();
};
#endif //CODE_INITGAMECONTROLLER_H
