//
// Created by endargon on 10/27/16.
//

#include "registerController.h"
#include "../entities/gameParameters.h"

RegisterController::RegisterController( DisplayController &dCtrl) : task("Register_Controller"), enabled(this, "register-enabled"),displayCtrl(dCtrl) { }

void RegisterController::main() {


    for (; ;) {

        wait(enabled);
        displayCtrl.displayText("waiting signal..");

        // wait for signal


    }

}

void RegisterController::enable() {
    enabled.set();
}

void RegisterController::receive(Command c) {
    hwlib::cout << HERE << " RECEIVED << " << c.get_sender() << "\n";
}