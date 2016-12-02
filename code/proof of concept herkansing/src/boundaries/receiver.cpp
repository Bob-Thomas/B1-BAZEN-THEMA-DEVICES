//
// Created by smart on 11/19/2016.
//

#include "receiver.h"

Receiver::Receiver(int priority, hwlib::target::pin_in &pin, RunGameController& controller) : task(priority, "receiver task"), pin(pin), controller(controller) { }

void Receiver::main() {
    Command c = Command();
    for (; ;) {
        hwlib::wait_ms(100);
        bits = 0;
        amount_bits_found = 0;
        while (amount_bits_found < 16) {
            if (!pin.get()) {
                while (!pin.get()) {
                    highs++;
                }
                if (highs > 1600) {
                    received = hwlib::now_us();
                    bits |= 1 << (15 - amount_bits_found);
                    amount_bits_found++;
                } else {
                    received = hwlib::now_us();
                    if (amount_bits_found != 0) {
                        amount_bits_found++;
                    }
                }
                highs = 0;
            }
            if((hwlib::now_us() - received) > 4*rtos::ms) {
                received = hwlib::now_us();
                break;
            }
        }
        if(amount_bits_found >= 16) {
            c = Command(bits);
            if(!c.get_error()) {
                commands_received++;
            }
            hwlib::wait_ms(3);
        }
        if(commands_received >= 2) {
            commands_received = 0;
            controller.ir_received(c);
        }
    }
}