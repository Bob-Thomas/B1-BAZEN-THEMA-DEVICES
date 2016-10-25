//
// Created by endargon on 10/25/16.
//

#include "gameClock.h"


void GameClock::main(void) {
    for(;;) {
        if(clock_started) {
            hwlib::cout << "CLOCK ACTIVE\n";
            if (!countdown_running && !game_running) {
                countdown_running = true;
            }
            if (countdown_running) {
                if (start_time == 0) {
                    hwlib::cout << "countdown started\n";
                    start_time = hwlib::now_us() / 1000;
                }
                if (hwlib::now_us() / 1000 > start_time + (countdown * 1000)) {
                    hwlib::cout << "count down ended\n";
                    hwlib::cout << "GAME STARTED\n";
                    start_time = hwlib::now_us() / 1000;
                    countdown_running = false;
                    game_running = true;
                }
            }
            if (game_running) {
                if (hwlib::now_us() / 1000 > start_time + (duration * 1000)) {
                    hwlib::cout << "game ended\n";
                    start_time = 0;
                    game_running = false;
                    clock_started = false;
                }
            }
            sleep(1 * rtos::s);
        } else {
            sleep(1 * rtos::ms);
        }
    }
}

void GameClock::set_countdown(int countdown) {
    this->countdown = countdown;
}

void GameClock::start() {
    this->clock_started = true;
}

void GameClock::set_duration(int duration) {
    this->duration = duration;
}

bool GameClock::started() {
    return clock_started;
}

bool GameClock::is_countdown_running() {
    return countdown_running;
}

bool GameClock::is_game_running() {
    return game_running;
}











