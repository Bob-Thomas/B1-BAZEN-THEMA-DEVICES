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
    Controller* controller;
    rtos::flag enabled;
    rtos::flag signal_found;
    Command last_command;
    unsigned short bits;
    int amount_bits_found = 0;
    int max_bits = 16;
    bool bit_found = true;
    bool bit_value = false;

    void main();

public:
    Receiver(const char *name, hwlib::pin_in &signal, Controller *controller)
            : task(name), signal(signal), controller(controller), enabled(this, "receiver-enabled"), signal_found(this, "signal-found") { }

    void enable() {
        enabled.set();
    }

    void set_controller(Controller* c) {
        this->controller = c;
    }

    Controller* get_controller() {
        return controller;
    }

};

#endif //B1_BAZEN_THEMA_DEVICES_RECEIVER_H
