//
// Created by endargon on 10/25/16.
//

#include "gameManager.h"

void GameManager::main() {
    rtos::timer test_timer(this, "testTimer");
    test_timer.set(5*rtos::s);
    for(;;) {
        wait(test_timer);
        if(!game_clock.started()) {
            game_clock.start();
        }
        while(1) {
            if(game_clock.is_countdown_running()) {
                hwlib::cout << "COUNTING DOWN\n";
            } else if(game_clock.is_game_running()) {
                char test[16] = "101010010100101";
                transmitter.send(test);
               \ hwlib::cout << "GAME IS RUNNING\n";
            } else if(!game_clock.started()) {
                hwlib::cout << "GAME STOPPED\n";
            }
            test_timer.set(1*rtos::s);
            wait(test_timer);
        }
    }
}

