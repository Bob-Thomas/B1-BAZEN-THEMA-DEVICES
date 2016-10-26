//
// Created by endargon on 10/25/16.
//

#include "../../libs/hwlib/hwlib.hpp"
#include "tasks/gameClock.h"
#include "tasks/gameManager.h"
#include "tasks/transmitter.h"
#include "tasks/receiver.h"
#include "tasks/comStation.h"

int main() {
#if GAMEMODE == PLAYER
    hwlib::cout << "Player";
#else
    hwlib::cout << "Leader";
#endif

    // kill the watchdog
    WDT->WDT_MR = WDT_MR_WDDIS;

    // wait for the PC console to start
    hwlib::wait_ms(1000);

    hwlib::cout << "timer demo\n";

    namespace target = hwlib::target;
    auto ir = target::d2_36kHz();
//    auto tsop_signal = target::pin_in( target::pins::d8 );
//    auto tsop_gnd    = target::pin_out( target::pins::d9 );
//    auto tsop_vdd    = target::pin_out( target::pins::d10 );
//    tsop_gnd.set( 0 );
//    tsop_vdd.set( 1 );

    auto transmitter = Transmitter("transmitter", ir);
    auto com_station = ComStation("com_station", transmitter);
//
    auto game_clock = GameClock("game_clock", 5, 5);
    auto game_manager = GameManager("game_manager", game_clock, com_station);
//
//    auto receiver = Receiver("receiver", tsop_signal, com_station);

    rtos::run();
}