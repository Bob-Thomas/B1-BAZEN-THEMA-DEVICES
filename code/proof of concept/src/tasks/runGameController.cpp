//
// Created by robbie on 9-11-2016.
//

#include "runGameController.h"

RunGameController::RunGameController(GameParameters &gameParam, DisplayController &disCtrl): task("RunGame_Controller"), enabled(this, "runGame-enabled"), pressed(this, "button-pressed"), gameParameters(gameParam), displayCtrl(disCtrl) { }

void RunGameController::main() {

    wait(enabled);
    // display on screen
    char txt[] = "hp: 100\nminutes left: 10";
    displayCtrl.displayText(txt);

    for(;;) {

        wait(enabled);

        // check if button pressed or hit received or game over
        wait(pressed);

        hwlib::cout << "I was pressed";

    }

}

void RunGameController::enable() {
    enabled.set();
}

void RunGameController::button_pressed() {
    pressed.set();
}

void RunGameController::receive(Command c) {
    hwlib::cout << HERE << " RECEIVED << " << c.get_sender() << "\n";
}