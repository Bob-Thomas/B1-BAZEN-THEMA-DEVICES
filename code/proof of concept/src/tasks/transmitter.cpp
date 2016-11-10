//
// Created by endargon on 10/25/16.
//

#include "transmitter.h"

void Transmitter::main() {
    for (; ;) {
        wait(command_received);
        for (int j = 0; j < 2; j++) {
            //command
            for (int i = 1; i < 16; i++) {
                bool bit = ((command_bits >> (16-i))&1);
                if (!bit) {

                    ir.set(1);
                    hwlib::wait_us(800);


                    ir.set(0);
                    hwlib::wait_us(1600);


                }
                if (bit) {
                    ir.set(1);
                    hwlib::wait_us(1600);


                    ir.set(0);
                    hwlib::wait_us(800);

                }
            }
            hwlib::wait_ms(3);
        }
    }
}
//1 100000 01001 0100
void Transmitter::send(short bits) {
    command_bits = bits;
    command_received.set();
}