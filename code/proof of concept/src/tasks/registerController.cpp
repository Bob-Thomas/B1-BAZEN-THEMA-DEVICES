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
    if(c.get_sender() == 0) {
        //admin command
        hwlib::cout << HERE << "Set gametime " << c.get_data() << " minutes";
    }
    c.print_command();
}