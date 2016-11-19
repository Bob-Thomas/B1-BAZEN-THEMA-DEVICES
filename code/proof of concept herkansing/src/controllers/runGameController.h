//
// Created by smart on 11/19/2016.
//

#ifndef CODE_RUNGAMECONTROLLER_H
#define CODE_RUNGAMECONTROLLER_H

#include "../../../libs/rtos/rtos.hpp"
#include "../applicationLogic/command.h"
#include "../entities/gameParameters.h"
#include "../boundaries/sound.h"
#include "../boundaries/transmitter.h"
#include "displayController.h"
#include "../entities/arsenal.h"

class RunGameController : public rtos::task<> {
    private:
        const int invincible_time = 5;

        long long int last_hit;
        long long int last_shot;

        GameParameters gameParameters;

        rtos::clock game_clock;
        rtos::flag received;
        rtos::flag pressed;

        Sound& sound;
        Transmitter &transmitter;
        DisplayController display;
        Arsenal &arsenal;

        void shoot();
        void hit(int enemy_id, int weapon_id);

        void main();
    public:
        RunGameController(int priority, Sound sound, Transmitter transmitter, DisplayController display, Arsenal arsenal);

        void ir_received(Command& c);
        void button_pressed();

};
#endif //CODE_RUNGAMECONTROLLER_H
