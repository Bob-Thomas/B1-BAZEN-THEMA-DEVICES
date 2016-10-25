//
// Created by endargon on 10/25/16.
//

#ifndef CODE_GAMEMANAGER_H
#define CODE_GAMEMANAGER_H

#include "../../../libs/rtos/rtos.hpp"
#include "gameClock.h"
#include "transmitter.h"

class GameManager : public rtos::task<> {
    GameClock &game_clock;
    Transmitter &transmitter;
    void main();

public:
    GameManager(const char * name, GameClock &game_clock, Transmitter &transmitter) : task(name), game_clock(game_clock), transmitter(transmitter){};
};
#endif //CODE_GAMEMANAGER_H
