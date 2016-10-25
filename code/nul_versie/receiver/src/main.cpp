// simple IR signal detector

#include <rtos.hpp>
#include "hwlib.hpp"

char bits[16];
bool bit_found = false;
bool bit_value = false;

void idle(hwlib::pin_in & signal);
void signal_found(hwlib::pin_in & signal);
void bit_zero();
void bit_one();

void bit_zero() {
    bit_found = true;
    bit_value = false;
    hwlib::wait_us(400);
}

void bit_one() {
    bit_found = true;
    bit_value = true;
    hwlib::wait_us(400);
}

void signal_found(hwlib::pin_in & signal) {

    bool in_progress = true;

    hwlib::wait_us(500);

    if(signal.get() == 1) {
        in_progress = false;
        bit_zero();
    }

    if(signal.get() == 0 && in_progress == true) {
        bit_one();
    }

}

void idle(hwlib::pin_in & signal) {

    bool starting = true;

    while(starting) {
        if(signal.get() == 0) {

            hwlib::wait_us(700);

            if(signal.get() == 0) {
                starting = false;
                signal_found(signal);
            }

        }

    }
}


int main( void ){

    // kill the watchdog
    WDT->WDT_MR = WDT_MR_WDDIS;

    hwlib::wait_ms(500);
    namespace target = hwlib::target;

    auto tsop_signal = target::pin_in( target::pins::d8 );
    auto tsop_gnd    = target::pin_out( target::pins::d9 );
    auto tsop_vdd    = target::pin_out( target::pins::d10 );
    tsop_gnd.set( 0 );
    tsop_vdd.set( 1 );

   // auto led         = target::pin_out( target::pins::led );

    //auto const active = 100'000;
    //auto last_signal = hwlib::now_us() - active;

    int amount_bits_found = 0;
    for(;;){

        // listen state
        idle(tsop_signal);

        // bit found
        if(bit_found == true) {

            if(amount_bits_found < 16) {
                (bit_value) ? bits[amount_bits_found] = '1' : bits[amount_bits_found] = '0';
                amount_bits_found++;
            } else{

                for(int i = 0; i < 16; i++) {
                    hwlib::cout << bits[i];
                }

                hwlib::cout << "\n-";
                amount_bits_found = 0;
            }

            bit_found = false;
        }

    }
}