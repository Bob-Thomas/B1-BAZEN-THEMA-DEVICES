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
#include "boundaries/sound.h"

int main() {

    //kill watch dog
    WDT->WDT_MR = WDT_MR_WDDIS;

    hwlib::wait_ms(1000);

    hwlib::cout << " starting laser tag project\n";

    Arsenal arsenal;
    arsenal.add_weapon({1,10, 20, "power beam"});
    arsenal.add_weapon({2,5, 10, "Sonic beam"});
    arsenal.add_weapon({3,1, 3, "laser beam"});


#if GAMEMODE == PLAYER
    hwlib::cout << "Enabling the player program\n";

    auto button_pin = target::pin_in(target::pins::d40);
    auto sound_pin = target::pin_out(target::pins::d10);
    auto ir_pin = target::d2_36kHz();

    Sound sound(3, sound_pin);
    Transmitter transmitter(0, ir_pin);
    DisplayController display;

    RunGameController runGameController(2, sound, transmitter, display, arsenal);
    Button button(2, button_pin, runGameController);
#else
    hwlib::cout << "Enabling the game master program\n";
#endif
    rtos::run();

}