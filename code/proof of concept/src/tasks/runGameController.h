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
#include "transmitter.h"
/**
 * RunGameController can be interpret as playing state and will handle each event during his state.
 */
class RunGameController : public Controller, public rtos::task<> {
private:
    /**
     * flag to enable the task
     */
    rtos::flag enabled;
    /**
     * rtos flag will be used for detecting button press
     */
    rtos::flag pressed;
    /**
     * gameParameters will be an entity object for storring the personal player data.
     */
    GameParameters &gameParameters;

    /**
     * DisplayController reference handles text display on oled screen.
     */
    DisplayController &displayCtrl;

    /**
     * RTOS task function.
     */
    void main();

public:
    /**
     * interface function for activating task.
     */
    void enable();

    /**
     * interface function for receiving a command
     * /param Command c for encode en decode data.
     */
    void receive(Command c);

    /**
     * interface function for getting controller name.
     */
    const char *get_name() {
        return this->name();
    }

    /**
    * button_pressed interface function.
    */
    void button_pressed();

    /**
     * RunGameController constructor.
     * /param &gameParam to set or get player game settings.
     * /param &disCtrl to write text on screen.
     */
    RunGameController(GameParameters &gameParam, DisplayController &disCtrl);
};

#endif //CODE_RUNEGAMECONTROLLER_H
