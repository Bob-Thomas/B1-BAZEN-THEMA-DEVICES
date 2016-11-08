//
// Created by endargon on 10/26/16.
//

#include "initGameController.h"

InitGameController::InitGameController(Transmitter &transmitter)
        : task("Init_Controller"), transmitter(transmitter), enabled(this, "init-enabled"), command_available(this, "command-available") { }

void InitGameController::main() {
    rtos::timer timer(this);
    Command test(0, 10);
    timer.set(2*rtos::s);
    for (; ;) {
        wait(enabled);
        wait(timer);
        hwlib::cout << "sending signal\n";
        test.print_command();
        transmitter.send(test.encode());
        timer.set(5*rtos::s);
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