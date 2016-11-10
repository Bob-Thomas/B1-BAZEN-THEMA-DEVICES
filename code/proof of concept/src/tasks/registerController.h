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

/**
 * \class RegisterController
 * \brief can be interpret as register state and will handle each event during his state.
 */

class RegisterController : public Controller, public rtos::task<> {
    /**
     * enable flag to continue task
     */
    rtos::flag enabled;
    /**
    * pressed flag to check for button presses
    */
    rtos::flag pressed;
    /**
    * command_available flag to check if command is available
    */
    rtos::flag command_processed;
    /**
     * gameParameters reference for get and set player data
     */
    GameParameters &gameParameters;

    /**
     * displayCtrl for writing text oled
     */
    DisplayController &displayCtrl;

    /**
     *
     */
    bool ready_to_receive = false;

    /**
     * RTOS main tas
     */
    void main();

    /**
     * char for changing state
     */
    char next_state = 0;
public:
    /**
     * interface function to activate task function
     */
    void enable();

    /**
    * interface function to set button_pressed flag
    */
    void button_pressed();

    /**
     * interface function for receiving data
     * /param Command c to encode and decode data
     */
    void receive(Command c);

    /**
     * interface function to get name of the controller
     */
    const char *get_name() {
        return this->name();
    }

    /**
     * function for change stat
     */
    int state() {
        return next_state;
    }

    /**
     * RegisterController Constructor
     * /param GameParameters  &gp for get and set player data
     * /param Display Controller &dCtrl for get and set player data
     */
    RegisterController(GameParameters &gp, DisplayController &dCtrl);

};

#endif //CODE_REGISTERCONTROLLER_H
