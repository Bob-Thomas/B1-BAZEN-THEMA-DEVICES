//
// Created by endargon on 10/25/16.
//

#include "../../libs/hwlib/hwlib.hpp"
#include "tasks/gameClock.h"
#include "tasks/gameManager.h"
#include "tasks/transmitter.h"

int main() {
#if GAMEMODE == PLAYER
    hwlib::cout << "Player";
#else
    hwlib::cout << "Leader";
#endif

    // kill the watchdog
    WDT->WDT_MR = WDT_MR_WDDIS;

    // wait for the PC console to start
    hwlib::wait_ms(500);

    hwlib::cout << "timer demo\n";

    namespace target = hwlib::target;
    auto ir = target::d2_36kHz();
    auto game_clock = GameClock("gameClock", 5, 5);
    auto transmitter = Transmitter("transmitter", ir);
    auto game_manager = GameManager("gameManager", game_clock, transmitter);

    rtos::run();
}