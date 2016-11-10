//
// Created by endargon on 10/27/16.
//

#include "registerController.h"

RegisterController::RegisterController( GameParameters &gp, DisplayController &dCtrl) : task("Register_Controller"), enabled(this, "register-enabled"), pressed(this, "button-pressed"), command_processed(this, "command-processed-flag"), gameParameters(gp), displayCtrl(dCtrl) { }

void RegisterController::main() {
    wait(enabled);
    displayCtrl.displayText("Press fire\n to start listening");
    wait(pressed);
    displayCtrl.displayText("Waiting for \n  signal");
    hwlib::wait_ms(300);
    receive(Command(0, 29));
    wait(command_processed);
    displayCtrl.displayText("Received \n gameTime");
    hwlib::wait_ms(300);
    receive(Command(10, 2));
    wait(command_processed);
    displayCtrl.displayText("Received Player \n Waiting for \n START SIGNAL");
    hwlib::wait_ms(1000);
    receive(Command(0, 0));
    for (; ;) {
        wait();
    }

}

void RegisterController::enable() {
    enabled.set();
}

void RegisterController::receive(Command c) {
    if(c.get_sender() == 0) {
        if(c.get_data() != 0) {
            gameParameters.game_time = c.get_data();
        }
        if(c.get_data() == 0) {
            displayCtrl.displayText("STARTING GAME in \n      5S");
            displayCtrl.displayText("STARTING GAME in \n      4S");
            displayCtrl.displayText("STARTING GAME in \n      3S");
            displayCtrl.displayText("STARTING GAME in \n      2S");
            displayCtrl.displayText("STARTING GAME in \n      1S");
            displayCtrl.displayText("STARTING GAME in \n      0S");
            next_state = 1;
        }
    } else {
        gameParameters.id = c.get_sender();
        gameParameters.weapon = c.get_data();
    }
    command_processed.set();
}

void RegisterController::button_pressed() {
    pressed.set();
}
