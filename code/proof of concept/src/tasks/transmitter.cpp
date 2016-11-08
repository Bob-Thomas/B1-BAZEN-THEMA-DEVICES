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
                bool bit = ((command_bits >> (15-i))&1);
                if (!bit) {

                    ir.set(1);
                    ir_timer.set(800 * rtos::us);
                    wait(ir_timer);

                    ir.set(0);
                    ir_timer.set(1600 * rtos::us);
                    wait(ir_timer);

                }
                if (bit) {
                    ir.set(1);
                    ir_timer.set(1600 * rtos::us);
                    wait(ir_timer);

                    ir.set(0);
                    ir_timer.set(800 * rtos::us);
                    wait(ir_timer);
                }
            }
            ir_timer.set(2 * rtos::ms);
            wait(ir_timer);
        }
        command_mutex.signal();
    }
}
//1 100000 01001 0100
void Transmitter::send(short bits) {
    command_mutex.wait();
    command_bits = bits;
    command_mutex.signal();
    command_received.set();
}