//
// Created by robbie on 10-11-2016.
//

#include "buttonController.h"

ButtonController::ButtonController(Controller *ctrl, hwlib::pin_out &gnd, hwlib::pin_out &vlt, hwlib::pin_in &b): task("Button controller"), controller(ctrl), ground(gnd), voltage(vlt), button(b), clock(this, 150 * rtos::ms, "a clock for button") {
    voltage.set(1);
    ground.set(0);
}

void ButtonController::main() {

    for(;;) {

        wait(clock);
        if(!button.get()) {
            controller->button_pressed();
        }

    }

}