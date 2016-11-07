//
// Created by endargon on 10/26/16.
//

#ifndef CODE_INITGAMECONTROLLER_H
#define CODE_INITGAMECONTROLLER_H

#include "../../../libs/rtos/rtos.hpp"
#include "../../../libs/hwlib/hwlib.hpp"
#include "controller.h"
#include "transmitter.h"

class InitGameController :  public Controller, public rtos::task<> {
    Transmitter &transmitter;
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
    InitGameController(Transmitter &transmitter);
};
#endif //CODE_INITGAMECONTROLLER_H
