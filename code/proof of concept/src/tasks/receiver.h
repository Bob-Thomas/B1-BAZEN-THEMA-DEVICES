//
// Created by endargon on 10/25/16.
//

#ifndef B1_BAZEN_THEMA_DEVICES_RECEIVER_H
#define B1_BAZEN_THEMA_DEVICES_RECEIVER_H

#include "../../../libs/rtos/rtos.hpp"
#include "../../../libs/hwlib/hwlib.hpp"
#include "comStation.h"

class Receiver : public rtos::task<> {
        hwlib::pin_in & signal;
        rtos::flag signal_found;
        char bits[16];
        int amount_bits_found = 0;
        bool bit_found = true;
        bool bit_value = false;
        ComStation &com_station;

        void main();

    public:
        Receiver(const char* name, hwlib::pin_in& signal, ComStation &com_station)
                : task(name), signal(signal), signal_found(this, "signal-found"), com_station(com_station){}

};

#endif //B1_BAZEN_THEMA_DEVICES_RECEIVER_H
