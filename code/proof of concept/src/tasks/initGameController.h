//
// Created by endargon on 10/26/16.
//

#ifndef CODE_INITGAMECONTROLLER_H
#define CODE_INITGAMECONTROLLER_H

#include "../../../libs/rtos/rtos.hpp"
#include "../../../libs/hwlib/hwlib.hpp"
#include "controller.h"
#include "transmitter.h"
#include "displayController.h"
#include "stdlib.h"

/**
 * \class InitGameController
 * \brief can be interpretted as playing state and will handle each event during his state.
 */

class InitGameController :  public Controller, public rtos::task<> {
    /**
     * transmitter boundary for sending data
     */
    Transmitter &transmitter;
    /**
     * keypad boundary for getting input
     */
    hwlib::keypad<16> &keypad;
    /**
     * displayController to display text on oled
     */
    DisplayController &displayCtrl;
    /**
     * RTOS enable flag to atctivate task
     */
    rtos::flag enabled;
    /**
     * RTOS flag foor command available
     */
    rtos::flag command_available;
    /**
     * COMMAND class for encoding and decoding bits
     */
    Command command;

    /**
     * int player_id is NOT admin id! it will be the player id to give
     */
    int player_id;
    /**
     * int weapon_id is weapon id to give
     */
    int weapon_id;
    /**
     * function valid_id will combine 2 input chars from keypad to 1 integer value.
     * integer value will be validated. Must be between 1 and 31. When true, return the valid id.
     * On failure, return 0.
     */
    int valid_id(char first, char second);
    /**
     * short custom_command will be the inputted command by leader with keypad.
     */
    short custom_command = 0;
    /**
     * command_full present a boolean value.
     * Used to check if player
     */
    char command_full;
    /**
     * RTOS main task function
     */
    void main();

public:

    /**
     * interface function to set flag that will activate task
     */
    void enable();

    /**
     * interface function for receiving command
     * /param Command c
     */
    void receive(Command c);
    /**
     * interface function for getting controller name
     */
    const char * get_name() {
        return this->name();
    }
    /**
     * InitGameController constructor
     * /param Transmitter &transmitter is a boundary object to send data
     * /param hwlib::keypad<16> &keypad is HWLIB boundary for keypad input
     * /param DisplayController &displayCtrl reference to display controller for handling text
     */
    InitGameController(Transmitter &transmitter, hwlib::keypad<16> &keypad, DisplayController &displayCtrl);
};
#endif //CODE_INITGAMECONTROLLER_H
