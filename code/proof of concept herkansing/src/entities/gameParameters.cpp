//
// Created by robbie on 9-11-2016.
//

#include "gameParameters.h"

GameParameters::GameParameters(): shots_taken(0) {

}

void GameParameters::add_received_shot(int player_id, int damage) {
    health -= damage;
    if(hit_amount < 20) {
        int index = -1;

        for(int i = 0; i < sizeof(shots)/ sizeof(shots[0]); i++) {
            if(player_id == shots[i].player_id) {
                index = i;
            }
        }
        if(index != -1) {
            shots[index].amount++;
        } else {
            shots[hit_amount++] = {player_id, 0};
        }
    }
}

int GameParameters::get_game_duration() const {
    return game_duration;
}

void GameParameters::set_game_duration(int game_duration) {
    GameParameters::game_duration = game_duration;
}

int GameParameters::get_id() const {
    return id;
}

void GameParameters::set_id(int id) {
    GameParameters::id = id;
}

int GameParameters::get_health() const {
    return health;
}

void GameParameters::set_health(int health) {
    GameParameters::health = health;
}

void GameParameters::set_weapon(const Weapon &weapon) {
    GameParameters::weapon = weapon;
}

const Weapon &GameParameters::getWeapon() const {
    return weapon;
}