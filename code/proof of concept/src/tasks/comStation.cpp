//
// Created by smart on 10/26/2016.
//

#include "comStation.h"

char *ComStation::encode(command_type command) {
    return (char *) "101010100101010";
}

command_type ComStation::decode(char *command) {
    return {1, 2};
}


void ComStation::main() {
    for(;;) {
        wait(commands);
        command_available.set();
        sleep(1*rtos::ms);

    }
}

command_type ComStation::get_command() {
    return {1, 1};
}

void ComStation::add_command(char *command) {
    command_type decoded_command = decode(command);
    if(!decoded_command.error) {
        hwlib::cout << "Received command \n";
        commands.write(decoded_command);
    }
}

void ComStation::send_command(command_type command) {
    hwlib::cout << "sending command \n";
    transmitter.send(encode(command));
}

rtos::flag ComStation::get_command_available_flag() {
    return command_available;
}







