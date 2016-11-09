//
// Created by endargon on 10/25/16.
//

#include "receiver.h"

void Receiver::main() {
    long long int received = 0;
    for (; ;) {
        wait(enabled);
        if(received+(4*rtos::ms) < hwlib::now_us())  {
            bits = 0;
            amount_bits_found = 0;
        }
        idle();
        Command c(bits);
        c.print_command();
        amount_bits_found = 0;
        bits = 0;
        hwlib::wait_ms(3);
    }
}

void Receiver::idle() {
    bool starting = true;
    while (starting) {
        if (signal.get() == 0) {
            hwlib::wait_us(400);
            if (signal.get() == 0) {
                hwlib::wait_us(800);
                if (signal.get() == 0) {
                    hwlib::wait_us(800);
                    //start bit found
                    bits |= (1 << (max_bits-1));
                    amount_bits_found++;
                    starting = false;
                    while (amount_bits_found < 16) {
                        signal_found();
                    }
                }
            }

        }
    }
}

void Receiver::signal_found() {
    if(signal.get() == 0) {
        hwlib::wait_us(1200);
        if (signal.get() == 1) {
            amount_bits_found++;
            hwlib::cout << "0";

        } else if (signal.get() == 0) {
            bits |= (1 << (max_bits - amount_bits_found));
            amount_bits_found++;
            hwlib::cout << "1";

        }
        hwlib::wait_us(600);
    }
}