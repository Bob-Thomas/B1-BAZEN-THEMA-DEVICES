//
// Created by smart on 11/19/2016.
//

#include "weapon.h"

Weapon::Weapon(int id, int cooldown, int damage, char *name) : id(id), cooldown(cooldown), damage(damage),
                                                               name(name) { }

int Weapon::get_id() const {
    return id;
}

void Weapon::set_id(int id) {
    Weapon::id = id;
}

int Weapon::get_cooldown() const {
    return cooldown;
}

void Weapon::set_cooldown(int cooldown) {
    Weapon::cooldown = cooldown;
}

int Weapon::get_damage() const {
    return damage;
}

void Weapon::set_damage(int damage) {
    Weapon::damage = damage;
}

char *Weapon::get_name() const {
    return name;
}

void Weapon::set_name(char *name) {
    Weapon::name = name;
}