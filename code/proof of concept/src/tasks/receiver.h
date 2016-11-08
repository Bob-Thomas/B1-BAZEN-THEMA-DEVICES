//
// Created by endargon on 10/25/16.
//

#ifndef B1_BAZEN_THEMA_DEVICES_RECEIVER_H
#define B1_BAZEN_THEMA_DEVICES_RECEIVER_H

#include "../../../libs/rtos/rtos.hpp"
#include "../../../libs/hwlib/hwlib.hpp"
#include "controller.h"

class Receiver : public rtos::task<> {
    hwlib::pin_in &signal;
    Controller *controller;
    rtos::flag enabled;
    rtos::timer timer;
    Command last_command;
    int amount_bits_found = 0;
    int max_bits = 16;
    bool bit_value = false;

    void main();

public:
    Receiver(const char *name, hwlib::pin_in &signal, Controller *controller)
            : task(name), signal(signal), controller(controller), enabled(this, "receiver-enabled"),
              timer(this) { }

    void enable() {
        enabled.set();
    }

    void set_controller(Controller *c) {
        this->controller = c;
    }

    Controller *get_controller() {
        return controller;
    }

    void bit_one();

    void bit_zero();

    void idle();

    void signal_found();

    bool bit_found;
};

#endif //B1_BAZEN_THEMA_DEVICES_RECEIVER_H
//1 10000 00100 10100
//1 00010 00110