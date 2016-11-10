//
// Created by robbie on 9-11-2016.
//

#include "gameParameters.h"

GameParameters::GameParameters(): shots_taken(0) {

}

void GameParameters::add_received_shot(int player_id, int weapon_id) {
    switch(weapon_id) {
        case 1:
            health -= 10;
        break;
        case 2:
            health -= 15;
        break;
        case 3:
            health -= 40;
        break;
    }

    if(shots_taken < 20) {
        // create structure
        receive_shot shot;

        // attributes
        shot.player_id = player_id;
        shot.weapon_id = weapon_id;

        // add to array
        shots[shots_taken] = shot;

        // array counter
        shots_taken++;
    }
}