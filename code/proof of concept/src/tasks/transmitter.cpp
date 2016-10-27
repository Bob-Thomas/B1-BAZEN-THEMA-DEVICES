//
// Created by endargon on 10/25/16.
//

#include "transmitter.h"

void Transmitter::main() {
    rtos::timer ir_timer(this, "ir_timer");
    for (; ;) {
        wait(command_received);
        command_mutex.wait();
        for (int j = 0; j < 2; j++) {
            //start bit
            ir.set(1);
            ir_timer.set(1600 * rtos::us);
            wait(ir_timer);

            ir.set(0);
            ir_timer.set(800 * rtos::us);
            wait(ir_timer);

            //command
            for (int i = 0; i < 16; i++) {
                if (command[i] == '0') {

                    ir.set(1);
                    ir_timer.set(800 * rtos::us);
                    wait(ir_timer);

                    ir.set(0);
                    ir_timer.set(800 * rtos::us);
                    wait(ir_timer);

                }
                if (command[i] == '1') {
                    ir.set(1);
                    ir_timer.set(1600 * rtos::us);
                    wait(ir_timer);

                    ir.set(0);
                    ir_timer.set(800 * rtos::us);
                    wait(ir_timer);
                }
            }
            ir_timer.set(3 * rtos::ms);
            wait(ir_timer);
        }
        command_mutex.signal();
    }
}

void Transmitter::send(char bits[16]) {
    command_mutex.wait();
    for(int i = 0; i < 15; i++) {
        command[i] = bits[i];
    }
    hwlib::cout << "SENDING " << command << "\n";
    command_mutex.signal();
    command_received.set();
}