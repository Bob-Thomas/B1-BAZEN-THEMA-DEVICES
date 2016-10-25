//
// Created by endargon on 10/25/16.
//

#ifndef CODE_GAMECLOCK_H
#define CODE_GAMECLOCK_H

#include "../../../libs/rtos/rtos.hpp"
#include "../../../libs/hwlib/hwlib.hpp"

class GameClock : public rtos::task<> {
    long long int start_time;
    int duration;
    int countdown = 10;
    bool game_running = false, countdown_running = false, clock_started = false;

    void main(void);

public:
    GameClock(
            const char *name,
            int duration,
            int countdown) : task(name), duration(duration), countdown(countdown){

    }
    GameClock(
            const char *name,
            int duration) : task(name), duration(duration), countdown(10) {

    }
    GameClock(
            const char *name) : task(name), duration(60), countdown(10) {

    }

    void set_duration(int duration);
    void set_countdown(int countdown);

    bool is_countdown_running();
    bool is_game_running();

    void start();

    bool started();
};

#endif //CODE_GAMECLOCK_H
