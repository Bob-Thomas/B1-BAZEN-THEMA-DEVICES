//
// Created by smart on 10/26/2016.
//

#ifndef B1_BAZEN_THEMA_DEVICES_COMSTATION_H
#define B1_BAZEN_THEMA_DEVICES_COMSTATION_H

#include "../../../libs/rtos/rtos.hpp"
#include "transmitter.h"

struct command_type {
    int sender;
    int data;
    bool error = false;
};

class ComStation : public rtos::task<> {
        rtos::channel<command_type, 4000> commands;
        char* encode(command_type command);
        rtos::flag command_available;
        command_type decode(char command[16]);
        Transmitter &transmitter;

        void main();

    public:
        command_type get_command();
        void add_command(char command[16]);
        void send_command(command_type command);
        rtos::flag get_command_available_flag();
        ComStation(const char *name, Transmitter &transmitter) : task(name), commands(this, "commands"), command_available(this, "command-available"), transmitter(transmitter) { }
};

#endif //B1_BAZEN_THEMA_DEVICES_COMSTATION_H
