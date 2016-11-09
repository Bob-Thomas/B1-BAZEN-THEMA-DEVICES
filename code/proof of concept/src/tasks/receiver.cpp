//
// Created by endargon on 10/25/16.
//

#include "receiver.h"

void Receiver::main() {
//    long long int received = 0;
    for (; ;) {
        wait(enabled);
//        if(received+(4*rtos::ms) < hwlib::now_us())  {
//            bits = 0;
//            amount_bits_found = 0;
//        }
        idle();
        (bits) = (bits <<1) | 1;
        for(int i = 0; i < 16; i++) {
            bool bit = ((bits >> (15-i))&1);
            if(bit) {
                hwlib::cout << "0";
            } else {
                hwlib::cout << "1";
            }

        }
        hwlib::cout << "\n1000000101001010";
        hwlib::cout << "\n##################3\n";
        Command c(bits);
        c.print_command();
        hwlib::cout << "\n##################3\n";
        amount_bits_found = 0;
        bits = 0;
        hwlib::wait_ms(2);
    }
}

void Receiver::idle() {
    bool starting = true;
    while (starting) {
        if (signal.get() == 0) {
            hwlib::wait_us(800);
            if (signal.get() == 0) {
                starting = false;
                hwlib::wait_us(800);
                while (amount_bits_found < 16) {
                    signal_found();
                    hwlib::wait_us(800);
                }
            }

        }
    }
}

void Receiver::signal_found() {
    bool in_progress = true;
    if (signal.get() == 0) {
        hwlib::wait_us(800);
        amount_bits_found++;
        if (signal.get() == 1) {
            in_progress = false;
            bits  |= (1 << (max_bits-amount_bits_found));
        } else if (signal.get() == 0 && in_progress) {
            bits  |= (0 << (max_bits-amount_bits_found));
        }
    }


}
//1 10000 00101 00101
//1 00000 01010 01010

//0 11000 00010 10010
//1 00000 01010 01010

//0100000101001011