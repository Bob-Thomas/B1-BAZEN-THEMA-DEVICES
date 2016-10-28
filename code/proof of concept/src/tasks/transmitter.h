//
// Created by endargon on 10/25/16.
//

#ifndef CODE_TRANSMITTER_H
#define CODE_TRANSMITTER_H

#include "../../../libs/rtos/rtos.hpp"
#include "../../../libs/hwlib/hwlib.hpp"

class Transmitter : public rtos::task<> {
    hwlib::target::d2_36kHz &ir;
    rtos::flag command_received;
    rtos::mutex command_mutex;
    char command[16] = {0};
    void main();
public:
    Transmitter(
            const char *name,
            hwlib::target::d2_36kHz &ir) : task(name), ir(ir), command_received(this, "transmit-flag"), command_mutex("command_mutex") {

    }

    void send(char bits[16]);
};

#endif //CODE_TRANSMITTER_H