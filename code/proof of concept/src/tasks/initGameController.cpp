//
// Created by endargon on 10/26/16.
//

#include "initGameController.h"

InitGameController::InitGameController()
        : task("Init_Controller"), enabled(this, "init-enabled"), command_available(this, "command-available") { }

void InitGameController::main() {
    for (; ;) {
        wait(enabled);
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
