//
// Created by robbie on 9-11-2016.
//

#include "runGameController.h"

RunGameController::RunGameController(GameParameters &gameParam, DisplayController &disCtrl,Transmitter  &t, SoundController &sCtrl)
        : task("RunGame_Controller"), enabled(this, "runGame-enabled"), pressed(this, "button-pressed"),
          hit(this, "on_hit_flag"), game_timer(this, 600000000000, "Game-timer"), gameParameters(gameParam), displayCtrl(disCtrl),transmitter(t), soundCtrl(sCtrl) { }

void RunGameController::main() {
    rtos::clock dummy_hit(this, 20 * rtos::s, "Dummy timer cause receive no work");
    wait(enabled);
    game_timer.clear();
    // display on screen
    char txt[] = "hp: 100\nminutes left: 00";
    if (gameParameters.game_time < 10) {
        txt[22] = '0';
        txt[23] = (char) (48 + gameParameters.game_time);
    } else {
        txt[22] = (char) (48 + (gameParameters.game_time / 10));
        txt[23] = (char) (48 + (gameParameters.game_time % 10));
    }
    displayCtrl.displayText(txt);

    for (; ;) {

        wait(enabled);
        // check if button pressed or hit received or game over
        auto evt = wait(pressed + hit + dummy_hit + game_timer);
        if (evt == dummy_hit) {
            receive(Command(6, 2));//uncomment to get test hits
        }
        else if (evt == pressed) {
            transmitter.send(Command(gameParameters.id, gameParameters.weapon).encode());
            soundCtrl.play_shoot();
        }
        else if (evt == hit) {
            if (gameParameters.health <= 0) {
                update_screen_game_parameters(false);
                suspend();
            }
            else {
                update_screen_game_parameters(true);
            }
        }
        else if(evt == game_timer) {
            gameParameters.game_time--;
            if(gameParameters.game_time < 0) {
                char txt[] = "\n\n   YOU SURVIVED \n    END SCORE \n\n      100";
                if(gameParameters.health < 100) {
                    if (gameParameters.health < 10) {
                        txt[41] = '0';
                        txt[42] = (char) (48 + gameParameters.health);
                    } else {
                        txt[41] = (char) (48 + (gameParameters.health / 10));
                        txt[42] = (char) (48 + (gameParameters.health % 10));
                    }
                    txt[43] = ' ';
                }
                displayCtrl.displayText(txt);
                suspend();
            } else {
                update_screen_game_parameters(true);
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
    if (c.get_sender() != gameParameters.id && c.get_sender() != 0) {
        gameParameters.add_received_shot(c.get_sender(), c.get_data());
        hit.set();
    }
}

void RunGameController::update_screen_game_parameters(bool alive) {
    if(!alive) {
        char txt[] = "\n\n\n   YOU'RE DEAD \n Remaining time \n\n      10";
        if (gameParameters.game_time < 10) {
            txt[43] = '0';
            txt[44] = (char) (48 + gameParameters.game_time);
        } else {
            txt[43] = (char) (48 + (gameParameters.game_time / 10));
            txt[44] = (char) (48 + (gameParameters.game_time % 10));
        }
        displayCtrl.displayText(txt);
    } else {
        char txt[] = "hp: 100\nminutes left: 00";
        if (gameParameters.game_time < 10) {
            txt[22] = '0';
            txt[23] = (char) (48 + gameParameters.game_time);
        } else {
            txt[22] = (char) (48 + (gameParameters.game_time / 10));
            txt[23] = (char) (48 + (gameParameters.game_time % 10));
        }
        if(gameParameters.health < 100) {
            if (gameParameters.health < 10) {
                txt[4] = '0';
                txt[5] = (char) (48 + gameParameters.health);
            } else {
                txt[4] = (char) (48 + (gameParameters.health / 10));
                txt[5] = (char) (48 + (gameParameters.health % 10));
            }
            txt[6] = ' ';
        }
        displayCtrl.displayText(txt);
    }
}