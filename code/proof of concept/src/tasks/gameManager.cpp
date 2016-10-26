//
// Created by endargon on 10/25/16.
//

#include "gameManager.h"

void GameManager::main() {
    rtos::timer test_timer(this, "testTimer");
    test_timer.set(5*rtos::s);
    rtos::clock test_clock(this, 1*rtos::s, "testClock");

    for(;;) {
        wait(test_timer);
        if(!game_clock.started()) {
            game_clock.start();
        }
        while(1) {
            if(game_clock.is_countdown_running()) {
                hwlib::cout << "COUNTING DOWN\n";
            } else if(game_clock.is_game_running()) {
//                com_station.send_command({1,2});
                hwlib::cout << "GAME IS RUNNING\n";
//                auto event = wait(test_clock);
//                if(event == test_clock) {
//                    com_station.send_command({1, 1});
//                }

            } else if(!game_clock.started()) {
                hwlib::cout << "GAME STOPPED\n";
            }
            test_timer.set(1*rtos::ms);
            wait(test_timer);
        }
    }
}

