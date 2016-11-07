//
// Created by endargon on 10/26/16.
//

#include "initGameController.h"

InitGameController::InitGameController(Transmitter &transmitter)
        : task("Init_Controller"), transmitter(transmitter), enabled(this, "init-enabled"), command_available(this, "command-available") { }

void InitGameController::main() {
    rtos::timer timer(this);
    Command test(2, 6);
    test.print_command();
    timer.set(1000);
    for (; ;) {
        wait(enabled);
        wait(timer);
        transmitter.send(test.encode());
        timer.set(1000);
    }
}


void InitGameController::receive(Command c) {
    command = c;
    command_available.set();
    hwlib::cout << HERE << " RECEIVED << " << c.get_sender() << "\n";
}

void InitGameController::enable() {
    enabled.set();
}