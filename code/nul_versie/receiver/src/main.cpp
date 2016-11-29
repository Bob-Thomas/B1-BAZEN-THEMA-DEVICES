// simple IR signal detector

#include "../../../libs/hwlib/hwlib.hpp"
#include "../../../libs/rtos/rtos.hpp"
#include "applicationLogic/command.h"

class test : public rtos::task<> {
    private:
        int highs = 0;
        short bits = 0;
        int amount_bits_found = 0;
        Command received[20];
        int counter = 0;
        hwlib::target::pin_in &pin;
        void main(){
            for(;;) {
                hwlib::wait_ms(100);
                if(counter >= 20) {
                    int correct = 0;
                    for(int i = 0; i < 20; i++) {
                        Command k = received[i];
                        hwlib::cout << "\n";
                        hwlib::cout << i << ": ";
                        k.print_command();
                        hwlib::cout << "\n";
                    }
                    counter = 0;
                    hwlib::cout << correct << "/20 - correct \n";
                } else {
                    while (amount_bits_found < 16) {
                        if (!pin.get()) {
                            while (!pin.get()) {
                                highs++;
                            }
                            if (highs > 1600) {
                                bits |= 1 << (15 - amount_bits_found);
                                amount_bits_found++;
                            } else {
                                if (amount_bits_found != 0) {
                                    amount_bits_found++;
                                }
                            }
                            highs = 0;
                        }
                    }
                    received[counter] = Command(bits);
                    counter++;
                    bits = 0;
                    amount_bits_found = 0;
                    hwlib::wait_ms(3);
                }
            }
        }

    public:
        test(hwlib::target::pin_in &pin) : task("test"), pin(pin){}
};

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

    auto kek = test(tsop_signal);

    rtos::run();
}
