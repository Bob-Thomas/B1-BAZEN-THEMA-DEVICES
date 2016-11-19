//
// Created by smart on 11/19/2016.
//
#include "transmitter.h"

void Transmitter::main() {
    for (; ;) {
        wait(command_received);
        for (int j = 0; j < 2; j++) {
            //command
            for (int i = 0; i < 16; i++) {
                bool bit = ((command_bits >> (15 - i)) & 1);
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

void Transmitter::send(short bits) {
    command_bits = bits;
    command_received.set();
}