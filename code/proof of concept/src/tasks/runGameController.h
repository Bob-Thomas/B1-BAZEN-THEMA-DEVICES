//
// Created by robbie on 9-11-2016.
//

#ifndef CODE_RUNEGAMECONTROLLER_H
#define CODE_RUNEGAMECONTROLLER_H

#include "../../../libs/rtos/rtos.hpp"
#include "controller.h"
#include "../../../libs/hwlib/hwlib-ostream.hpp"
#include "displayController.h"
#include "../entities/gameParameters.h"


class RunGameController : public Controller, public rtos::task<> {
private:
    rtos::flag enabled;
    GameParameters &gameParameters;
    DisplayController &displayCtrl;
    void main();

public:
    void enable();

    void receive(Command c);

    const char *get_name() {
        return this->name();
    }

    RunGameController(GameParameters &gameParam, DisplayController &disCtrl);
};


#endif //CODE_RUNEGAMECONTROLLER_H
