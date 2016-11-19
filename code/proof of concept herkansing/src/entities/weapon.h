//
// Created by smart on 11/19/2016.
//

#ifndef B1_BAZEN_THEMA_DEVICES_WEAPON_H
#define B1_BAZEN_THEMA_DEVICES_WEAPON_H
class Weapon {
    private:
        int id;
        int cooldown;
        int damage;
        char * name;
    public:
        Weapon(int id, int cooldown, int damage, char * name);

        int get_id() const;

        void set_id(int id);

        int get_cooldown() const;

        void set_cooldown(int cooldown);

        int get_damage() const;

        void set_damage(int damage);

        char * get_name() const;

        void set_name(char *name);


};
#endif //B1_BAZEN_THEMA_DEVICES_WEAPON_H
