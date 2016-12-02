//
// Created by smart on 11/19/2016.
//

#include "runGameController.h"

RunGameController::RunGameController(int priority, Sound &sound, Transmitter &transmitter, DisplayController &display, Arsenal arsenal)
        : task(priority, "Rungame task"), game_clock(this, 600000000000, "gameclock")
        , received(this, "Received flag"), pressed(this, "Pressed flag"),
          sound(sound), transmitter(transmitter), display(display), arsenal(arsenal) {}


void RunGameController::main() {
    for(;;) {
        auto evt = wait(game_clock + pressed + received);

        if(evt == game_clock) {
            int duration = gameParameters.get_game_duration()-1;
            gameParameters.set_game_duration(duration);
        }
        else if(evt == pressed) {
            if(hwlib::now_us() - last_shot >= gameParameters.get_weapon().get_cooldown() && hwlib::now_us() - last_hit >= invincible_time) {
                shoot();
            }
        }
        else if(evt == received ) {
        }
    }

}

void RunGameController::shoot() {
    last_shot = hwlib::now_us();
    transmitter.send(Command(gameParameters.get_id(), gameParameters.get_weapon().get_id()).encode());
    sound.play_shoot();
}

void RunGameController::hit(int enemy_id, int weapon_id) {
    last_hit = hwlib::now_us();
    gameParameters.add_received_shot(enemy_id, arsenal.get_weapon_by_id(weapon_id).get_damage());
    sound.play_hit();
}


void RunGameController::ir_received(Command &c) {
    if(c.get_sender() == 0) {
        if(gameParameters.get_game_duration() == 0){
            gameParameters.set_game_duration(c.get_data());
        } else if(gameParameters.get_id() == 0) {
            gameParameters.set_id(c.get_data());
        } else if(gameParameters.get_weapon().get_id() == 0) {
            gameParameters.set_weapon(arsenal.get_weapon_by_id(c.get_data()));
        }
    }
    else {
        hit(c.get_sender(), c.get_data());
    }
    received.set();
}


void RunGameController::button_pressed() {
    pressed.set();
}
