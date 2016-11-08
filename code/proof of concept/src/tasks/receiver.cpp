//
// Created by endargon on 10/25/16.
//

#include "receiver.h"

void Receiver::main() {
    long long int received = 0;
    for (; ;) {
        wait(enabled);
        if (received + (4 * rtos::ms) < hwlib::now_us()) {
            amount_bits_found = 0;
        }
        short bits;
        bool starting = true;
        while (starting) {
            if (signal.get() == 0) {
                sleep(1600 * rtos::us);
                if (signal.get() == 0) {
                    bits |= (1 << 0);
                    amount_bits_found++;
                    while (amount_bits_found < max_bits) {
                        if (signal.get() == 0) {
                            sleep(800 * rtos::us);
                            if (signal.get() == 1) {
                                amount_bits_found++;
                                sleep(1600 * rtos::us);
                            }
                            else if (signal.get() == 0) {
                                bits |= (1 << (max_bits - amount_bits_found));
                                amount_bits_found++;
                                sleep(1600 * rtos::us);
                            }
                        }
                    }
                    Command c(bits);
                    c.print_command();
                    if(c.encode() == last_command.encode() && received+(2*rtos::ms) < hwlib::now_us()) {
                        if(!c.get_error()) {
                            controller->receive(c);
                            received = hwlib::now_us();
                        }
                    }
                    if (!c.get_error()) {
                        received = hwlib::now_us();
                        last_command = c;
                    }
                    amount_bits_found = 0;
                    bits = 0;
                    bit_found = false;
                }
            }
            starting = false;
            sleep(2 * rtos::ms);
        }
    }

}
