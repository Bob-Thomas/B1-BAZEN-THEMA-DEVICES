//
// Created by smart on 11/19/2016.
//

#include "arsenal.h"

Weapon Arsenal::get_weapon_by_id(int id) {
    for(int i = 0; i <3; i++) {
        if(weapons[i].get_id() == id) {
            return weapons[i];
        }
    }
    return Weapon(0,0,0, (char*)"Weapon not found");
}

void Arsenal::add_weapon(const Weapon& weapon) {
    if(weapon_counter < 3) {
        weapons[weapon_counter++] = weapon;
    } else {
        hwlib::cout << "arsenal full";
    }
}

Arsenal::Arsenal() {}