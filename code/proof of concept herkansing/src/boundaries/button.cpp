//
// Created by smart on 11/19/2016.
//

#include "button.h"

Button::Button(int priority, hwlib::pin_in pin, RunGameController& controller) : task(priority, "Button task"), clock(this, 100 * rtos::ms, "Button clock"), pin(pin), controller(controller) {}

void Button::main() {

    for(;;) {
        wait(clock);
        if(!pin.get()) {
            controller.button_pressed();
        }

    }

}