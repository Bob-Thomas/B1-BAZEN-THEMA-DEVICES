//
// Created by robbie on 10-11-2016.
//

#ifndef CODE_BUTTONCONTROLLER_H
#define CODE_BUTTONCONTROLLER_H

#include "../../../libs/rtos/rtos.hpp"
#include "../../../libs/hwlib/hwlib.hpp"
#include "runGameController.h"

/**
 * ButtonController Task. Can set flags with interfaces form referenced controllers.
 */

/**
 * \class ButtonController
 * \brief can be interpreted as playing state and will handle each event during his state.
 */

class ButtonController : public rtos::task<> {
private:
    /**
     * abstract controller to use interface function
     */
    Controller* controller;
    /**
     * pin settings for the button
     */
    hwlib::pin_out &ground;
    hwlib::pin_out &voltage;
    hwlib::pin_in &button;

    /**
     * RTOS task function
     */
    void main();
    /**
     * clock for polling button press
     */
    rtos::clock clock;
public:
    /**
     * Constructor ButtonController.
     * /param ctrl reference for using controller interface
     * /param gnd reference pin requires output pin
     * /param vlt reference pin requires output pin
     * /param b reference pin requires input pin
     */
    ButtonController(Controller *ctrl, hwlib::pin_out &gnd, hwlib::pin_out &vlt, hwlib::pin_in &b);

    /**
     * Sets the controller the button will send messages to
     */
    void set_listener(Controller *ctrl) {
        this->controller = ctrl;
    }
};


#endif //CODE_BUTTONCONTROLLER_H
