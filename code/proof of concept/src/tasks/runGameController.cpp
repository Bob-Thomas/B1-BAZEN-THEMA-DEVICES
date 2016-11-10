//
// Created by robbie on 9-11-2016.
//

#include "runGameController.h"

RunGameController::RunGameController(GameParameters &gameParam, DisplayController &disCtrl, SoundController &sCtrl): task("RunGame_Controller"), enabled(this, "runGame-enabled"), pressed(this, "button-pressed"), hit(this, "on_hit_flag"), gameParameters(gameParam), displayCtrl(disCtrl), soundCtrl(sCtrl) { }

void RunGameController::main() {
    rtos::clock dummy_hit(this, 5*rtos::s, "Dummy timer cause receive no work");
    wait(enabled);
    // display on screen
    char txt[] = "hp: 100\nminutes left: 00";
    if(gameParameters.game_time < 10) {
        txt[22] = '0';
        txt[23] = (char)(48+gameParameters.game_time);
    } else {
        txt[22] = (char)(48+(gameParameters.game_time/10));
        txt[23] = (char)(48+(gameParameters.game_time%10));
    }
    displayCtrl.displayText(txt);

    for(;;) {

        wait(enabled);
        // check if button pressed or hit received or game over
        auto evt = wait(pressed + hit + dummy_hit);
        if(evt == dummy_hit) {
            receive(Command(6, 2));
        }
        if(evt == pressed) {
            hwlib::cout << "I was pressed";
            soundCtrl.play_shoot();
        }
        else if(evt == hit) {
            if(gameParameters.health <= 0) {
                displayCtrl.displayText("\n\n\n     YOU'RE DEAD");
                suspend();
            }
        }

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
    if(c.get_sender() != gameParameters.id && c.get_sender() != 0) {
        gameParameters.add_received_shot(c.get_sender(), c.get_data());
        hwlib::cout << gameParameters.health << "\n";
        char txt[] = "hp: 100\nminutes left: 00";

        gameParameters.game_time--;
        if(gameParameters.game_time < 10) {
            txt[22] = '0';
            txt[23] = (char)(48+gameParameters.game_time);
        } else {
            txt[22] = (char)(48+(gameParameters.game_time/10));
            txt[23] = (char)(48+(gameParameters.game_time%10));
        }
        if(gameParameters.health < 10) {
            txt[4] = '0';
            txt[5] = (char)(48+gameParameters.health);
        } else {
            txt[4] = (char)(48+(gameParameters.health/10));
            txt[5] = (char)(48+(gameParameters.health%10));
            txt[6] = '\0';
        }
        displayCtrl.displayText(txt);
    }
}