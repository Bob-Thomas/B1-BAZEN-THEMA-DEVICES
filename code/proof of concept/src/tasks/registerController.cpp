//
// Created by endargon on 10/27/16.
//

#include "registerController.h"

RegisterController::RegisterController(DisplayController &d, GameParameters &gp) : task("Register_Controller"), enabled(this, "register-enabled"), displayCtrl(d), gameParameters(gp) { }

void RegisterController::main() {
    for (; ;) {

        displayCtrl.displayText("waiting data.. \n");

        // when register received...
            // todo..

        // decode signal and assign to variables below
            // todo...

        gameParameters.id = 1;
        gameParameters.weapon = 1;
        gameParameters.health = 100;

        // activate game time or something
            // todo...

        // this task is done, suspend task after init
        wait(enabled);

    }
}

void RegisterController::enable() {
    enabled.set();
}

void RegisterController::receive(Command c) {
    hwlib::cout << HERE << " RECEIVED << " << c.get_sender() << "\n";
}