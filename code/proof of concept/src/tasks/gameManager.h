//
// Created by endargon on 10/25/16.
//

#ifndef CODE_GAMEMANAGER_H
#define CODE_GAMEMANAGER_H

#include "../../../libs/rtos/rtos.hpp"
#include "gameClock.h"
#include "comStation.h"

class GameManager : public rtos::task<> {
    GameClock &game_clock;
    ComStation &com_station;
    void main();

public:
    GameManager(const char * name, GameClock &game_clock, ComStation &com_station) : task(name), game_clock(game_clock), com_station(com_station){};
};
#endif //CODE_GAMEMANAGER_H
