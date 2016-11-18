// simple IR signal detector

#include <rtos.hpp>
#include "hwlib.hpp"

int main(void) {

    // kill the watchdog
    WDT->WDT_MR = WDT_MR_WDDIS;

    hwlib::wait_ms(500);
    namespace target = hwlib::target;

    auto tsop_signal = target::pin_in(target::pins::d8);
    auto tsop_gnd = target::pin_out(target::pins::d9);
    auto tsop_vdd = target::pin_out(target::pins::d10);
    tsop_gnd.set(0);
    tsop_vdd.set(1);
    int highs = 0;
    int amount_bits_found = 0;
    for (; ;) {
        hwlib::wait_ms(100);
        while (amount_bits_found < 16)
            if (!tsop_signal.get()) {
                while (!tsop_signal.get()) {
                    highs++;
                }
                if (highs > 4000) {
                    amount_bits_found++ ;
                    hwlib::cout << "1";
                } else {
                    if(amount_bits_found != 0) {
                        amount_bits_found++;
                        hwlib::cout << "0";
                    }
                }
                highs = 0;
            }
        hwlib::cout << "\n";
        amount_bits_found = 0;
        hwlib::wait_ms(3);
    }
}
