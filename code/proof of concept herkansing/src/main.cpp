//
// Created by smart on 11/19/2016.
//

/*! \mainpage Laser tag
 * This is doxygen documentation for our school project named THEMA DEVICES.
 *
 * THEMA DEVICES is a group project about building a laser tag game with RTOS.
 * This is the proof of concept documentation.
 */

#include "../../libs/hwlib/hwlib.hpp"
#include "../../libs/rtos/rtos.hpp"
#include "entities/weapon.h"
#include "entities/arsenal.h"
#include "boundaries/button.h"
#include "boundaries/receiver.h"

namespace target = hwlib::target;

int main() {

    //kill watch dog
    WDT->WDT_MR = WDT_MR_WDDIS;

    hwlib::wait_ms(1000);

    hwlib::cout << " starting laser tag project\n";

    Arsenal arsenal;
    arsenal.add_weapon({1, 10, 20, (char *) "power beam"});
    arsenal.add_weapon({2, 5, 10, (char *) "Sonic beam"});
    arsenal.add_weapon({3, 1, 3, (char *) "laser beam"});


#if GAMEMODE == PLAYER
    hwlib::cout << "Enabling the player program\n";

    auto gnd = target::pin_out( target::pins::d49);
    auto vlt = target::pin_out( target::pins::d51);
    gnd.set(0);
    vlt.set(1);
    auto button_pin = target::pin_in(target::pins::d53);

    auto sound_pin = target::pin_out(target::pins::d11);
    auto ir_pin = target::d2_36kHz();

    auto tsop_signal = target::pin_in(target::pins::d8);
    auto tsop_gnd = target::pin_out(target::pins::d9);
    auto tsop_vdd = target::pin_out(target::pins::d10);
    tsop_gnd.set(0);
    tsop_vdd.set(1);

    auto sound = Sound(4, sound_pin);
    auto transmitter = Transmitter(3, ir_pin);
    auto display = DisplayController();

    auto runGameController = RunGameController(2, sound, transmitter, display, arsenal);
    auto receiver = Receiver(1, tsop_signal, runGameController);
    auto button = Button(0, button_pin, runGameController);
#else
    hwlib::cout << "Enabling the game master program\n";
#endif
    rtos::run();

}