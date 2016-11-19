//
// Created by smart on 11/19/2016.
//

#ifndef B1_BAZEN_THEMA_DEVICES_ARSENAL_H
#define B1_BAZEN_THEMA_DEVICES_ARSENAL_H

#include "weapon.h"
#include "../../../libs/hwlib/hwlib.hpp"

class Arsenal {
    private:
        int weapon_counter;
        Weapon weapons[3];

    public:

        Arsenal();

        Weapon get_weapon_by_id(int id);

        void add_weapon(const Weapon& weapon);
};
#endif //B1_BAZEN_THEMA_DEVICES_ARSENAL_H
