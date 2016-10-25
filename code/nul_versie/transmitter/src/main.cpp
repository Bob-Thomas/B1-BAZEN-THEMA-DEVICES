#include "bmptk.h"
#include "hwlib.hpp"
#include "rtos.hpp"

class send_ir : public rtos::task<> {
    hwlib::target::d2_36kHz &ir;
    hwlib::target::pin_in_out &button;
    rtos::timer ir_timer;
    char bits[16] = {'1', '0', '0', '0', '1', '0', '0', '0', '1', '0', '0', '0', '1', '0', '0', '0'};

    void main() {
        for (; ;) {
            bool clicked = !button.get();
            while (clicked) {
                for(int j = 0; j < 2; j++) {
                    //start bit
                    ir.set(1);
                    ir_timer.set(1600*rtos::us);
                    wait(ir_timer);

                    ir.set(0);
                    ir_timer.set(800*rtos::us);
                    wait(ir_timer);

                    //command
                    for (int i = 0; i < 16; i++) {
                        if (bits[i] == '0') {

                            ir.set(1);
                            ir_timer.set(800 * rtos::us);
                            wait(ir_timer);

                            ir.set(0);
                            ir_timer.set(800 * rtos::us);
                            wait(ir_timer);

                        }
                        if (bits[i] == '1') {
                            ir.set(1);
                            ir_timer.set(1600 * rtos::us);
                            wait(ir_timer);

                            ir.set(0);
                            ir_timer.set(800 * rtos::us);
                            wait(ir_timer);
                        }
                    }
                    ir_timer.set(3 * rtos::ms);
                    wait(ir_timer);
                }
                clicked = !button.get();
            }
        }
    }

public:
    send_ir(
            const char *name,
            hwlib::target::d2_36kHz &ir,
            hwlib::target::pin_in_out &button) : task(name), ir(ir), button(button), ir_timer(this, "ir_timer") {

    }
};

int main(void) {

    // kill the watchdog
    WDT->WDT_MR = WDT_MR_WDDIS;

    // wait for the PC console to start
    hwlib::wait_ms(500);

    hwlib::cout << "timer demo\n";

    namespace target = hwlib::target;
    auto ir = target::d2_36kHz();
    auto button = target::pin_in_out(target::pins::d7);
    auto ir_task = send_ir("ir_task", ir, button);

    rtos::run();
}
