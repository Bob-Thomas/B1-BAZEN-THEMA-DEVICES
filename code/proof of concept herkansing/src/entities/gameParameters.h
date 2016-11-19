//
// Created by robbie on 9-11-2016.
//

#ifndef CODE_GAMEPARAMETERS_H
#define CODE_GAMEPARAMETERS_H

// struct for shot taken information.
// each shot can be registered in an array.

#include "weapon.h"

/**
 * \struct receive_shot
 * \brief receive_shot structure. Will be used for class GameParameters. Each structure contains the player id and weapon id from the received hit
 */

struct receive_shot {
    /**
     * play id from the received hit
     */
    int player_id;
    /**
     * amount of times the player got hit by this id
     */
    int amount;

};


/**
 * \class GameParameters
 * \brief GameParameters entity object will contain the player data.
 */

class GameParameters {
    private:
        /**
         * Amount of times the player got hit
         */
        int hit_amount;

        /**
         * received shots array
         */
        receive_shot shots[20];


        /**
         * int player id
         */
        int id;

        /**
         * int health
         */
        int health = 100;

        /**
         * weapon id
         */
        Weapon weapon;

        /**
         * game time
         */
        int game_duration;

    public:

        /**
         * GameParameter Constructor
         */
        GameParameters();

        /**
         * function to store the received shot data
         * /param player_id int for player id
         * /param weapon_id int for weapon id
         */
        void add_received_shot(int player_id, int damage);


        int get_game_duration() const;

        void set_game_duration(int game_duration);

        int get_id() const;

        void set_id(int id);

        int get_health() const;

        void set_health(int health);

        const Weapon &get_weapon() const {
            return weapon;
        }

        void set_weapon(const Weapon &weapon);

        const Weapon & get_weapon() const;
};


#endif //CODE_GAMEPARAMETERS_H
