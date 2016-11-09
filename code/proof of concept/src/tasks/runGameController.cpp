//
// Created by robbie on 9-11-2016.
//

#include "runGameController.h"

RunGameController::RunGameController(GameParameters &gameParam, DisplayController &disCtrl): task("RunGame_Controller"), enabled(this, "runGame-enabled"), gameParameters(gameParam), displayCtrl(disCtrl) { }

void RunGameController::main() {
    for(;;) {
        hwlib::cout << "derup";
        wait(enabled);
        char txt[] = "hp: 100\ntime left: 00:00";
        displayCtrl.displayText(txt);
    }
}

void RunGameController::enable() {
    enabled.set();
}

void RunGameController::receive(Command c) {
    hwlib::cout << HERE << " RECEIVED << " << c.get_sender() << "\n";
}