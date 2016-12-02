//
// Created by smart on 11/19/2016.
//

#ifndef CODE_RECEIVER_H
#define CODE_RECEIVER_H

#include "../../../libs/rtos/rtos.hpp"
#include "../../../libs/hwlib/hwlib.hpp"
#include "../applicationLogic/command.h"
#include "../controllers/runGameController.h"

class Receiver : public rtos::task<> {
    private:
        int highs = 0;
        short bits = 0;
        int amount_bits_found = 0;
        long long int received = 0;
        int commands_received = 0;
        int counter = 0;

        hwlib::target::pin_in &pin;
        RunGameController &controller;

        void main();

    public:
        Receiver(int priority, hwlib::target::pin_in &pin, RunGameController &controller);
};

#endif //CODE_RECEIVER_H