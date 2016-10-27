//
// Created by endargon on 10/27/16.
//

#include "registerController.h"

RegisterController::RegisterController() : task("Register_Controller"), enabled(this, "register-enabled") { }

void RegisterController::main() {
    for (; ;) {
        wait(enabled);
    }
}

void RegisterController::enable() {
    enabled.set();
}

void RegisterController::receive(Command c) {
    hwlib::cout << HERE << " RECEIVED << " << c.get_sender() << "\n";
}