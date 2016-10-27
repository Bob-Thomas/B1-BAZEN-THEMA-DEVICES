//
// Created by endargon on 10/25/16.
//

#include "receiver.h"

void Receiver::main() {
    rtos::timer receive_timer(this, "receive-timer");
    long long int message_received = 0;
    for (;;) {
        wait(enabled);
        while (true) {
            if (signal.get() == 0) {
                receive_timer.set(700*rtos::us);
                wait(receive_timer);

                if (signal.get() == 0) {
                    signal_found.set();
                    break;
                }

            }
            receive_timer.set(1*rtos::ms);
            wait(receive_timer);
        }
        wait(signal_found);
        bool in_progress = true;
        receive_timer.set(500*rtos::us);
        wait(receive_timer);
        if (signal.get() == 1) {
            in_progress = false;
            bit_found = true;
            bit_value = false;
            receive_timer.set(400*rtos::us);
            wait(receive_timer);
        }
        if (signal.get() == 0 && in_progress) {
            bit_found = true;
            bit_value = true;
            receive_timer.set(400*rtos::us);
            wait(receive_timer);
        }

        if (bit_found == true) {

            if (amount_bits_found < 16) {
                amount_bits_found++;
                if(bit_value) {
                    bits |= (1 << (max_bits - amount_bits_found));
                }
            } else {
                if(message_received != 0 && message_received - hwlib::now_us() / 1000 < 4 && last_command.encode() == bits) {
                    last_command = Command(bits);
                } else {
                    if(!last_command.get_error()) {
                        controller->receive(last_command);
                    }
                }
                message_received = hwlib::now_us()/10000;
                amount_bits_found = 0;
            }

            bit_found = false;
        }
        receive_timer.set(1*rtos::s);
        wait(receive_timer);
    }
}